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
private:
    Ui::MainWindow *ui;
    QTableView *tableview;
    QTableView *tableviewTrans;
    QTreeWidget* treeviewleft;
    QTabWidget* tabRules;
    Database* db2;
    Style* style;
    QMap<QString,double> condits;
    QStandardItemModel *csvModel;
    QGridLayout* mainGbox;
    QLabel*  welcome;
    QCustomPlot* customplot;

    QComboBox* listCategory;

    QString isOpenItem;
    int prevopen;
    int numchek;
    QFont f;

    QWidget* Products;
    QWidget* Tranzactions;
public slots:
    void openItem(QTreeWidgetItem*,int);
   // void closeTab(int);
    void OpenCSVFile();
    void createRules();
    void ProductsView();
    void TransactionView();
};

#endif // MAINWINDOW_H
