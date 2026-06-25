#ifndef CONFIG_H
#define CONFIG_H

// =====================================================================
//  ZENTRALE EINSTELLUNGEN
//  In der Projektwoche muss normalerweise NUR diese Datei angepasst
//  werden: Zugangsdaten, Tabellenname und wie viele Datensaetze geholt
//  werden. Der restliche Code bleibt unveraendert.
// =====================================================================

namespace Config {

// --- Verbindung zur Datenbank ----------------------------------------
inline const char* HOST     = "127.0.0.1";   // Server-Adresse (localhost = 127.0.0.1)
inline const char* USER     = "root";        // Benutzername
inline const char* PASSWORD = "p123456";            // Passwort
inline const char* DATABASE = "produktion";      // Name der Datenbank
inline const unsigned int PORT = 3306;       // Standard-Port von MySQL

// --- Welche Daten sollen geholt werden? ------------------------------
inline const char* TABLE        = "messwerte"; // Name der Tabelle
inline const char* ORDER_COLUMN = "id";        // Spalte, nach der "die letzten" bestimmt werden
                                               // (z.B. id oder ein Zeitstempel)
inline const int   RECORD_COUNT = 20;          // Wie viele Datensaetze (das "X")

} // namespace Config

#endif // CONFIG_H
