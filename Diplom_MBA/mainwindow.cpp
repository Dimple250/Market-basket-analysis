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



    db2=new Database;
    db2->Connect("journal");
    style=new Style;
    tab=new QTabWidget(this);
    QWidget* WidgetRepository=new QWidget(this);
    treeview=new QTreeWidget(WidgetRepository);
    addData=new QPushButton("AddData",WidgetRepository);


    //loadStyle();
    createTreeTables();

    //this->setStyleSheet(style->getWindowStyleSheet());
    //treeview->setStyleSheet(style->getTreeviewStyleSheet());
    //tab->setStyleSheet(style->getTabWidgetStyleSheet());
    //addData->setStyleSheet(style->getAddDataButtonStyleSheet());



    connect(tab,SIGNAL(tabCloseRequested(int)),SLOT(closeTab(int)));


    addData->setIcon(QIcon("../Picture/plus.png"));
    addData->setIconSize(QSize(20,20));
    addData->setMinimumHeight(30);
    //treeview->setIconSize(QSize(20,20)););


    QVBoxLayout* VBox=new QVBoxLayout;
    VBox->addWidget(addData);
    VBox->addWidget(treeview);
    WidgetRepository->setLayout(VBox);


    QDockWidget* dockBD=new QDockWidget("Repository");
    dockBD->setWidget(WidgetRepository);
    //dockBD->setStyleSheet("background-color:pink;");
    addDockWidget(Qt::LeftDockWidgetArea,dockBD);


    //start test block
    QSqlTableModel *model=new QSqlTableModel(this);
    model->setTable("transactions");
    model->select();
    //зпрещает менять значения в ячейках
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableview=new QTableView;
    //tableview->setModel(model);


    QSqlQueryModel* query=new QSqlQueryModel;
    QSqlQuery* query2=new QSqlQuery;
    query->setQuery("select count(tid) from transactions group by tid");
    query2->exec("select count(tid) from transactions group by tid");
    int kol=query2->numRowsAffected();
    query2->exec("select count(name)/"+QString::number(kol)+" from transactions group by name;");
    query2->next();
    qDebug()<<query2->value(0).toFloat();
    query->setQuery("select name,count(name)/"+QString::number(kol)+" from transactions group by name;");
    tableview->setModel(query);
    //tableview->verticalHeader()->hide();

    //tableview->horizontalHeader()->setStyleSheet("QHeaderView::section{border:1px solid lightgray;}");
    //tableview->verticalHeader()->setStyleSheet("QHeaderView::section{border:1px solid lightgray;}");

    tableview->setStyleSheet("background-color:white;");

    tab->addTab(tableview,model->tableName());
    tableview->resize(tab->size());
    //end test block


    tab->setTabsClosable(true);

    //create test dock
    //QDockWidget* dock=new QDockWidget(this);
    //dock->setWidget(tab);
     //addDockWidget(Qt::RightDockWidgetArea ,dock);


     setCentralWidget(tab);

}

void MainWindow::createRules(){

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



void MainWindow::createTreeTables(){

    QTreeWidgetItem* itemBD=new QTreeWidgetItem(treeview);

     itemBD->setText(0,"BD");

     QPixmap pixmap("../Picture/BD.png");

     itemBD->setIcon(0,pixmap);
     treeview->setIconSize(QSize(23,23));

     QTreeWidgetItem* itemBDname=new QTreeWidgetItem(itemBD);
     itemBDname->setText(0,db2->getNameBase());

     QTreeWidgetItem* itemTable=0;

     QStringList list=db2->tables();

     foreach(QString st,list){
         itemTable=new QTreeWidgetItem(itemBDname);
         itemTable->setText(0,st);
         itemTable->setIcon(0,QIcon("../Picture/table.png"));
        // qDebug()<<st;
     }

     QObject::connect(treeview,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),SLOT(openTable(QTreeWidgetItem*,int)));

     treeview->header()->hide();

}


void MainWindow::openTable(QTreeWidgetItem * item,int i){

    QString TableName=item->text(i);

    int pages = tab->count() ;
    for ( int i = 0; i < pages; i++ ) {
     if ( tab->tabText(i) == TableName ) {
      tab->setCurrentIndex(i);
      return;
     }
    }
    //qDebug()<<item->parent()->data(0,0).toString();

    QSqlTableModel *model=new QSqlTableModel(this);
    model->setTable(TableName);
    model->select();
    //зпрещает менять значения в ячейках
    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    QTableView* tableview=new QTableView;
     tableview->setModel(model);

    tableview->setStyleSheet("background-color:white;");

    tab->addTab(tableview,TableName);

    tableview->resize(tab->size());
    tableview->setStyleSheet(style->getTableViewStyleSheet());

    tab->setCurrentIndex(tab->currentIndex()+1);

}

void MainWindow::closeTab(int index){
    tab->removeTab(index);
}

MainWindow::~MainWindow()
{
    delete ui;
}
