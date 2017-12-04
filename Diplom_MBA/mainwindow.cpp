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
    tableview=new QTableView;


    //loadStyle();
    createTreeTables();

    //this->setStyleSheet(style->getWindowStyleSheet());
    //treeview->setStyleSheet(style->getTreeviewStyleSheet());
    tab->setStyleSheet(style->getTabWidgetStyleSheet());
    //addData->setStyleSheet(style->getAddDataButtonStyleSheet());



    connect(tab,SIGNAL(tabCloseRequested(int)),SLOT(closeTab(int)));
    connect(treeview,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),SLOT(openTable(QTreeWidgetItem*,int)));


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
    addDockWidget(Qt::RightDockWidgetArea,dockBD);



    QStringList qlist;
    qlist<<"Look data base"<<"Add transaction"<<"Create Rules";

    QListWidget* lwg=new QListWidget(this);
    QListWidgetItem* item=0;

    foreach(QString str,qlist){
        item=new QListWidgetItem(str,lwg);
    }

    QDockWidget* dockLeft=new QDockWidget("Items");
    dockLeft->setWidget(lwg);
    //dockBD->setStyleSheet("background-color:pink;");
    addDockWidget(Qt::LeftDockWidgetArea,dockLeft);



    //start test block
    QSqlTableModel *model=new QSqlTableModel(this);
    model->setTable("transactions");
    model->select();
    //зпрещает менять значения в ячейках
    model->setEditStrategy(QSqlTableModel::OnFieldChange);


    tableview->setModel(model);

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
     createRules();

}

void MainWindow::createRules(){

    //bug
    /*for(int i=0;i<list.length();i++){
        for(int j=i+1;j<list.length();j++)
            list<<list[i]+','+list[j];
    }*/

    QList<QString> list;
    QList<QString> ListTid;
    int min_sup=2;
    int length=1;

    QString items="";
    QString baskets="";
    QString ravno="";
    QString mensh="";


    QTableView* tableview=new QTableView;
    tableview->setStyleSheet("background-color:white;");


    QSqlQueryModel* query=new QSqlQueryModel;
    QSqlQuery* query2=new QSqlQuery;
    query->setQuery("select count(tid) from transactions group by tid");
    query2->exec("select count(tid) from transactions group by tid");
    //usless
    int kol_chek=query2->numRowsAffected();
    //fix next
    query2->exec("SELECT name,COUNT(*) FROm transactions GROUP BY name;");

    while(query2->next()){
            if(query2->value(1).toInt()>=min_sup){
                //list<<query2->value(0).toString()<<query2->value(1).toString();
                condits[query2->value(0).toString()]=query2->value(1).toDouble();
            }
        }
        qDebug()<<list;

        int flag=1;
        int kol_items=4-1;

        while(flag>0){
          items="";
          baskets="";
          ravno="";
          mensh="";

        for(int i=1;i<kol_items;i++){
        items+="t"+QString::number(i)+".name,";
        }
        items=items.remove(items.length()-1,items.length()-1);

        for(int i=1;i<kol_items;i++){
        baskets+="transactions as t"+QString::number(i)+",";
        }
        baskets=baskets.remove(baskets.length()-1,baskets.length()-1);

        for(int i=1;i<kol_items-1;i++){
        ravno+="t"+QString::number(i)+".tid=t"+QString::number(i+1)+".tid ";
        ravno+="and ";
        }
        ravno=ravno.remove(ravno.length()-5,ravno.length()-1);

        for(int i=1;i<kol_items-1;i++){
        mensh+="t"+QString::number(i)+".name<t"+QString::number(i+1)+".name ";
        mensh+="and ";
        }
        mensh=mensh.remove(mensh.length()-5,mensh.length()-1);

        QString exec="select "+items+", COUNT(*) from "+baskets+" where "+ravno+" and "+mensh+" group by "+items+" having count(*)>="+QString::number(min_sup)+";";
        //qDebug()<<exec;

        query2->exec(exec);
        QString ss="";

        while(query2->next()){
            ss="";
            for(int i=0;i<kol_items-1;i++){
            ss+=query2->value(i).toString()+",";
            }
            list<<ss.remove(ss.length()-1,ss.length()-1);
            //ss=ss.remove(ss.length()-1,ss.length()-1);
           //list<<query2->value(kol_items-1).toString();
            condits[ss]=query2->value(kol_items-1).toDouble();
             qDebug()<<ss;
            }
            //qDebug()<<list;

            kol_items++;


            query2->last();
           flag=query2->at();
        }

         QLabel* lb=new QLabel(tab);
         int y=300;
         for(int i=0;i<4;i++){
             lb=new QLabel(tab);
             y+=20;
         lb->setStyleSheet("margin-top:"+QString::number(y)+"px;margin-left:100px;");
         double sup=condits[list[i]]/kol_chek;
         double cond=condits[list[i]]/condits[list[i].split(",")[0]];
         //double lift=condits[list[2]]/(condits[list[2].split(",")[0]]*condits[list[2].split(",")[1]]);
         double lift=cond/condits[list[i].split(",")[0]];
         QString st="";
         for(int k=1;k<list[i].split(",").length();k++){
             st+=list[i].split(",")[k];
             if(k!=list[i].split(",").length()-1){
             st+=",";
             }
         }
         lb->setText(list[i].split(",")[0]+"==>"+st+"{support:"+QString::number(sup,'f',2)+",confidence:"+QString::number(cond,'f',2)+",lift:"+QString::number(lift,'f',2)+"}");
       }
         qDebug()<<list.length();



    query->setQuery("select name,count(name)/"+QString::number(kol_chek)+" from transactions group by name;");
    tableview->setModel(query);

    /*tab->addTab(tableview,"Test Rusles");
    tableview->resize(tab->size());
    tableview->setStyleSheet(style->getTableViewStyleSheet());

    tab->setCurrentIndex(1);*/


    QTableWidgetItem* tableitem=0;

      QTableWidget*  tablewidget=new QTableWidget;
      tablewidget->setRowCount(list.length());
      tablewidget->setColumnCount(2);
      tablewidget->setHorizontalHeaderLabels(QString("Items;Support").split(";"));

      int kol=0;

        for(int i=0;i<list.length();i++){
         tableitem=new QTableWidgetItem(list[i]);
         tablewidget->setItem(kol,0,tableitem);
         tableitem=new QTableWidgetItem(QString::number(condits[list[i]]));
         tablewidget->setItem(kol,1,tableitem);
         kol++;
        }

        tab->addTab(tablewidget,"Test Rusles");
        //tablewidget->resize(tab->size());
        //tableview->setStyleSheet(style->getTableViewStyleSheet());

        tab->setCurrentIndex(1);


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
