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
    //this->setFixedSize(r.width()*0.80, r.height()*0.80);

    db2=new Database;
    style=new Style;
    tab=new QTabWidget(this);
    QWidget* WidgetRepository=new QWidget(this);
    treeview=new QTreeWidget(WidgetRepository);
    addData=new QPushButton("AddData",WidgetRepository);


    //loadStyle();
    createTreeTables();

    this->setStyleSheet(style->getWindowStyleSheet());
    treeview->setStyleSheet(style->getTreeviewStyleSheet());
    tab->setStyleSheet(style->getTabWidgetStyleSheet());
    addData->setStyleSheet(style->getAddDataButtonStyleSheet());


    db2->Connect("journal");

    //qDebug() << QSqlDatabase::drivers();


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
    dockBD->setStyleSheet("background-color:pink;");
    addDockWidget(Qt::LeftDockWidgetArea,dockBD);


    //start test block
    QSqlTableModel *model=new QSqlTableModel(this);
    model->setTable("stud");
    model->select();
    //зпрещает менять значения в ячейках
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    tableview=new QTableView;
    tableview->setModel(model);
    //tableview->verticalHeader()->hide();

    //tableview->horizontalHeader()->setStyleSheet("QHeaderView::section{border:1px solid lightgray;}");
    //tableview->verticalHeader()->setStyleSheet("QHeaderView::section{border:1px solid lightgray;}");

    tableview->setStyleSheet("background-color:white;");

    tab->addTab(tableview,"Stud");
    tableview->resize(tab->size());
    //end test block


    tab->setTabsClosable(true);

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

}

MainWindow::~MainWindow()
{
    delete ui;
}
