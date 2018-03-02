#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QWidget>
#include <QtSql>
#include <QStandardItemModel>

#include "database.h"
#include "style.h"
#include "associationrules.h"
#include "QCustomPlot/qcustomplot.h"
#include "salesanalysis.h"

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
    void createTreeTables();
    void createWidgetProducts();
    void createWidgetTransactions();
    void createTabWidgetRules();
    void createWidgetDiagram();
private:
    Ui::MainWindow *ui;
    QTableView *tableview;
    QTableView *tableviewTrans;
    QListWidget* treeviewleft;
    QTabWidget* tabRules;
    Database* database;
    Style* style;
    QMap<QString,double> condits;
    QStandardItemModel *csvModel;
    QGridLayout* mainGbox;
    QLabel*  welcome;

    QCustomPlot* customplot;

    QComboBox* listCategory;
    //QComboBox* listCategory;

    QString isOpenItem;
    int prevopen;
    int numchek;
    QFont f;

    QWidget* Products;
    QWidget* Tranzactions;
    QWidget* Diagram;
public slots:
    void openItem(QListWidgetItem*);
   // void closeTab(int);
    void changeProductsView();
    void changeTransactionsView();
    void OpenCSVFile();
    void createRules();
};

#endif // MAINWINDOW_H
