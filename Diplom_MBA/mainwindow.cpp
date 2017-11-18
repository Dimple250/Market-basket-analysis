#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Size MainWindow
    const QRect r = QApplication::desktop()->availableGeometry();
    this->resize(r.width()*0.80, r.height()*0.80);

    loadStyle();

    db=QSqlDatabase::addDatabase("QMYSQL");
    //db.setHostName("elaks");
    db.setDatabaseName("journal");
    db.setUserName("root");
    db.setPassword("233685614");

    if(!db.open()){
        qDebug()<<"NO";
    }

    treeview=new QTreeWidget(this);


   QTreeWidgetItem* itemBD=new QTreeWidgetItem(treeview);
    itemBD->setText(0,db.databaseName());

    QTreeWidgetItem* itemTable=0;

    QStringList list=db.tables();

    foreach(QString st,list){
        itemTable=new QTreeWidgetItem(itemBD);
        itemTable->setText(0,st);
        qDebug()<<st;
    }
    QObject::connect(treeview,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),SLOT(openTable(QTreeWidgetItem*,int)));


    QDockWidget* dockBD=new QDockWidget(this);
    dockBD->setWidget(treeview);


    addDockWidget(Qt::LeftDockWidgetArea,dockBD);


    QSqlTableModel *model=new QSqlTableModel(this,db);
    model->setTable("stud");
    model->select();
    //зпрещает менять значения в ячейках
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    QSqlTableModel *model2=new QSqlTableModel(this,db);
    model2->setTable("marks");
    model2->select();
    //зпрещает менять значения в ячейках
    model2->setEditStrategy(QSqlTableModel::OnFieldChange);


    tableview=new QTableView;
    tableview->setModel(model);

    QTableView* t=new QTableView;
    t->setModel(model2);


    tab=new QTabWidget(this);
    tab->addTab(tableview,"Stud");
    tab->addTab(t,"Marks");
    tab->setTabsClosable(true);
    //tab->setTabShape(QTabWidget::Triangular);

    //create test dock
    //QDockWidget* dock=new QDockWidget(this);
    //dock->setWidget(tab);
     //addDockWidget(Qt::RightDockWidgetArea ,dock);

     setCentralWidget(tab);
}

void MainWindow::loadStyle(){
    QString CSS;
    QFile FileStyle("../Style/QTabWidget.css");
    if(FileStyle.open(QIODevice::ReadOnly)){
        CSS=FileStyle.readAll();
        FileStyle.close();
    }

    qApp->setStyleSheet(CSS);
}

void MainWindow::openTable(QTreeWidgetItem * item,int i){

    QString TableName=item->text(i);
    qDebug()<<item->parent()->data(0,0).toString();

    QSqlTableModel *model=new QSqlTableModel(this,db);
    model->setTable(TableName);
    model->select();
    //зпрещает менять значения в ячейках
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    QTableView* tableview=new QTableView;
     tableview->setModel(model);

    tab->addTab(tableview,TableName);
}

MainWindow::~MainWindow()
{
    delete ui;
}
