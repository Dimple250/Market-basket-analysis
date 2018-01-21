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
    tab=new QTabWidget;
    QWidget* WidgetRepository=new QWidget;
    treeview=new QTreeWidget(WidgetRepository);
    treeviewleft=new QTreeWidget;
    addData=new QPushButton("AddData",WidgetRepository);
    tableview=new QTableView;



    QMenu*  menu_file=new QMenu("&File");
    menu_file->addAction("Open",this,SLOT(OpenCSVFile()));
    //menu_file->addAction("Save",this,SLOT(SaveFile()));
    menu_file->addSeparator();
    menu_file->addAction("Exit",this,SLOT(close()));

    QMenu*  menu_analiz=new QMenu("&Analysis");
    menu_file->addAction("Open",this,SLOT(OpenCSVFile()));

    ui->menuBar->addMenu(menu_file);
    ui->menuBar->addMenu(menu_analiz);





    /*QAction* file=new QAction("file",0);
    file->setIcon(QPixmap("/home/elaks/Документы/College/Диплом/Diplom_MBA/Picture/New/frXbUkgtdj.png"));
    file->setToolTip("");
  // QObject::connect(lock,SIGNAL(triggered()),SLOT(Cipher_Atbash_and_Polibia()));

    QAction* open=new QAction("open",0);
    open->setIcon(QPixmap("/home/elaks/Документы/College/Диплом/Diplom_MBA/Picture/New/image_20170928_192348_4943.png"));
    open->setToolTip("");

    QToolBar* toolBar=new QToolBar;
    toolBar->addAction(file);
    toolBar->addAction(open);
    toolBar->setIconSize(QSize(30,30));
    ui->mainToolBar->addWidget(toolBar);
    //ui->mainToolBar->setStyleSheet("background:white");*/
    ui->mainToolBar->setVisible(false);

    //loadStyle();
    createTreeTables();

    //this->setStyleSheet(style->getWindowStyleSheet());
   treeview->setStyleSheet(style->getTreeviewStyleSheet());
    tab->setStyleSheet(style->getTabWidgetStyleSheet());
  //  addData->setStyleSheet(style->getAddDataButtonStyleSheet());



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


    //QDockWidget* dockBD=new QDockWidget("Repository");
    //dockBD->setWidget(WidgetRepository);
    //dockBD->setStyleSheet("background-color:pink;");
   // addDockWidget(Qt::RightDockWidgetArea,dockBD);



    /*QStringList qlist;
    qlist<<"Look data base"<<"Add transaction"<<"Create Rules";

    QListWidget* lwg=new QListWidget(this);
    QListWidgetItem* item=0;

    foreach(QString str,qlist){
        item=new QListWidgetItem(str,lwg);

    }
    lwg->setStyleSheet("background:blue;");*/

    treeviewleft->setStyleSheet(style->getTreeviewfeltStyleSheet());
     QTreeWidgetItem* item=0;

     QStringList list;
     list<<"Продукты"<<"Транзакции"<<"Анализ корзины"<<"Поиск шаболных покупок"<<"Диаграммы"<<"Склад"<<""<<"Заказать пиццу";

     foreach(QString st,list){
         item=new QTreeWidgetItem(treeviewleft);
         item->setText(0,st);
     }

     treeviewleft->header()->hide();

    //QDockWidget* dockLeft=new QDockWidget("Items");
   // dockLeft->setWidget(treeviewleft);
    //dockBD->setStyleSheet("background-color:pink;");
   // addDockWidget(Qt::LeftDockWidgetArea,dockLeft);



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


     //setCentralWidget(tab);
     createRules();

     treeviewleft->setFixedHeight(r.height()*0.80);
     treeviewleft->setFixedWidth(r.width()*0.15);
     WidgetRepository->setFixedWidth(r.width()*0.15);
     //treeviewleft

     QHBoxLayout* hbox=new QHBoxLayout;
     hbox->addWidget(treeviewleft);
     hbox->addWidget(tab);
     hbox->addWidget(WidgetRepository);


     ui->centralWidget->setLayout(hbox);
    // this->setStyleSheet("background-color:#4C5866");

   // tab->setHidden(false);

    /* QSqlDatabase db1 = QSqlDatabase::addDatabase("QODBC3", "xlsx_connection");
     db1.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + QString("/home/elaks/Excel2.xlsx"));
     if(db1.open())
     {
      QSqlQuery query("select * from [" + QString("Sheet1") + "$]"); // Select range, place A1:B5 after $

      while (query.next())
      {
      QString column1= query.value(0).toString();
      qDebug() << column1;
      }
     db1.close();
     QSqlDatabase::removeDatabase("xlsx_connection");
     }else{
      qDebug()<<"sdf"<<db1.lastError().text();

     }*/

     QSqlDatabase db = QSqlDatabase::addDatabase("QODBC3", "xlsx_connection");
        QString baseName;
        baseName += "DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)}; FIL={MS Excel}; ";
        baseName += "DBQ=/home/elaks/Excel2.xlsx";
        db.setDatabaseName(baseName);
        if(!db.open()){
            qDebug()<<"dsfs";
        }

}

void MainWindow::createRules(){

     AssociationRules* rules=new AssociationRules;
     rules->setMinSup(2);
     rules->CreateRules();
     //rules->setTable();


         tab->addTab(rules,"Test Rules");


   /* QTableWidgetItem* tableitem=0;

      QTableWidget*  tablewidget=new QTableWidget;
      tablewidget->setRowCount(rules->getListSize());
      tablewidget->setColumnCount(2);
      tablewidget->setHorizontalHeaderLabels(QString("Items;Support").split(";"));

      int kol=0;

        for(int i=0;i<rules->getListSize();i++){
         tableitem=new QTableWidgetItem(list[i]);
         tablewidget->setItem(kol,0,tableitem);
         tableitem=new QTableWidgetItem(QString::number(condits[list[i]]));
         tablewidget->setItem(kol,1,tableitem);
         kol++;
        }

        tab->addTab(tablewidget,"Test confidence");
        //tablewidget->resize(tab->size());
        //tableview->setStyleSheet(style->getTableViewStyleSheet());*/

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

void MainWindow::OpenCSVFile(){
    QString str = QFileDialog::getOpenFileName(0, "Open file", "", "*.csv");
    if(str==""){
        return;
    }

    QTableView* tableview=new QTableView(this);

    csvModel = new QStandardItemModel;
       csvModel->setColumnCount(2);
       csvModel->setHorizontalHeaderLabels(QStringList() << "Марка" << "Модель" << "Цена");

       // Open the file from the resources. Instead of the file
       // Need to specify the path to your desired file
       QFile file(str);
       if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
           qDebug() << "File not exists";
       } else {
           // Create a thread to retrieve data from a file
           QTextStream in(&file);
           //Reads the data up to the end of file
           while (!in.atEnd())
           {
               QString line = in.readLine();

               // Adding to the model in line with the elements
               QList<QStandardItem *> standardItemsList;
               // consider that the line separated by semicolons into columns
               QStringList item;
               item << line.split(',');
               for (int i=0;i<item.length();i++) {
                  standardItemsList.append(new QStandardItem(item[i]));
               }
               csvModel->insertRow(csvModel->rowCount(), standardItemsList);
           }
           file.close();
       }
       tableview->setModel(csvModel);
       tab->addTab(tableview,"CSV");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete csvModel;
    delete tableview;
    delete treeview;
    delete tab;
    delete addData;
    delete db2;
    delete style;
}
