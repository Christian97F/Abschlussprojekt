#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include "queryresult.h"

// Vorwaerts-Deklaration, damit mysql.h nicht im Header gebraucht wird.
// (haelt diese Datei sauber; mysql.h wird nur in database.cpp benoetigt)
// In MySQL 8 heisst der Typ direkt "MYSQL", deshalb genau so deklarieren.
struct MYSQL;

// =====================================================================
//  Database
//
//  Duenne Huelle um die MySQL C API. Aufgabe:
//    1. Verbindung aufbauen  -> connect()
//    2. Letzte X Datensaetze holen -> fetchLast()
//
//  Rueckgabe ist immer ein generisches QueryResult, damit der Rest des
//  Programms nichts ueber MySQL wissen muss.
// =====================================================================

class Database {
public:
    Database();
    ~Database();

    // Baut die Verbindung anhand der Werte aus config.h auf.
    // Gibt true bei Erfolg zurueck. Bei Fehler steht der Grund in errorOut.
    bool connect(QString *errorOut = nullptr);

    // Holt die letzten 'count' Datensaetze aus der konfigurierten Tabelle,
    // sortiert nach Config::ORDER_COLUMN. Reihenfolge im Ergebnis:
    // aelteste zuerst, neueste zuletzt (gut fuer Diagramme).
    QueryResult fetchLast(int count, QString *errorOut = nullptr);

private:
    struct MYSQL *m_conn;   // Verbindungs-Handle der C API (nullptr = nicht verbunden)
};

#endif // DATABASE_H
