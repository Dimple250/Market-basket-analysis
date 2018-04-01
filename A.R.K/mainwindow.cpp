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


    database=new Database;
    database->Connect("market");
    style=new Style;
    treeviewleft=new QListWidget;
    csvModel = new QStandardItemModel;
    SalesAnalysis salesAnalysis;

    createWidgetProducts();
    createWidgetTransactions();
    createTabWidgetRules();
    createWidgetDiagram();
    createWidgetAnalis();
    createWidgetSclad();


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
     list<<"Главная"<<"Товары"<<"Транзакции"<<"Анализ корзины"<<"Поиск шаболных покупок"<<"Аналитика"<<"Загрузить файл";

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
     welcome=new QLabel("Добро пожаловать\n ");
     welcome->setStyleSheet("font-size:50px;padding-top:-400%;padding-left:300%;background-color:#4C5866;padding-right:300%;color:white;");

         treeviewleft->setFont(f);

     mainGbox=new QGridLayout;
     mainGbox->addWidget(treeviewleft,0,0);
     mainGbox->setSpacing(5);
     mainGbox->addWidget(welcome,0,1);
     mainGbox->addWidget(Products,0,1);
     mainGbox->addWidget(Tranzactions,0,1);
     mainGbox->addWidget(Analis,0,1);
     mainGbox->addWidget(tabRules,0,1);
     mainGbox->addWidget(Diagram,0,1);
     mainGbox->addWidget(Sclad,0,1);
     prevopen=1;

     Products->setHidden(true);
     Tranzactions->setHidden(true);
     Analis->setHidden(true);
     tabRules->setHidden(true);
     Diagram->setHidden(true);
     Sclad->setHidden(true);


     ui->centralwidget->setLayout(mainGbox);

     SalesAnalysis ss;
     QLabel* lb=new QLabel(ss.getZnach());
     //lb.setText();
    // lb->show();
     //Kagle


}

void MainWindow::changeProductsView(){
    QString category="";
    QString querystr="";
    if(listCategory.currentIndex()==0){
        querystr="select category.name,products.name,price from products inner join category using(idcat);";
    }else{
        category=listCategory.currentText();
        querystr="select category.name,products.name,price from products inner join category using(idcat) where category.name like '"+category+"';";
    }
            tableview->setModel(database->getModelProducts(querystr));
}


void MainWindow::createWidgetProducts(){
    Products=new QWidget;



    tableview=new QTableView(Products);

    QWidget* FilterProductsView=new QWidget;
    //SettingProducts->setMinimumWidth(100);
    QPalette Pal(palette());

    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background,"#4C5866");
     Products->setAutoFillBackground(true);
   Products->setPalette(Pal);


   // SettingProducts->setObjectName("sett");

    //QString stylefilter="background-color:#292E3D;color:#9aa5b3;";
     //SettingProducts->setStyleSheet("margin-top:-10px;");

        Pal.setColor(QPalette::Background,"#647387");
         FilterProductsView->setAutoFillBackground(true);
        FilterProductsView->setPalette(Pal);

    QStringList ls;

    QSqlQuery categoryName;
        categoryName.exec("select category.name from category;");

         ls<<"Все";
    while (categoryName.next()){
        ls<<categoryName.value(0).toString();
    }

    listCategory;// (FilterProductsView);
    listCategory.setStyleSheet(style->getComboBoxStyleSheet());
    listCategory.addItems(ls);

    connect(&listCategory,SIGNAL(currentTextChanged(QString)),this,SLOT(changeProductsView()));

    QPushButton* button_setcategory=new QPushButton("Применить");
    //button_setcategory->setStyleSheet(stylefilter);
    connect(button_setcategory,SIGNAL(clicked()),this,SLOT(changeProductsView()));

        QLabel* nameFilter=new QLabel("Фильтр");
        nameFilter->setAlignment(Qt::AlignCenter);
        nameFilter->setStyleSheet("font-size:15px;color:white;");

        QLabel* lb2=new QLabel("Категория:");
        lb2->setStyleSheet("font-size:15px;color:white;");

    QVBoxLayout*  layoutsettprod=new QVBoxLayout;
    layoutsettprod->addWidget(nameFilter);
    layoutsettprod->addWidget(lb2);
    layoutsettprod->addWidget(&listCategory);
    layoutsettprod->addStretch(10);
    layoutsettprod->addWidget(button_setcategory);

   FilterProductsView->setLayout(layoutsettprod);



           tableview->setModel(database->getModelProducts("select category.name,products.name,price,kol_on_sclad from products inner join category using(idcat);"));

        tableview->setStyleSheet(style->getTableViewStyleSheet());
        tableview->setColumnHidden(0,true);

                 tableview->setFont(f);
                 FilterProductsView->setFont(f);

                 tableview->resizeRowsToContents();
                 tableview->resizeColumnsToContents();
                tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);
                    tableview->setAlternatingRowColors(true);
                     tableview->setSelectionMode(QAbstractItemView::SingleSelection);

                     tableview->setColumnWidth(1,250);
                     tableview->setColumnWidth(2,250);
                    // tableview->s;
                    // tableview->set




    QHBoxLayout* layoutprod=new QHBoxLayout;
    layoutprod->addWidget(tableview);
    layoutprod->addWidget(FilterProductsView);
   // layoutprod->setMargin(0);

    Products->setLayout(layoutprod);
    FilterProductsView->setMinimumWidth(Products->width()*0.45);

}

void MainWindow::changeTransactionsView(){
    QString product="";
    QString tid="";
    QString querystr;
   if(namepProducts.text()==""){
       querystr="select tid,name,kol,DATE_FORMAT(date,GET_FORMAT(DATE,'EUR')),time(date) from transactions inner join date using(tid) order by tid;";
    }else{
        product=namepProducts.text();

        QSqlQuery productsName;
            productsName.exec("select tid from transactions where name like '"+product+"';");
           // qDebug()<<product;

        while (productsName.next()){
            tid+="tid="+productsName.value(0).toString()+" or ";
           // qDebug()<<productsName.value(0).toString();
        }
        tid=tid.remove(tid.length()-3,tid.length()-1);

        querystr="select tid,name,kol,DATE_FORMAT(date,GET_FORMAT(DATE,'EUR')),time(date) from transactions inner join date using(tid) where "+tid+" order by tid;";
    //qDebug()<<querystr;
   }

            tableviewTrans->clearSpans();
            tableviewTrans->setModel(database->getModelTransactions(querystr));

            for(int i=0;i<tableviewTrans->model()->rowCount();i++){
                QString number=tableviewTrans->model()->data(tableviewTrans->model()->index(i,0)).toString();
                if(number.contains( "Транзакция №", Qt::CaseInsensitive)){
               tableviewTrans->setSpan(i,0,1,5);
               const QModelIndex index =tableviewTrans->model()->index(i,0);
               tableviewTrans->model()->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
                }
            }
}

void MainWindow::createWidgetTransactions(){
    Tranzactions=new QWidget;
   // Tranzactions->setStyleSheet("background-color:#4C5866;");
    QPalette Pal(palette());

    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background,"#4C5866");
     Tranzactions->setAutoFillBackground(true);
  Tranzactions->setPalette(Pal);


  tableviewTrans=new QTableView;
  tableviewTrans->setModel(database->getModelTransactions("select tid,name,kol,DATE_FORMAT(date,GET_FORMAT(DATE,'EUR')),time(date) from transactions inner join date using(tid) order by tid;"));

    tableviewTrans->setStyleSheet(style->getTableViewStyleSheet());
        //tableview->setColumnHidden(0,true);
    tableviewTrans->setColumnWidth(0,250);

   for(int i=0;i<tableviewTrans->model()->rowCount();i++){
       QString number=tableviewTrans->model()->data(tableviewTrans->model()->index(i,0)).toString();
       if(number.contains( "Транзакция №", Qt::CaseInsensitive)){
    tableviewTrans->setSpan(i,0,1,5);
    const QModelIndex index =tableviewTrans->model()->index(i,0);
    tableviewTrans->model()->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
       }
   }


    tableviewTrans->setFont(f);
              //  tableview->resizeRowsToContents();
               // tableview->resizeColumnsToContents();
    tableviewTrans->setEditTriggers(QAbstractItemView::NoEditTriggers);


       // tableview->resize();
 // tableview->setStyleSheet(style->getTableViewStyleSheet());


    QWidget* FilterTransactionsView=new QWidget;

        Pal.setColor(QPalette::Background,"#647387");
         FilterTransactionsView->setAutoFillBackground(true);
        FilterTransactionsView->setPalette(Pal);
        FilterTransactionsView->setFont(f);

    /*QStringList ls;

    QSqlQuery productsName;
        productsName.exec("select name from products;");
        listproducts.view()->setMaximumHeight(100);

         ls<<"Все";
    while (productsName.next()){
        ls<<productsName.value(0).toString();
    }

   // listproducts.setStyleSheet(style->getComboBoxStyleSheet());
    listproducts.addItems(ls);*/

   // namepProducts.setMaximumWidth(100);

    //connect(&listproducts,SIGNAL(currentTextChanged(QString)),this,SLOT(changeTransactionsView()));

    QPushButton* button_setcategory=new QPushButton("Применить");
    //button_setcategory->setStyleSheet(stylefilter);
    connect(button_setcategory,SIGNAL(clicked()),this,SLOT(changeTransactionsView()));

        QLabel* nameFilter=new QLabel("Фильтр");
        nameFilter->setAlignment(Qt::AlignCenter);
        nameFilter->setStyleSheet("font-size:15px;color:white;");

        QLabel* lb2=new QLabel("Продукты:");
        lb2->setStyleSheet("font-size:15px;color:white;");

    QVBoxLayout*  layoutsettrans=new QVBoxLayout;
    layoutsettrans->addWidget(nameFilter);
    layoutsettrans->addWidget(lb2);
    layoutsettrans->addWidget(&namepProducts);
    layoutsettrans->addStretch(10);
    layoutsettrans->addWidget(button_setcategory);

   FilterTransactionsView->setLayout(layoutsettrans);

    QHBoxLayout* layout=new QHBoxLayout;
    layout->addWidget(tableviewTrans);
    layout->addWidget(FilterTransactionsView);

    Tranzactions->setLayout(layout);
    FilterTransactionsView->setMaximumWidth(Tranzactions->width()*0.45);

}

void MainWindow::changeAnalisProdycts(){

    salesTableView->setModel(salesAnalysis.getModelSales(namepProducts.text()));

    salesTableView->resizeRowsToContents();
    salesTableView->resizeColumnsToContents();

    ostatkiTableView->setModel(salesAnalysis.getModelOstatki(namepProducts.text(),inMonth.currentText().toInt()));

    ostatkiTableView->resizeRowsToContents();
    ostatkiTableView->resizeColumnsToContents();

    QString month="";
    int flagMonth=0;

    for(int i=0;i<ostatkiTableView->model()->columnCount();i++){
        int number=ostatkiTableView->model()->data(ostatkiTableView->model()->index(0,i)).toInt();
        if(number<0){
            if(flagMonth==0){

             //   month=horizontalHeader.at(i);
                flagMonth=1;
            }
       const QModelIndex index =ostatkiTableView->model()->index(0,i);
       ostatkiTableView->model()->setData(index,QColor("#FF0F12"),Qt::TextColorRole);
        }
    }
}

void MainWindow::createWidgetAnalis(){
    Analis=new QWidget;
  // Analis->setStyleSheet("background-color:#4C5866;");
   QPalette Pal(palette());

   // устанавливаем цвет фона
   Pal.setColor(QPalette::Background,"#4C5866");
     Analis->setAutoFillBackground(true);
  Analis->setPalette(Pal);

  for(int i=1;i<=12;i++){
      inMonth.addItem(QString::number(i));
  }

  QLabel* label=new QLabel("Продукты:");
  label->setStyleSheet("font-size:15px;color:white;");

  QLabel* label2=new QLabel("Кол-во месяцев:");
  label2->setStyleSheet("font-size:15px;color:white;");

  QPushButton* settingName=new QPushButton("Применить");
    connect(settingName,SIGNAL(clicked(bool)),SLOT(changeAnalisProdycts()));

   QHBoxLayout* HBox=new QHBoxLayout;
   HBox->addWidget(label);
   HBox->addWidget(&namepProducts);
   HBox->addWidget(label2);
   HBox->addWidget(&inMonth);
   HBox->addWidget(settingName);
   HBox->addStretch(9);

   QString tovar="";

   int kol_month=12;

    salesTableView=new QTableView;

   // salesTableView->setModel(salesAnalysis.getModelSales(tovar));
    salesTableView->setStyleSheet(style->getTableViewStyleSheet());
    salesTableView->setFont(f);
    salesTableView->resizeRowsToContents();
    salesTableView->resizeColumnsToContents();
    salesTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    salesTableView->setAlternatingRowColors(true);
    salesTableView->setSelectionMode(QAbstractItemView::SingleSelection);


    ostatkiTableView=new QTableView;

   // ostatkiTableView->setModel(salesAnalysis.getModelOstatki(tovar,inMonth.currentText().toInt()));
    ostatkiTableView->setStyleSheet(style->getTableViewStyleSheet());
    ostatkiTableView->setFont(f);
    ostatkiTableView->resizeRowsToContents();
    ostatkiTableView->resizeColumnsToContents();
    ostatkiTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ostatkiTableView->setAlternatingRowColors(true);
    ostatkiTableView->setSelectionMode(QAbstractItemView::SingleSelection);

        QString month="";
        int flagMonth=0;

        /*for(int i=0;i<ostatkiTableView->model()->columnCount();i++){
            int number=ostatkiTableView->model()->data(ostatkiTableView->model()->index(0,i)).toInt();
            if(number<0){
                if(flagMonth==0){

                 //   month=horizontalHeader.at(i);
                    flagMonth=1;
                }
           const QModelIndex index =ostatkiTableView->model()->index(0,i);
           ostatkiTableView->model()->setData(index,QColor("#FF0F12"),Qt::TextColorRole);
            }
        }*/

        QLabel* lb=new QLabel("Продажи за 2018");
        lb->setStyleSheet("color:white;font-size:23px;");

        QLabel* lb2=new QLabel("Остатки на конец периода");
        lb2->setStyleSheet("color:white;font-size:23px;");

        QLabel* lb3=new QLabel("Товар "+tovar+" закончится на складе в месяце "+month);
        lb3->setStyleSheet("color:white;font-size:23px;");

        QPushButton* prodazaOstatcov=new QPushButton("Расчет продажи остатков");
       // prodazaOstatcov->setFixedWidth(200);
        QPushButton* kolProdaz=new QPushButton("Расчет объема продаж");
       //  kolProdaz->setFixedWidth(200);

        QHBoxLayout* Hbox=new QHBoxLayout;
        //Hbox->addSpacing(400);
        Hbox->addWidget(prodazaOstatcov);
        Hbox->addWidget(kolProdaz);
      //  Hbox->addSpacing(400);


    QVBoxLayout* layout=new QVBoxLayout;
    layout->addLayout(HBox);
    layout->addWidget(lb);
    layout->addWidget(salesTableView);
    layout->addWidget(lb2);
    layout->addWidget(ostatkiTableView);
    //layout->addWidget(lb3);
    layout->addStretch(10);

    Analis->setLayout(layout);
}

void MainWindow::createTabWidgetRules(){
    tabRules=new QTabWidget;
    QWidget* settingRules=new QWidget;

    QPalette Pal(palette());

    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background,"#4C5866");
     settingRules->setAutoFillBackground(true);
    settingRules->setPalette(Pal);

    QWidget* setting=new QWidget;

    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background, Qt::white);
     setting->setAutoFillBackground(true);
    setting->setPalette(Pal);
    setting->setMaximumWidth(400);

    QVBoxLayout* layout=new QVBoxLayout;

    QLabel* minsup=new QLabel("Минимальная поддержка %:");

    QLabel* maxsup=new QLabel("Максимальная поддержка %:");

    QLabel* minconf=new QLabel("Минимальная достоверность %:");

    QLabel* maxconf=new QLabel("Максимальная достоверность %:");

    QPushButton* button_setttules=new QPushButton("Поиск");
    connect(button_setttules,SIGNAL(clicked()),this,SLOT(createRules()));

    layout->addWidget(minsup);
    layout->addWidget(&minsupline);
    layout->addWidget(maxsup);
    layout->addWidget(&maxsupline);
    layout->addWidget(minconf);
    layout->addWidget(&minconfline);
    layout->addWidget(maxconf);
    layout->addWidget(&maxconfline);
    layout->addStretch(10);
    layout->addWidget(button_setttules);

    setting->setLayout(layout);

    QHBoxLayout* hbox=new QHBoxLayout;
    hbox->addWidget(setting);

    settingRules->setLayout(hbox);

    tabRules->addTab(settingRules,"Настройка");


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
    tabRules->removeTab(1);
    tabRules->removeTab(1);
    tabRules->removeTab(1);


     AssociationRules* rules=new AssociationRules;
     rules->setMinSup(minsupline.text().toInt());
     rules->setMaxSup(maxsupline.text().toInt());
     rules->setMinConf(minconfline.text().toInt());
     rules->setMaxConf(maxconfline.text().toInt());
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
        query.exec("select month(date),count(tid) from date where year(date)=2017 group by month(date);");

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

    //средняя цена чека на месяц
    //select month(date),sum(price*kol)/count(distinct tid) from transactions as t1 inner join products using(id) inner join date using(tid) where year(date)=2018 group by month(date);

    //объем продаж за месяц в гривнах
    //select month(date),sum(price*kol) from transactions as t1 inner join products using(id) inner join date using(tid) where year(date)=2018 group by month(date);


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

    QPushButton* settgraph=new QPushButton("Настрйки");
   settgraph->setStyleSheet("background-color:#4547E8;color:white;");
   // settgraph->setPalette(QColor(69, 71, 232));
    settgraph->setMaximumWidth(100);

    QHBoxLayout* hbox=new QHBoxLayout;
    hbox->addWidget(namegraph);
    hbox->addSpacing(100);
    hbox->addWidget(settgraph);


    choiseGraph->setStyleSheet("background-color:white;");
    choiseGraph->setMaximumHeight(50);
    choiseGraph->setLayout(hbox);


    QVBoxLayout* layout=new QVBoxLayout;
    layout->addWidget(choiseGraph);
    layout->addWidget(customplot);

    Diagram->setLayout(layout);

}

void MainWindow::createWidgetSclad(){
    Sclad=new QWidget;
   Sclad->setStyleSheet("background-color:#4C5866;");


    QVBoxLayout* layout=new QVBoxLayout;
   // layout->addWidget();

    Sclad->setLayout(layout);
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
    if(item->text()=="Товары"){//"Продукты"
        isOpenItem="Товары";
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
            isOpenItem="Анализ корзины";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
           Analis->setHidden(false);
           prevopen=4;
    }else
        if(item->text()=="Поиск шаболных покупок"){//"Поиск шаболных покупок"
            isOpenItem="Поиск шаболных покупок";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
           tabRules->setHidden(false);
           prevopen=5;
    }else
        if(item->text()=="Аналитика"){//"Диаграммы"
            isOpenItem="Аналитика";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
           Diagram->setHidden(false);
           prevopen=6;
    }else
        if(item->text()=="Склад"){//"Склад"
            isOpenItem="Склад";
            mainGbox->itemAt(prevopen)->widget()->setHidden(true);
           Sclad->setHidden(false);
           prevopen=7;
    }

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
    /*delete tableview;
    delete tableviewTrans;
    delete treeviewleft;
    delete tabRules;
    delete database;
    delete style;
    delete csvModel;
    delete mainGbox;
    delete  welcome;

    delete customplot;

    delete listCategory;

    delete Products;
    delete Tranzactions;
    delete Diagram;*/
}
