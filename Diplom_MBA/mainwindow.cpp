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
    addDockWidget(Qt::LeftDockWidgetArea,dockBD);


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

    int kol_chek=query2->numRowsAffected();

    query2->exec("SELECT name,COUNT(*) FROm transactions GROUP BY name;");

    while(query2->next()){
            if(query2->value(1).toInt()>=min_sup){
                list<<query2->value(0).toString();
            }
        }
        qDebug()<<list;

        int flag=1;
        int kol_items=3;

        while(flag!=0){

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

        QString exec="select "+items+", COUNT(*) from "+baskets+" where "+ravno+" and "+mensh+" group by "+items+" having count(*)>=2;";
        //qDebug()<<exec;

        query2->exec(exec);
        QString ss="";

        while(query2->next()){
            ss="";
            for(int i=0;i<kol_items-1;i++){
            ss+=query2->value(i).toString()+",";
            }
            list<<ss;
            }
            qDebug()<<list;

            kol_items++;

            query2->last();
           flag=query2->at();
           qDebug()<<flag;
        }



         int kol2=list.length();



    /*query2->exec("select tid from transactions group by tid");

    while(query2->next()){
                ListTid<<query2->value(0).toString();
            //qDebug()<<query2->value(0).toFloat();
        }
        qDebug()<<ListTid;*/



   // query2->exec("select count(tid) from transactions group by tid");

    //query2->next();
    //qDebug()<<query2->value(0).toString();

    //qDebug()<<query2->value(1).toString();
    //query2->last();
    //qDebug()<<query2->at();


    /*float count=0;
    int schet=0;
    float sup=0;

     QSqlQuery* query3=new QSqlQuery;

        for(int i=0;i<kol2;i++){
            for(int j=i+1;j<kol2;j++){
                 count=0;
                for(int tid=0;tid<ListTid.length();tid++){
                    schet=0;
                    query3->exec("select name from transactions where tid="+ListTid[tid]+";");

                    while(query3->next()){
                        if(query3->value(0).toString()==list[i]||query3->value(0).toString()==list[j]){
                            schet++;
                        }
                    }

                    if(schet==2){
                        count++;
                    }

                }
                    sup=count/kol_chek;
                   qDebug()<<list[i]<<','<<list[j]<<"="<<sup;

                   if(sup>=min_sup){
                       list<<list[i]+','+list[j];
                  }
                }

        }*/
        // qDebug()<<list;



    query->setQuery("select name,count(name)/"+QString::number(kol_chek)+" from transactions group by name;");
    tableview->setModel(query);

    tab->addTab(tableview,"Test Rusles");
    tableview->resize(tab->size());
    tableview->setStyleSheet(style->getTableViewStyleSheet());

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
