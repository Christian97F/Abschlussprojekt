#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config.h"
#include "database.h"

#include <QtWidgets>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

using namespace QtCharts;

// ---------------------------------------------------------------------
//  Aufbau des Fensters
// ---------------------------------------------------------------------
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // --- Bedienelemente per Code aufbauen ---
    // (bewusst im Code statt im Designer, damit alles an EINER Stelle
    //  nachvollziehbar ist.)

    QPushButton *refreshButton = new QPushButton("Aktualisieren");
    m_status = new QLabel("Bereit.");

    // Anzeige 1: Tabelle
    m_table = new QTableWidget;
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers); // nur ansehen

    // Anzeige 2: Diagramm
    m_chartView = new QChartView(new QChart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    // Tabelle und Diagramm nebeneinander, Trennbalken verschiebbar.
    QSplitter *splitter = new QSplitter;
    splitter->addWidget(m_table);
    splitter->addWidget(m_chartView);

    // Alles untereinander: oben der Button, dann der Splitter, unten Status.
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(refreshButton);
    layout->addWidget(splitter);
    layout->addWidget(m_status);

    QWidget *central = new QWidget;
    central->setLayout(layout);
    setCentralWidget(central);

    setWindowTitle("Datenbank-Visualisierung");
    resize(900, 500);

    // Klick auf den Button ruft loadData() auf.
    connect(refreshButton, &QPushButton::clicked, this, &MainWindow::loadData);

    // Beim Start direkt einmal laden.
    loadData();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ---------------------------------------------------------------------
//  Daten laden: verbinden -> abfragen -> anzeigen
// ---------------------------------------------------------------------
void MainWindow::loadData()
{
    Database db;
    QString error;

    if (!db.connect(&error)) {
        m_status->setText(error);
        return;
    }

    QueryResult result = db.fetchLast(Config::RECORD_COUNT, &error);
    if (result.isEmpty()) {
        m_status->setText(error.isEmpty() ? "Keine Daten gefunden." : error);
        return;
    }

    showData(result);
    m_status->setText(QString("%1 Datensaetze geladen.").arg(result.rowCount()));
}

// ---------------------------------------------------------------------
//  Anzeige verteilen
//
//  Hier wird entschieden, WIE die Daten dargestellt werden. Eine
//  Anzeigeform weglassen = entsprechende Zeile auskommentieren.
// ---------------------------------------------------------------------
void MainWindow::showData(const QueryResult &result)
{
    fillTable(result);
    fillChart(result);
}

// ---------------------------------------------------------------------
//  Anzeige 1: Tabelle
// ---------------------------------------------------------------------
void MainWindow::fillTable(const QueryResult &result)
{
    m_table->clear();
    m_table->setColumnCount(result.columnCount());
    m_table->setRowCount(result.rowCount());
    m_table->setHorizontalHeaderLabels(result.columns);

    for (int r = 0; r < result.rowCount(); ++r) {
        const QStringList &row = result.rows[r];
        for (int c = 0; c < row.size(); ++c) {
            m_table->setItem(r, c, new QTableWidgetItem(row[c]));
        }
    }
    m_table->resizeColumnsToContents();
}

// ---------------------------------------------------------------------
//  Anzeige 2: Diagramm
//
//  Generisch: Jede Spalte, deren Werte sich komplett in Zahlen wandeln
//  lassen, wird als eigene Linie gezeichnet. Text-Spalten werden
//  uebersprungen. So funktioniert das Diagramm mit beliebigen Tabellen.
// ---------------------------------------------------------------------
void MainWindow::fillChart(const QueryResult &result)
{
    QChart *chart = new QChart;

    for (int c = 0; c < result.columnCount(); ++c) {

        // Pruefen, ob die ganze Spalte numerisch ist.
        bool columnIsNumeric = true;
        for (int r = 0; r < result.rowCount() && columnIsNumeric; ++r) {
            bool ok = false;
            result.rows[r][c].toDouble(&ok);
            if (!ok) columnIsNumeric = false;
        }
        if (!columnIsNumeric) continue;   // Text-Spalte ueberspringen

        // Eine Linie pro numerischer Spalte.
        QLineSeries *series = new QLineSeries;
        series->setName(result.columns[c]);
        for (int r = 0; r < result.rowCount(); ++r) {
            series->append(r, result.rows[r][c].toDouble());
        }
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->setTitle(QString("Letzte %1 Datensaetze").arg(result.rowCount()));

    // Altes Diagramm durch das neue ersetzen.
    QChart *old = m_chartView->chart();
    m_chartView->setChart(chart);
    delete old;
}
