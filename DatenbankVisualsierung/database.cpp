#include "database.h"
#include "config.h"

#include <mysql.h>   // MySQL C API (Connector/C) -- Pfad in der .pro gesetzt

// ---------------------------------------------------------------------
//  Konstruktor / Destruktor
// ---------------------------------------------------------------------
Database::Database()
    : m_conn(nullptr)
{
}

Database::~Database()
{
    // Verbindung sauber schliessen, falls noch offen.
    if (m_conn) {
        mysql_close(m_conn);
        m_conn = nullptr;
    }
}

// ---------------------------------------------------------------------
//  Verbindung aufbauen
// ---------------------------------------------------------------------
bool Database::connect(QString *errorOut)
{
    // mysql_init reserviert das Verbindungs-Objekt.
    m_conn = mysql_init(nullptr);
    if (!m_conn) {
        if (errorOut) *errorOut = "mysql_init fehlgeschlagen (kein Speicher).";
        return false;
    }

    // Eigentlicher Verbindungsaufbau mit den Werten aus config.h.
    MYSQL *ok = mysql_real_connect(
        m_conn,
        Config::HOST,
        Config::USER,
        Config::PASSWORD,
        Config::DATABASE,
        Config::PORT,
        nullptr,   // Unix-Socket (unter Windows nicht noetig)
        0          // keine speziellen Flags
    );

    if (!ok) {
        // mysql_error liefert die Klartext-Fehlermeldung des Servers.
        if (errorOut) *errorOut = QString("Verbindung fehlgeschlagen: %1").arg(mysql_error(m_conn));
        mysql_close(m_conn);
        m_conn = nullptr;
        return false;
    }

    return true;
}

// ---------------------------------------------------------------------
//  Letzte X Datensaetze holen
// ---------------------------------------------------------------------
QueryResult Database::fetchLast(int count, QString *errorOut)
{
    QueryResult result;

    if (!m_conn) {
        if (errorOut) *errorOut = "Nicht verbunden. Zuerst connect() aufrufen.";
        return result;
    }

    // Abfrage zusammenbauen:
    //   SELECT * FROM <tabelle> ORDER BY <spalte> DESC LIMIT <count>
    // DESC + LIMIT holt die NEUESTEN count Zeilen.
    QString query = QString("SELECT * FROM %1 ORDER BY %2 DESC LIMIT %3")
                        .arg(Config::TABLE)
                        .arg(Config::ORDER_COLUMN)
                        .arg(count);

    // Abfrage an den Server schicken (0 = Erfolg).
    if (mysql_query(m_conn, query.toUtf8().constData()) != 0) {
        if (errorOut) *errorOut = QString("Abfrage fehlgeschlagen: %1").arg(mysql_error(m_conn));
        return result;
    }

    // Ergebnis komplett vom Server abholen.
    MYSQL_RES *res = mysql_store_result(m_conn);
    if (!res) {
        if (errorOut) *errorOut = QString("Kein Ergebnis: %1").arg(mysql_error(m_conn));
        return result;
    }

    // --- Spaltennamen auslesen ---
    unsigned int numFields = mysql_num_fields(res);
    MYSQL_FIELD *fields = mysql_fetch_fields(res);
    for (unsigned int i = 0; i < numFields; ++i) {
        result.columns << QString::fromUtf8(fields[i].name);
    }

    // --- Zeilen auslesen ---
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(res)) != nullptr) {
        QStringList cells;
        for (unsigned int i = 0; i < numFields; ++i) {
            // row[i] ist ein C-String oder nullptr (SQL NULL).
            cells << (row[i] ? QString::fromUtf8(row[i]) : QString());
        }
        result.rows << cells;
    }

    mysql_free_result(res);

    // Wir haben absteigend (neueste zuerst) geholt. Fuer Diagramme ist
    // aufsteigend (aelteste zuerst) angenehmer -> Reihenfolge umdrehen.
    std::reverse(result.rows.begin(), result.rows.end());

    return result;
}
