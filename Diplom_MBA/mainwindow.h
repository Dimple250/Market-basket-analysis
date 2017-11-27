#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>

#include "database.h"
#include "style.h"

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
    void loadStyle();
    void createRules();

private:
    Ui::MainWindow *ui;
    QTableView *tableview;
    QTreeWidget* treeview;
    QTabWidget* tab;
    QPushButton* addData;
    Database* db2;
    Style* style;
public slots:
    void openTable(QTreeWidgetItem*,int);
    void createTreeTables();
    void closeTab(int);
};

#endif // MAINWINDOW_H
