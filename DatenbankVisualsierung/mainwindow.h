#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "queryresult.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class QTableWidget;
class QLabel;
QT_END_NAMESPACE

// QtCharts liegt in Qt5 in einem eigenen Namespace.
namespace QtCharts { class QChartView; }

// =====================================================================
//  MainWindow
//
//  Holt die Daten ueber die Database-Klasse und zeigt sie an.
//  Anzeige besteht aus zwei Teilen, die beide dasselbe QueryResult
//  lesen:  fillTable()  und  fillChart().
//  Anzeigeform tauschen = in showData() eine Zeile aus-/einkommentieren.
// =====================================================================

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void loadData();   // verbinden, abfragen, anzeigen (Button "Aktualisieren")

private:
    void showData(const QueryResult &result);              // verteilt an die Anzeigen
    void fillTable(const QueryResult &result);             // Anzeige 1: Tabelle
    void fillChart(const QueryResult &result);             // Anzeige 2: Diagramm

    Ui::MainWindow *ui;
    QTableWidget *m_table;
    QtCharts::QChartView *m_chartView;
    QLabel *m_status;
};

#endif // MAINWINDOW_H
