#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QWidget>
#include <QtSql>
#include <QStandardItemModel>
#include <QScrollArea>

#include "database.h"
#include "style.h"
#include "associationrules.h"
#include "QCustomPlot/qcustomplot.h"
#include "salesanalysis.h"
#include "chart.h"

namespace Ui {
class MainWindow;
}

class QDesktopWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void createWidgetProducts();
    void createWidgetTransactions();
    void createTabWidgetRules();
    void createWidgetDiagram();
    void createWidgetAnalis();
private:
    Ui::MainWindow *ui;

    QTableView *tableview;
    QTableView *tableviewTrans;
    QListWidget* treeviewleft;
    QTabWidget* tabRules;
    QTableView* salesTableView;
    QTableView* ostatkiTableView;
    QTableView* rulesTableView;


    Database* database;
    Style* style;
    SalesAnalysis salesAnalysis;
    Chart chart;
    AssociationRules* rules;


    QMap<QString,double> condits;
    QStandardItemModel *csvModel;
    QGridLayout* mainGbox;
    QLabel*  welcome;

    QCustomPlot* customplot;

    QComboBox listCategory;
    QLineEdit namepProducts;
    QLineEdit namepSalesProducts;
    QComboBox inMonth;
    QComboBox variantDiagram;

    QDateEdit diagramToDate;
    QDateEdit diagramFromDate;

    QDateEdit toDate;
    QDateEdit fromDate;
    QTimeEdit toTime;
    QTimeEdit fromTime;

    QLineEdit minsupline;
    QLineEdit maxsupline;
    QLineEdit minconfline;
    QLineEdit maxconfline;
    QComboBox categoryline;


    QString isOpenItem;
    int prevopen;
    int numchek;
    QFont f;

    QWidget* Products;
    QWidget* Tranzactions;
    QWidget* Diagram;
    QWidget* Analis;
    QScrollArea *scrollAreaAnalis;
public slots:
    void openItem(QListWidgetItem*);
   // void closeTab(int);
    void changeProductsView();
    void changeTransactionsView();
    void changeAnalisProdycts();
    void changeDiagram();
    void OpenCSVFile();
    void createRules();
};

#endif // MAINWINDOW_H
