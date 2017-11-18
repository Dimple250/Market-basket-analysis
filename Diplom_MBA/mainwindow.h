#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtSql>

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

private:
    Ui::MainWindow *ui;
    QTableView *tableview;
    QTreeWidget* treeview;
    QTabWidget* tab;
    QSqlDatabase db;
public slots:
    void openTable(QTreeWidgetItem*,int);
};

#endif // MAINWINDOW_H
