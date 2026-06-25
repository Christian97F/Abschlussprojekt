#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <QStringList>
#include <QVector>

// =====================================================================
//  Generisches Abfrage-Ergebnis
//
//  Das ist eine reine Datenstruktur. Sie weiss NICHTS von MySQL und
//  NICHTS von der Anzeige. Genau deshalb ist die Anzeigeform leicht
//  austauschbar: Die Datenbank fuellt diese Struktur, und Tabelle oder
//  Diagramm lesen nur daraus.
//
//  Aufbau wie eine Tabelle:
//    columns = Spaltennamen, z.B. {"id", "temperatur", "zeit"}
//    rows    = Liste von Zeilen, jede Zelle als Text
// =====================================================================

struct QueryResult {
    QStringList columns;           // Spaltenueberschriften
    QVector<QStringList> rows;     // eine QStringList pro Zeile

    bool isEmpty() const { return rows.isEmpty(); }
    int rowCount() const { return rows.size(); }
    int columnCount() const { return columns.size(); }
};

#endif // QUERYRESULT_H
