//-----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>

#define trennzeichen     ';'     //Trennzeichen als Zeichen (für Vergleich in getfile)
#define trennzeichen_str ";"     //Trennzeichen als String (für strtok in readcsv)

#define HOST "localhost"
#define PORT 3306
#define USER "root"
#define PASSWORD "p123456"
#define DB "produktion"


//-----------------------------------------------------------------------------
//---struct mit den CSV Dimensionen + FILE pointer-----------------------------
//-----------------------------------------------------------------------------

typedef struct CsvInfo{
	
	char filename[256];		//Dateiname
	FILE *file;				//pointer auf Datei
	int line_len;			//Länge der längsten Zeile
	int lines;				//Anzahl Zeilen
	int cols;				//Anzahl Spalten
	int cell_size;			//Länge des größten Zelleninhalts
	int has_header;			//Gibt es eine Überschriftenzeile?

} CsvInfo;



//-----------------------------------------------------------------------------
//---inline-Funktion für virtuelles 3D Array-----------------------------------
//-----------------------------------------------------------------------------

static inline int idx(int i, int j, int k, int cols, int cell_size){
	
	return i*cols*cell_size + j*cell_size + k;

}



//-----------------------------------------------------------------------------
//---Funktions-Prototypen------------------------------------------------------
//-----------------------------------------------------------------------------

void get_file(CsvInfo *csv);
void read_csv(CsvInfo *csv, char *array);
void print_array(CsvInfo *csv, char *array);

MYSQL *connect_to_db(void);
int run_query(MYSQL *conn, const char *query);
void insert_row(MYSQL *conn, CsvInfo *csv, char *array, int line);
void push_to_db(CsvInfo *csv, char *array);



//-----------------------------------------------------------------------------
//---main Funktion-------------------------------------------------------------
//-----------------------------------------------------------------------------

int main(void){
	
	CsvInfo csv = {0};
	csv.has_header = 1;
	
	getfile(&csv);		//CSV-Datei öffnen, Dimensionen bestimmen
	
	char *daten = malloc((size_t)csv.lines * csv.cols * csv.cell_size * sizeof(char));  	//size_t da Ergebnis potenziell zu groß für int
	
	if(!daten){
		
		fprintf(stderr, "malloc failed!");
		fclose(csv.file);
		exit(1);
	
	}
		
	readcsv(&csv, daten); 		//CSV-Datei in Array speichern
	
	printarray(&csv, daten);	//Inhalt ausgeben(drucken)

	pushtoDB(&csv, daten);		//Daten in Datenbank übertragen

	fclose(csv.file);		//file schließen und Speicher freigeben
	free(daten);
	
	
	getchar();
	
	return 0;

}



//-----------------------------------------------------------------------------
//---CSV auswählen, öffnen und Dimensionen bestimmen, diese in struct ablegen--
//-----------------------------------------------------------------------------

void get_file(CsvInfo *csv){
	
	int c;							//ASCII für einen char
	int current_len = 0;			//aktuelle Zeilenlänge
	int max_cell_size = 0;			//länge der größten Zelle
	int current_cell_size = 0;		//aktuelle Zellenlänge
	int cols_counted = 0;			//wurden die Spalten bereits gezählt?
	char *line_buffer;				//buffer für eine Zeile
	
	printf("enter file name: ");							//Konsoleneingabe = Dateiauswahl
	fgets(csv->filename, sizeof(csv->filename), stdin);
	
	csv->filename[strcspn(csv->filename, "\n")] = '\0';		//"\n" durch '\0' ersetzen
	
	csv->file = fopen(csv->filename, "r");
	
	if(!csv->file){
		
		fprintf(stderr, "\ncan`t open file!");
		exit(1);
	
	}
	
	while((c = fgetc(csv->file)) != EOF){		//Zeichen für Zeichen einlesen
		
		if(c == trennzeichen || c == '\n'){		//Ende einer Zelle erkennen
			
			if(!cols_counted){			//Spalten müssen nur einmal gezählt werden
				
				csv->cols++;
				
			}
			
			if(max_cell_size < current_cell_size){
				
				max_cell_size = current_cell_size;
				
			}
			
			current_cell_size = 0;
			
		}
		if(c == '\n'){		//Ende einer Zeile erkennen
			
			if(csv->line_len < current_len){
			
				csv->line_len = current_len;
			
			}
			
			cols_counted = 1;
			current_len = 0;
			
		}
		else{
			
			current_len++;
			current_cell_size++;
			
		}
				
	}
	
	csv->cell_size = max_cell_size + 1;		//+1 für Null-Terminator
	
	rewind(csv->file);		//FILE pointer wieder auf den Anfang
	
	line_buffer = malloc(csv->line_len + 2);		//Speicherplatz allozieren mit +2 für \n und \0
	
	if(!line_buffer){
		
		fprintf(stderr, "malloc failed!");
		fclose(csv->file);
		exit(1);
	
	}
	
	while(fgets(line_buffer, csv->line_len + 2, csv->file)){		//Zeilenweises Einlesen um Zeilenzahl zu bestimmen
		
		csv->lines++;
		
	}
	
	free(line_buffer);		//Speicher freigeben
	
}



//-----------------------------------------------------------------------------
//---CSV-Datei in Array speichern----------------------------------------------
//-----------------------------------------------------------------------------

void read_csv(CsvInfo *csv, char *array){
	
	int line_counter = 0;		//Zähler für Zeilen
	int col_counter = 0;		//Zähler für Spalten
	char *line_buffer;			//buffer für eine Zeile
	char *token;				//von einer Zeile abgeschnittener Zelleninhalt
	
	rewind(csv->file);
	
	line_buffer = malloc(csv->line_len + 2);		//+2 für \n und \0
	
	if(!line_buffer){
		
		fprintf(stderr, "malloc failed!");
		fclose(csv->file);
		exit(1);
	
	}
	
	while(fgets(line_buffer, csv->line_len + 2, csv->file) && line_counter < csv->lines){		//Schleife durch alle Zeilen
		
		for(token = strtok(line_buffer, trennzeichen_str);token != NULL && col_counter < csv->cols; token = strtok(NULL, trennzeichen_str)){
			
			token[strcspn(token, "\n")] = '\0';			//"\n" ersetzen durch '\0'
			
			strcpy(&array[idx(line_counter, col_counter, 0, csv->cols, csv->cell_size)], token);
			
			col_counter++;
			
		}
		
		line_counter++;
		col_counter = 0;
		
	}
	
	free(line_buffer);
	
}



//-----------------------------------------------------------------------------
//---print-Funktion zum Testen-------------------------------------------------
//-----------------------------------------------------------------------------

void print_array(CsvInfo *csv, char *array){
	
	for(int i = 0; i < csv->lines; i++){
		
		printf("\n");
		
		for(int j = 0; j < csv->cols; j++){
			
			printf("%s\t", &array[idx(i, j, 0, csv->cols, csv->cell_size)]);
			
		}
		
	}
	
}



//-----------------------------------------------------------------------------
//---Verbindung zur Datenbank herstellen---------------------------------------
//-----------------------------------------------------------------------------


MYSQL *connect_to_db(void){

	MYSQL *connection = mysql_init(NULL);
	
	if(!connection){
		
		fprintf(stderr, "SQL Initialisierung fehlgeschlagen\n");
		return NULL;
	}
	
	if(mysql_real_connect(connection, HOST, USER, PASSWORD, DB, PORT, NULL, 0) == NULL){

		fprintf(stderr, "Verbindung mit der Datenabank fehlgeschlagen: %s\n", mysql_error(connection));
		mysql_close(connection);
		return NULL;
			
    }
	
	printf("\nVerbindung zur Datenbank hergestellt\n");
	
	return connection;
	
}



//-----------------------------------------------------------------------------
//---Funktion zum Senden einer Query-------------------------------------------
//-----------------------------------------------------------------------------


int run_query(MYSQL *conn, const char *query){
	
	
	
}


//-----------------------------------------------------------------------------
//---Funktion zum Übertragen in die Datenbank----------------------------------
//-----------------------------------------------------------------------------


void push_to_db(CsvInfo *csv, char *array){
	
	MYSQL *connection = connect_to_db();
	char query[1000];
	
	if(!connection){
		
		return;
	}
	
	
	for(int lines = 0; lines < csv->lines; lines++){
		
		if((csv->has_header && lines) || !csv->has_header){
			
			//1. Query für die Fahrrad Tabelle erstellen und an die Datenbank senden
			snprintf(query, sizeof(query),
				"INSERT INTO `produktion`.`fahrrad` (`serien_NR`) VALUES (%s)",
				&array[idx(lines, 0, 0, csv->cols, csv->cell_size)]);

			if(mysql_query(connection, query)){

				fprintf(stderr, "Query fehlgeschlagen: %s\n", mysql_error(connection));
				mysql_close(connection);
				return;

			}

			//2. Query für die Endkontrolle Tabelle erstellen und an die Datenbank senden
			snprintf(query, sizeof(query),
				"INSERT INTO `produktion`.`endkontrolle_daten` (`serien_NR`, `nachbearbeitungszeit`, `abschluss_test`, `test_datum`) VALUES (%s, %s, %s, '%s')",
				&array[idx(lines, 0, 0, csv->cols, csv->cell_size)],
				&array[idx(lines, 4, 0, csv->cols, csv->cell_size)],
				&array[idx(lines, 6, 0, csv->cols, csv->cell_size)],
				&array[idx(lines, 7, 0, csv->cols, csv->cell_size)]);

			if(mysql_query(connection, query)){

				fprintf(stderr, "Query fehlgeschlagen: %s\n", mysql_error(connection));
				mysql_close(connection);
				return;

			}
			
			//Query für die Produktions Tabelle erstellen und an die Datenbank senden
			snprintf(query, sizeof(query),
				"INSERT INTO `produktion`.`produktions_daten` (`serien_NR`, `laenge`, `kleber_menge`, `kleber_temp`, `lackmenge`) VALUES (%s, %s, %s, %s, %s)",
				&array[idx(lines, 0, 0, csv->cols, csv->cell_size)],
				&array[idx(lines, 1, 0, csv->cols, csv->cell_size)],
				&array[idx(lines, 2, 0, csv->cols, csv->cell_size)],
				&array[idx(lines, 3, 0, csv->cols, csv->cell_size)],
				&array[idx(lines, 5, 0, csv->cols, csv->cell_size)]);
			
			if(mysql_query(connection, query)){
				
				fprintf(stderr, "Query fehlgeschlagen: %s\n", mysql_error(connection));
				mysql_close(connection);
				return;
				
			}
			
		}
		
	}
	
	mysql_close(connection);
	
}
