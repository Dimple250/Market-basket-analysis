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

    numchek=1001;


    db2=new Database;
    db2->Connect("market");
    style=new Style;
    tabRules=new QTabWidget;
    treeviewleft=new QTreeWidget;
    csvModel = new QStandardItemModel;

    createWidgetProducts();
    createWidgetTransactions();
    createTabWidgetRules();


   /* QMenu*  menu_file=new QMenu("&File");
    menu_file->addAction("Open",this,SLOT(OpenCSVFile()));
    //menu_file->addAction("Save",this,SLOT(SaveFile()));
    menu_file->addSeparator();
    menu_file->addAction("Exit",this,SLOT(close()));

   // QMenu*  menu_analiz=new QMenu("&Analysis");
    //menu_file->addAction("Open",this,SLOT(OpenCSVFile()));*/
    QMenu*  menu_rules=new QMenu("&Rules");
    menu_rules->addAction("Create",this,SLOT(createRules()));

    ui->menubar->addMenu(menu_rules);



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
    //ui mainToolBar->setVisible(false);

    //loadStyle();
    //createTreeTables();

    //this->setStyleSheet(style->getWindowStyleSheet());
  // treeview->setStyleSheet(style->getTreeviewStyleSheet());
    tabRules->setStyleSheet(style->getTabWidgetStyleSheet());
  //  addData->setStyleSheet(style->getAddDataButtonStyleSheet());



   // connect(tabRules,SIGNAL(tabCloseRequested(int)),SLOT(closeTab(int)));
    connect(treeviewleft,SIGNAL(itemClicked(QTreeWidgetItem*,int)),SLOT(openItem(QTreeWidgetItem*,int)));



    treeviewleft->setStyleSheet(style->getTreeviewleftStyleSheet());
     QTreeWidgetItem* item=0;

     QStringList list;
     list<<"Продукты"<<"Транзакции"<<"Анализ корзины"<<"Поиск шаболных покупок"<<"Диаграммы"<<"Склад"<<"Загрузить файл"<<"";

     foreach(QString st,list){
         item=new QTreeWidgetItem(treeviewleft);
         item->setText(0,st);
     }

     treeviewleft->header()->hide();




   // tabRules->setTabsClosable(true);

   // treeviewleft->setMaximumHeight(r.height()*0.80);
    treeviewleft->setMaximumWidth(r.width()*0.20);
    treeviewleft->setMinimumWidth(r.width()*0.10);
     //WidgetRepository->setFixedWidth(r.width()*0.15);
     welcome=new QLabel("Добро пожаловат\n ");
     welcome->setStyleSheet("font-size:50px;padding-top:-400%;padding-left:300%;background-color:#4C5866;padding-right:300%;color:white;");

     int id = QFontDatabase::addApplicationFont("../Fonts/HelveticaRegular.ttf"); //путь к шрифту
         QString family = QFontDatabase::applicationFontFamilies(id).at(0); //имя шрифта
         QFont f(family);  // QFont c вашим шрифтом

         treeviewleft->setFont(f);

     mainGbox=new QGridLayout;
     mainGbox->addWidget(treeviewleft,0,0);
     mainGbox->addWidget(welcome,0,1);
     mainGbox->addWidget(Products,0,1);
     mainGbox->addWidget(Tranzactions,0,1);

     mainGbox->addWidget(tabRules,0,1);
     prevopen=1;

     Products->setHidden(true);
     Tranzactions->setHidden(true);
     tabRules->setHidden(true);


     ui->centralwidget->setLayout(mainGbox);


}

void MainWindow::createWidgetProducts(){
    Products=new QWidget;
    Products->setStyleSheet("background-color:#4C5866;");

    tableview=new QTableView(Products);
    /*QSqlTableModel *model=new QSqlTableModel(db2);
        model->setTable("products");
        model->select();
        //зпрещает менять значения в ячейках
        model->setEditStrategy(QSqlTableModel::OnFieldChange);

        QTableView* tableview=new QTableView;
         tableview->setModel(model);*/
    QSqlQuery query;
        query.exec("select category.name,products.name,price from products inner join category using(idcat);");

        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
           horizontalHeader.append("");
           horizontalHeader.append("Категория");
           horizontalHeader.append("Продукты");
           horizontalHeader.append("Цена");

           model->setHorizontalHeaderLabels(horizontalHeader);

           int i=0;
           while (query.next()) {
           //Первый ряд
           item = new QStandardItem(query.value(0).toString());
           model->setItem(i, 1, item);

           item = new QStandardItem(query.value(1).toString());
           model->setItem(i, 2, item);

           item = new QStandardItem(QString::number(query.value(2).toFloat()));
           model->setItem(i, 3, item);
           i++;
  }

           tableview->setModel(model);

        tableview->setStyleSheet(style->getTableViewStyleSheet());
        tableview->setColumnHidden(0,true);
        int id = QFontDatabase::addApplicationFont("../Fonts/HelveticaRegular.ttf"); //путь к шрифту
                  QString family = QFontDatabase::applicationFontFamilies(id).at(0); //имя шрифта
                  QFont f(family);  // QFont c вашим шрифтом

                 tableview->setFont(f);

                 tableview->resizeRowsToContents();
                 tableview->resizeColumnsToContents();
                 tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
                    tableview->setAlternatingRowColors(true);
                     tableview->setSelectionMode(QAbstractItemView::SingleSelection);

    QHBoxLayout* layoutprod=new QHBoxLayout;
    layoutprod->addWidget(tableview);

    Products->setLayout(layoutprod);

}

void MainWindow::createWidgetTransactions(){
    Tranzactions=new QWidget;
    Tranzactions->setStyleSheet("background-color:#4C5866;");

    QSqlTableModel *model=new QSqlTableModel(db2);
        model->setTable("transactions");
        model->select();
        //зпрещает менять значения в ячейках
        model->setEditStrategy(QSqlTableModel::OnFieldChange);

        QTableView* tableview=new QTableView;
         tableview->setModel(model);

        tableview->setStyleSheet(style->getTableViewStyleSheet());
        //tableview->setColumnHidden(0,true);
        tableview->setColumnWidth(2,250);
       int id = QFontDatabase::addApplicationFont("../Fonts/HelveticaRegular.ttf"); //путь к шрифту
                 QString family = QFontDatabase::applicationFontFamilies(id).at(0); //имя шрифта
                 QFont f(family);  // QFont c вашим шрифтом

                tableview->setFont(f);
              //  tableview->resizeRowsToContents();
               // tableview->resizeColumnsToContents();
                tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);


       // tableview->resize();
       // tableview->setStyleSheet(style->getTableViewStyleSheet());

    QHBoxLayout* layout=new QHBoxLayout;
    layout->addWidget(tableview);

    Tranzactions->setLayout(layout);

}

void MainWindow::createTabWidgetRules(){

}

void MainWindow::createRules(){

    //Creater transaction
    /*QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    QStringList st;
    QFile file("/home/elaks/Документы/College/Диплом/Diplom_A.R.K/BD/Transactions.txt");
    if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
        qDebug() << "File not exists";
    } else {
        // Create a thread to retrieve data from a file
        QTextStream in(&file);
        //Reads the data up to the end of file
        while (!in.atEnd())
        {
            st<<in.readLine();
        }
       // qDebug()<<st[0];
    }
     int k=qrand()%15+1;
     QString str="";
     int rand=0;
     QList<int> list;
     for(int i=0;i<k;i++){
        // qDebug()<<st[qrand()%90];
         rand=qrand()%92;
        while(list.indexOf(rand)!=-1){
        rand=qrand()%92;
        }
        str+=QString::number(numchek)+";"+st[rand]+QString::number(qrand()%5+1)+'\n';
         list<<rand;
     }

     QFile fileOut("/home/elaks/Документы/College/Диплом/Diplom_A.R.K/BD/TR.txt"); // Связываем объект с файлом fileout.txt
         if(fileOut.open(QIODevice::Append | QIODevice::Text))
         { // Если файл успешно открыт для записи в текстовом режиме
             QTextStream writeStream(&fileOut); // Создаем объект класса QTextStream
     // и передаем ему адрес объекта fileOut
             writeStream <<str; // Посылаем строку в поток для записи
             fileOut.close(); // Закрываем файл
         }
     numchek++;*/


    tabRules->clear();

     AssociationRules* rules=new AssociationRules;
     rules->setMinSup(5);
     rules->setMinConf(50);
     rules->CreateRules();
     //rules->setTable();

       tabRules->addTab(rules->getTableRyles(),"Test Rules Table");
        tabRules->addTab(rules->getTextRyles(),"Test Rules Text");


}

void MainWindow::createTreeTables(){

   /* QTreeWidgetItem* itemBD=new QTreeWidgetItem(treeview);

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

     treeview->header()->hide();*/

}


void MainWindow::openItem(QTreeWidgetItem * item,int i){

    if(item->text(i)==isOpenItem){
        return;
    }


    if(item->text(i)=="Продукты"){//"Продукты"
        isOpenItem="Продукты";
      mainGbox->itemAt(prevopen)->widget()->setHidden(true);
     Products->setHidden(false);
     prevopen=2;
    }else
        if(item->text(i)=="Транзакции"){//"Транзакции"
            isOpenItem="Транзакции";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
           Tranzactions->setHidden(false);
           prevopen=3;

    }else
        if(item->text(i)=="Анализ корзины"){//"Анализ корзины"
            /*isOpenItem="Анализ корзины";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
           //Tranzactions->setHidden(false);
           prevopen=4;*/
    }else
        if(item->text(i)=="Поиск шаболных покупок"){//"Поиск шаболных покупок"
            isOpenItem="Поиск шаболных покупок";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
           tabRules->setHidden(false);
           prevopen=4;
    }/*else
        if(item->text(i)=="Диаграммы"){//"Диаграммы"
            isOpenItem="Диаграммы";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
          // Tranzactions->setHidden(false);
           prevopen=6;
    }else
        if(item->text(i)=="Склад"){//"Склад"
            isOpenItem="Склад";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
          // Tranzactions->setHidden(false);
           prevopen=7;
    }*/

}

/*void MainWindow::closeTab(int index){
    tabRules->removeTab(index);
}*/

void MainWindow::OpenCSVFile(){
   /* QString str = QFileDialog::getOpenFileName(0, "Open file", "", "*.csv");
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
       tabRules->addTab(tableview,"CSV");*/
}

MainWindow::~MainWindow()
{
    delete ui;
   /* delete csvModel;
    delete tableview;
    delete treeview;
    delete tab;
    delete addData;
    delete db2;
    delete style;
    delete welcome;
    delete mainHbox;*/
}
