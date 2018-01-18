#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
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
    QTreeWidget* treeview;
    QTabWidget* tab;
    QPushButton* addData;
    Database* db2;
    Style* style;
    QMap<QString,double> condits;
    QStandardItemModel *csvModel;
public slots:
    void openTable(QTreeWidgetItem*,int);
    void closeTab(int);
    void OpenCSVFile();
};

#endif // MAINWINDOW_H
