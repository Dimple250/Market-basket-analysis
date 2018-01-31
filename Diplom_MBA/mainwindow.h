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
    void createRules();
    void createTreeTables();
private:
    Ui::MainWindow *ui;
    QTableView *tableview;
    QTreeWidget* treeviewleft;
    QTabWidget* tab;
    Database* db2;
    Style* style;
    QMap<QString,double> condits;
    QStandardItemModel *csvModel;
    QGridLayout* mainGbox;
    QLabel*  welcome;

    QString isOpenItem;
    int prevopen;

    QWidget* Products;
    QWidget* Tranzactions;
public slots:
    void openTable(QTreeWidgetItem*,int);
    void openItem(QTreeWidgetItem*,int);
    void closeTab(int);
    void OpenCSVFile();
};

#endif // MAINWINDOW_H
