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

    int id = QFontDatabase::addApplicationFont("../Fonts/HelveticaRegular.ttf"); //путь к шрифту
              QString family = QFontDatabase::applicationFontFamilies(id).at(0); //имя шрифта
              f.setFamily(family);  // QFont c вашим шрифтом


    db2=new Database;
    db2->Connect("market");
    style=new Style;
    treeviewleft=new QListWidget;
    csvModel = new QStandardItemModel;

    createWidgetProducts();
    createWidgetTransactions();
    createTabWidgetRules();
    createWidgetDiagram();


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
    connect(treeviewleft,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(openItem(QListWidgetItem*)));



    treeviewleft->setStyleSheet(style->getTreeviewleftStyleSheet());
     QListWidgetItem* item=0;

     QStringList list;
     list/*<<"Главная"*/<<"Продукты"<<"Транзакции"<<"Анализ корзины"<<"Поиск шаболных покупок"<<"Аналитика"<<"Склад"<<"Загрузить файл"<<"Профиль";

     treeviewleft->setIconSize(QSize(70,70));
     foreach(QString st,list){
         item=new QListWidgetItem(st,treeviewleft);
       // item->setIcon(QPixmap("../Picture/LeftPanel/"+st+".png"));
         //item->setText(0,st);
     }

   //  treeviewleft->header()->hide();




   // tabRules->setTabsClosable(true);

   // treeviewleft->setMaximumHeight(r.height()*0.80);
    treeviewleft->setMaximumWidth(r.width()*0.20);
    treeviewleft->setMinimumWidth(r.width()*0.08);
     //WidgetRepository->setFixedWidth(r.width()*0.15);
     welcome=new QLabel("Добро пожаловаться\n ");
     welcome->setStyleSheet("font-size:50px;padding-top:-400%;padding-left:300%;background-color:#4C5866;padding-right:300%;color:white;");

         treeviewleft->setFont(f);

      //   QLabel* Hat=new QLabel("LUTIK");
       //  Hat->setStyleSheet(/*"background-color:#292E2D;*/"background-color:#292E3D;padding:15%,10%;padding-left:10%;color:white;font-size:30px;");
        // Hat->setFont(f);

     mainGbox=new QGridLayout;
    // mainGbox->addWidget(Hat,0,0,1,2);
     mainGbox->addWidget(treeviewleft,0,0);
     mainGbox->setSpacing(5);
     mainGbox->addWidget(welcome,0,1);
     mainGbox->addWidget(Products,0,1);
     mainGbox->addWidget(Tranzactions,0,1);

     mainGbox->addWidget(tabRules,0,1);
     mainGbox->addWidget(Diagram,0,1);
     prevopen=1;

     Products->setHidden(true);
     Tranzactions->setHidden(true);

     tabRules->setHidden(true);
     Diagram->setHidden(true);


     ui->centralwidget->setLayout(mainGbox);


}


void MainWindow::ProductsView(){
    QString category="";
    QString querystr="";
    if(listCategory->currentIndex()==0){
        querystr="select category.name,products.name,price from products inner join category using(idcat);";
    }else{
        category=listCategory->currentText();
        querystr="select category.name,products.name,price from products inner join category using(idcat) where category.name like '"+category+"';";
    }

        QSqlQuery query;
            query.exec(querystr);

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
}

void MainWindow::createWidgetProducts(){
    Products=new QWidget;
    QWidget* SettingProducts=new QWidget;
    //SettingProducts->setMinimumWidth(100);


    Products->setStyleSheet("background-color:#4C5866;");
    SettingProducts->setObjectName("sett");

    QString stylefilter="background-color:#292E3D;color:#9aa5b3;";
     SettingProducts->setStyleSheet("#sett{border:2px solid black;"+stylefilter+"}");

    tableview=new QTableView(Products);

    QStringList ls;
    ls<<"Все"<<"Овощи"
    <<"Мясо,копчености"
    <<"Рыбные"
    <<"Зелень"
    <<"Хлеба"
    <<"Молоко,сыры,яйца"
    <<"Крупы"
    <<"Макаронные изделия"
    <<"Соль,сахар,крахмал,сода"
    <<"Масла растительные"
    <<"Алкогольные напитки"
    <<"Безалкогольные напитки и соки";

    listCategory=new QComboBox(SettingProducts);
    listCategory->setStyleSheet(style->getComboBoxStyleSheet());
    listCategory->addItems(ls);

    connect(listCategory,SIGNAL(currentTextChanged(QString)),this,SLOT(ProductsView()));

    QPushButton* button_setcategory=new QPushButton("Применить");
    button_setcategory->setStyleSheet(stylefilter);
    connect(button_setcategory,SIGNAL(clicked()),this,SLOT(ProductsView()));
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

                 tableview->setFont(f);
                 SettingProducts->setFont(f);

                 tableview->resizeRowsToContents();
                 tableview->resizeColumnsToContents();
                 tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
                    tableview->setAlternatingRowColors(true);
                     tableview->setSelectionMode(QAbstractItemView::SingleSelection);


                     QLabel* nameFilter=new QLabel("Фильтр");
                     nameFilter->setAlignment(Qt::AlignCenter);
                     nameFilter->setStyleSheet("font-size:15px;"+stylefilter);

    QVBoxLayout*  layoutsettprod=new QVBoxLayout;
    layoutsettprod->addWidget(nameFilter);
    layoutsettprod->addWidget(new QLabel("Категория:",SettingProducts));
    layoutsettprod->addWidget(listCategory);
    layoutsettprod->addStretch(10);
    layoutsettprod->addWidget(button_setcategory);

    SettingProducts->setLayout(layoutsettprod);

    QHBoxLayout* layoutprod=new QHBoxLayout;
    layoutprod->addWidget(tableview);
    layoutprod->addWidget(SettingProducts);

    Products->setLayout(layoutprod);

}


void MainWindow::TransactionView(){
   QSqlQuery query;
            query.exec("select * from transactions inner join date using(tid);");

            QStandardItemModel *model = new QStandardItemModel;
            QStandardItem *item;

            QStringList horizontalHeader;
               horizontalHeader.append("Номер");
               horizontalHeader.append("Продукты");
               horizontalHeader.append("Кол-во");
               horizontalHeader.append("Дата");

               model->setHorizontalHeaderLabels(horizontalHeader);

               int i=0;
               while (query.next()) {
               //Первый ряд
               item = new QStandardItem(QString::number(query.value(0).toInt()));
               model->setItem(i, 0, item);

               item = new QStandardItem(query.value(2).toString());
               model->setItem(i, 1, item);

               item = new QStandardItem(QString::number(query.value(3).toInt()));
               model->setItem(i, 2, item);

               item = new QStandardItem(query.value(4).toString());
               model->setItem(i, 3, item);
               i++;
      }

             tableviewTrans->setModel(model);

}

void MainWindow::createWidgetTransactions(){
    Tranzactions=new QWidget;
    Tranzactions->setStyleSheet("background-color:#4C5866;");
    tableviewTrans=new QTableView;

    QSqlQuery query;
        query.exec("select tid,name,kol,DATE_FORMAT(date,GET_FORMAT(DATE,'EUR')),time(date) from transactions inner join date using(tid);");

        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
           horizontalHeader.append("Номер");
           horizontalHeader.append("Продукты");
           horizontalHeader.append("Кол-во");
           horizontalHeader.append("Дата");
           horizontalHeader.append("Время");

           model->setHorizontalHeaderLabels(horizontalHeader);

           int i=0;
           while (query.next()) {
           //Первый ряд
           item = new QStandardItem(QString::number(query.value(0).toInt()));
           model->setItem(i, 0, item);

           item = new QStandardItem(query.value(1).toString());
           model->setItem(i, 1, item);

           item = new QStandardItem(QString::number(query.value(2).toInt()));
           model->setItem(i, 2, item);

           item = new QStandardItem(query.value(3).toString());
           model->setItem(i, 3, item);

           item = new QStandardItem(query.value(4).toString());
           model->setItem(i, 4, item);
           i++;
  }

         tableviewTrans->setModel(model);

        tableviewTrans->setStyleSheet(style->getTableViewStyleSheet());
        //tableview->setColumnHidden(0,true);
        tableviewTrans->setColumnWidth(1,250);


                tableviewTrans->setFont(f);
              //  tableview->resizeRowsToContents();
               // tableview->resizeColumnsToContents();
                tableviewTrans->setEditTriggers(QAbstractItemView::NoEditTriggers);


       // tableview->resize();
       // tableview->setStyleSheet(style->getTableViewStyleSheet());

    QHBoxLayout* layout=new QHBoxLayout;
    layout->addWidget(tableviewTrans);

    Tranzactions->setLayout(layout);

}

void MainWindow::createTabWidgetRules(){
    tabRules=new QTabWidget;

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
     rules->setMaxSup(10);
     rules->setMinConf(0);
     rules->setMaxConf(100);
     rules->CreateRules();
     //rules->setTable();

       tabRules->addTab(rules->getTableRyles(),"Test Rules Table");
        tabRules->addTab(rules->getTextRyles(),"Test Rules Text");
        tabRules->addTab(rules->getTextRyles(),"Test Rules Tree");


}

void MainWindow::createWidgetDiagram(){
    Diagram=new QWidget;
    Diagram->setStyleSheet("background-color:#4C5866;");

    QSqlQuery query;
        query.exec("select month(date),count(tid) from date group by month(date);");

    double a = 1; //Начало интервала, где рисуем график по оси Ox
       double b =  13; //Конец интервала, где рисуем график по оси Ox
       double h = 1; //Шаг, с которым будем пробегать по оси Ox

       double N=(b-a)/h + 2;
       QVector<double> x(N), y(N);
       int i=0;
       while (query.next()) {
           x[i] = query.value(0).toDouble();
           y[i] =query.value(1).toDouble();
           i++;
       }

    customplot = new QCustomPlot;


    customplot->addGraph();

  //  customplot->graph(0)->setData(x,y);
    customplot->graph(0)->setLineStyle(QCPGraph::lsImpulse);



    customplot->xAxis->setRange(a,b);
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 <<10 <<11<<12;
    labels <<"Январь"
           <<"Февраль"
           <<"Март"
           <<"Апрель"
           <<"Май"
           <<"Июнь"
           <<"Июль"
           <<"Август"
           <<"Сентябрь"
           <<"Октябрь"
           <<"Ноябрь"
           <<"Декабрь";
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    customplot->xAxis->setTicker(textTicker);


    double minY = y[0], maxY = y[0];
        for (int i=1; i<N; i++)
        {
            if (y[i]<minY) minY = y[i];
            if (y[i]>maxY) maxY = y[i];
        }


    customplot->yAxis->setRange(minY, maxY+2);

    QCPBars *bars1 = new QCPBars(customplot->xAxis, customplot->yAxis);
    bars1->setData(x, y);
    bars1->setWidth(9/(double)x.size());
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(69, 71, 232));

    customplot->xAxis->setLabel("Месяцы\n2017");
    customplot->yAxis->setLabel("Кол-во чеков");
    customplot->xAxis->setRangeUpper(13);
    customplot->xAxis->setRangeLower(0);

   // customplot->yAxis->setRangeUpper(maxY+200);
    //customplot->yAxis->setRangeUpper(maxY);

  // customplot->xAxis->setSelectableParts(QCPAxis::spAxis|QCPAxis::spTickLabels);


    /*customplot->xAxis->setBasePen(QPen(Qt::white, 1));
    customplot->yAxis->setBasePen(QPen(Qt::white, 1));
    customplot->xAxis->setTickPen(QPen(Qt::white, 1));
    customplot->yAxis->setTickPen(QPen(Qt::white, 1));
    customplot->xAxis->setSubTickPen(QPen(Qt::white, 1));
    customplot->yAxis->setSubTickPen(QPen(Qt::white, 1));
    customplot->xAxis->setTickLabelColor(Qt::white);
    customplot->yAxis->setTickLabelColor(Qt::white);
    customplot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customplot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    customplot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customplot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    customplot->xAxis->grid()->setSubGridVisible(true);
    customplot->yAxis->grid()->setSubGridVisible(true);
    customplot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
    customplot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
    customplot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    customplot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(80, 80, 80));
    plotGradient.setColorAt(1, QColor(50, 50, 50));
    customplot->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(80, 80, 80));
    axisRectGradient.setColorAt(1, QColor(30, 30, 30));
    customplot->axisRect()->setBackground(axisRectGradient);*/

   //customplot->rescaleAxes();
  //  customplot->yAxis->setTickLength(1);
    customplot->replot();

    //customplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);

    QWidget* choiseGraph=new QWidget;

    QLabel* namegraph=new QLabel("График:");


    QHBoxLayout* hbox=new QHBoxLayout;
    hbox->addWidget(namegraph);


    choiseGraph->setStyleSheet("background-color:white;");
    choiseGraph->setMaximumHeight(50);
    choiseGraph->setLayout(hbox);


    QVBoxLayout* layout=new QVBoxLayout;
    layout->addWidget(choiseGraph);
    layout->addWidget(customplot);

    Diagram->setLayout(layout);

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


void MainWindow::openItem(QListWidgetItem * item){

    if(item->text()==isOpenItem){
        return;
    }


    if(item->text()=="Главная"){//"Продукты"
        isOpenItem="Главная";
      mainGbox->itemAt(prevopen)->widget()->setHidden(true);
     welcome->setHidden(false);
     prevopen=1;
    }else
    if(item->text()=="Продукты"){//"Продукты"
        isOpenItem="Продукты";
      mainGbox->itemAt(prevopen)->widget()->setHidden(true);
     Products->setHidden(false);
     prevopen=2;
    }else
        if(item->text()=="Транзакции"){//"Транзакции"
            isOpenItem="Транзакции";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
           Tranzactions->setHidden(false);
           prevopen=3;

    }else
        if(item->text()=="Анализ корзины"){//"Анализ корзины"
            /*isOpenItem="Анализ корзины";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
           //Tranzactions->setHidden(false);
           prevopen=4;*/
    }else
        if(item->text()=="Поиск шаболных покупок"){//"Поиск шаболных покупок"
            isOpenItem="Поиск шаболных покупок";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
           tabRules->setHidden(false);
           prevopen=4;
    }else
        if(item->text()=="Аналитика"){//"Диаграммы"
            isOpenItem="Аналитика";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
           Diagram->setHidden(false);
           prevopen=5;
    }/*else
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
