#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
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
#include "addtransaction.h"

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
    AddTransaction* formAddTransaction;

    QTableView *tableview;
    QTableView *tableviewTrans;
    QListWidget* treeviewleft;
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
    QCustomPlot* customplot1;
    QCustomPlot* customplot2;
    QCustomPlot* customplotSales;
    QCustomPlot* customplotOstatki;

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

    QComboBox* boxTovar;

    QString isOpenItem;
    int prevopen;
    int numchek;
    QFont f;

    QWidget* Products;
    QWidget* Tranzactions;
    QWidget* Rules;
    QWidget* Diagram;
    QWidget* Analis;
    QScrollArea *scrollAreaAnalis;
public slots:
    void openItem(QListWidgetItem*);
    void openFormAddTrans();
    void changeProductsView();
    void changeTransactionsView();
    void changeAnalisProdycts();
    void changeDiagram();
    void OpenCSVFile();
    void createRules();
    void addTovar();
    void delTovar();
    void showPointToolTip(QMouseEvent *event);
    void analisPdf();
    void chartsPdf();
    void rulesPdf();
};

#endif // MAINWINDOW_H
