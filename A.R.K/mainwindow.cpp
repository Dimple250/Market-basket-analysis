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

    customplot=new QCustomPlot;
    customplot1=new QCustomPlot;
    customplot2=new QCustomPlot;


    createWidgetProducts();
    createWidgetTransactions();
    createTabWidgetRules();
    createWidgetDiagram();
    createWidgetAnalis();

   /* QMenu*  menu_file=new QMenu("&File");
    menu_file->addAction("Open",this,SLOT(OpenCSVFile()));
    //menu_file->addAction("Save",this,SLOT(SaveFile()));
    menu_file->addSeparator();
    menu_file->addAction("Exit",this,SLOT(close()));

   // QMenu*  menu_analiz=new QMenu("&Analysis");
    //menu_file->addAction("Open",this,SLOT(OpenCSVFile()));*/
   // QMenu*  menu_rules=new QMenu("&Rules");
   // menu_rules->addAction("Create",this,SLOT(createRules()));

   // ui->menubar->addMenu(menu_rules);



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
    //Rules->setStyleSheet(style->getTabWidgetStyleSheet());
  //  addData->setStyleSheet(style->getAddDataButtonStyleSheet());



   // connect(tabRules,SIGNAL(tabCloseRequested(int)),SLOT(closeTab(int)));
    connect(treeviewleft,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(openItem(QListWidgetItem*)));



    treeviewleft->setStyleSheet(style->getTreeviewleftStyleSheet());
    QListWidgetItem* item;

    QStringList list;
    list<<"Товары"<<"Транзакции"<<"Анализ корзины"<<"Поиск шаболных покупок"<<"Аналитика"<<"О программе";//<<"Загрузить файл";

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
    mainGbox->addWidget(scrollAreaAnalis,0,1);
    mainGbox->addWidget(Rules,0,1);
    mainGbox->addWidget(Diagram,0,1);
    prevopen=3;

    welcome->setHidden(true);
    Products->setHidden(true);
    //Tranzactions->setHidden(true);
    scrollAreaAnalis->setHidden(true);
    Rules->setHidden(true);
    Diagram->setHidden(true);

    ui->centralwidget->setLayout(mainGbox);

}

void MainWindow::changeProductsView(){
    QString category="";
    QString querystr="";
    if(listCategory.currentIndex()==0){
        querystr="select category.name,products.name,price,kol_on_sclad from products inner join category using(idcat);";
    }else{
        category=listCategory.currentText();
        querystr="select category.name,products.name,price,kol_on_sclad from products inner join category using(idcat) where category.name like '"+category+"';";
    }
    tableview->setModel(database->getModelProducts(querystr));
}


void MainWindow::createWidgetProducts(){
    Products=new QWidget;

    tableview=new QTableView(Products);
  // tableview->setSortingEnabled(true);
   // tableview->sortByColumn(2, Qt::DescendingOrder);

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

    //listCategory;// (FilterProductsView);
    listCategory.setStyleSheet(style->getComboBoxStyleSheet());
    listCategory.addItems(ls);

    connect(&listCategory,SIGNAL(currentTextChanged(QString)),this,SLOT(changeProductsView()));

    QPushButton* button_setcategory=new QPushButton("Применить");
    //button_setcategory->setStyleSheet(stylefilter);
    connect(button_setcategory,SIGNAL(clicked()),this,SLOT(changeProductsView()));

    QLabel* nameFilter=new QLabel("Фильтр");
    nameFilter->setAlignment(Qt::AlignCenter);
    nameFilter->setStyleSheet("font-size:17px;color:white;");

    QLabel* lb2=new QLabel("Категория:");
    lb2->setStyleSheet("font-size:17px;color:white;");

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
    tableview->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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

    QString fdate=fromDate.date().toString("yyyy-MM-dd");
    QString tdate=toDate.date().toString("yyyy-MM-dd");

    QString ftime=fromTime.time().toString();
    QString ttime=toTime.time().toString();


   if(namepProducts.text()==""){
       querystr="select tid,products.name,kol,DATE_FORMAT(date,GET_FORMAT(DATE,'EUR')),time(date) from transactions inner join date using(tid) inner join products using(id) where date(date) between '"+fdate+"' and '"+tdate+"' and time(date)>='"+ftime+"' and time(date)<='"+ttime+"' order by tid;";
   }else{
        product=namepProducts.text();

        QSqlQuery productsName;
            productsName.exec("select tid from transactions where name like '"+product+"';");

        while (productsName.next()){
            tid+="tid="+productsName.value(0).toString()+" or ";
        }
        tid=tid.remove(tid.length()-3,tid.length()-1);

        querystr="select tid,products.name,kol,DATE_FORMAT(date,GET_FORMAT(DATE,'EUR')),time(date) from transactions inner join date using(tid) inner join products using(id) where "+tid+" and date(date) between '"+fdate+"' and '"+tdate+"' and time(date)>='"+ftime+"' and time(date)<='"+ttime+"' order by tid;";
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
   // Tranzactions->setStyleSheet("padding-left:10%;");//("background-color:#4C5866;");
    QPalette Pal(palette());

    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background,"#4C5866");
    Tranzactions->setAutoFillBackground(true);
    Tranzactions->setPalette(Pal);

    tableviewTrans=new QTableView;
    tableviewTrans->setModel(database->getModelTransactions("select tid,products.name,kol,DATE_FORMAT(date,GET_FORMAT(DATE,'EUR')),time(date) from transactions inner join date using(tid) inner join products using(id) order by tid;"));

    tableviewTrans->setStyleSheet(style->getTableViewStyleSheet()+"QTableView{margin-left:30%;}");
        //tableview->setColumnHidden(0,true);
    tableviewTrans->setColumnWidth(0,250);
    //tableviewTrans->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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
        nameFilter->setStyleSheet("font-size:17px;color:white;");

        QLabel* lb2=new QLabel("Продукты:");
        lb2->setStyleSheet("font-size:17px;color:white;");

       // toDate=new QDateEdit;
        toDate.setDisplayFormat("dd-MMM-yyyy");
        toDate.setCalendarPopup(true);

        //fromDate=new QDateEdit;
        fromDate.setDisplayFormat("dd-MMM-yyyy");
        fromDate.setCalendarPopup(true);

        QLabel* lb3=new QLabel("За период от:");
        lb3->setStyleSheet("font-size:17px;color:white;");

        QLabel* lb5=new QLabel("-");
        lb5->setStyleSheet("font-size:25px;color:white;");

        //toTime=new QTimeEdit;
        //fromTime=new QTimeEdit;

        QLabel* lb6=new QLabel("Временой промежуток:");
        lb6->setStyleSheet("font-size:17px;color:white;");

        QLabel* lb8=new QLabel(":");
        lb8->setStyleSheet("font-size:20px;color:white;");


        QHBoxLayout* layoutDate=new QHBoxLayout;
        layoutDate->addWidget(&fromDate);
        layoutDate->addWidget(lb5);
        layoutDate->addWidget(&toDate);
        layoutDate->addStretch(1);

        QHBoxLayout* layoutMonth=new QHBoxLayout;
        layoutMonth->addWidget(&fromTime);
        layoutMonth->addWidget(lb8);
        layoutMonth->addWidget(&toTime);
        layoutMonth->addStretch(1);


    QVBoxLayout*  layoutsettrans=new QVBoxLayout;
    layoutsettrans->addWidget(nameFilter);
    layoutsettrans->addWidget(lb2);
    layoutsettrans->addWidget(&namepProducts);
    layoutsettrans->addWidget(lb3);
    layoutsettrans->addLayout(layoutDate);
    layoutsettrans->addWidget(lb6);
    layoutsettrans->addLayout(layoutMonth);
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
    boxTovar->clear();
    boxTovar->addItem(namepSalesProducts.text());

    salesTableView->setModel(salesAnalysis.getModelSales(boxTovar));

    for(int i=0;i<salesTableView->verticalHeader()->count();i++){
        for(int j=0;j<salesTableView->horizontalHeader()->count();j++){
            const QModelIndex index = salesTableView->model()->index(i,j);
               salesTableView->model()->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
        }
    }


   //salesTableView->resize(salesTableView->width(),boxTovar->count()*100);

    ostatkiTableView->setModel(salesAnalysis.getModelOstatki(boxTovar,inMonth.currentText().toInt()));

    for(int i=0;i<ostatkiTableView->verticalHeader()->count();i++){
        for(int j=0;j<ostatkiTableView->horizontalHeader()->count();j++){
            const QModelIndex index = ostatkiTableView->model()->index(i,j);
               ostatkiTableView->model()->setData(index, Qt::AlignCenter, Qt::TextAlignmentRole);
        }
    }


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
    scrollAreaAnalis = new QScrollArea;
  // Analis->setStyleSheet("background-color:#4C5866;");
    QPalette Pal(palette());

   // устанавливаем цвет фона
    Pal.setColor(QPalette::Background,"#4C5866");
    Analis->setAutoFillBackground(true);
    Analis->setPalette(Pal);
    scrollAreaAnalis->setPalette(Pal);

    for(int i=1;i<=12;i++){
        inMonth.addItem(QString::number(i));
    }


    QString tovar="";

   //int kol_month=12;

    salesTableView=new QTableView;

   // salesTableView->setModel(salesAnalysis.getModelSales(tovar));
    salesTableView->setStyleSheet(style->getTableViewStyleSheet());
    salesTableView->setFont(f);
  //  salesTableView->resizeRowsToContents();
   // salesTableView->resizeColumnsToContents();
    //salesTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //salesTableView->setAlternatingRowColors(true);
    //salesTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    salesTableView->setMaximumHeight(60);

    ostatkiTableView=new QTableView;

   // ostatkiTableView->setModel(salesAnalysis.getModelOstatki(tovar,inMonth.currentText().toInt()));
    ostatkiTableView->setStyleSheet("QTableView{border: 0px solid white;background-color:#4C5866;font-size:17px;}"
                                    "QTableView::item{border:0px solid white;background-color:white;}"
                                    "QTableView QHeaderView{font-size:17px;background-color:#4C5866;}");
    ostatkiTableView->setFont(f);
    ostatkiTableView->resizeRowsToContents();
    ostatkiTableView->resizeColumnsToContents();
    ostatkiTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ostatkiTableView->setAlternatingRowColors(true);
    ostatkiTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ostatkiTableView->setMaximumHeight(60);

    QString month="";
        //int flagMonth=0;

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
    QLabel* label=new QLabel("Товары:");
    label->setStyleSheet("font-size:20px;color:white;");

    QLabel* label2=new QLabel("Прогноз на кол-во месяцев:");
    label2->setStyleSheet("font-size:20px;color:white;");

    QPushButton* settingName=new QPushButton("Применить");
    connect(settingName,SIGNAL(clicked(bool)),SLOT(changeAnalisProdycts()));


    //QComboBox* cbox=new QComboBox;



    QSqlQuery* query2=new QSqlQuery();
    query2->exec("select name from products;");

    QListWidget* list=new QListWidget;
    while(query2->next()){
    list->addItem(query2->value(0).toString());
    //cbox->addItem(query2->value(0).toString());
    }

    QCompleter* completer = new QCompleter( this );
    completer->setModel(list->model());
    completer->setCaseSensitivity( Qt::CaseInsensitive );

    namepSalesProducts.setCompleter(completer);

    //cbox->setCompleter(completer);
    //cbox->setMaxVisibleItems(3);
    //completer->setCaseSensitivity(Qt::CaseInsensitive);
    //completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);

    QLabel* lbTovaru=new QLabel("Выбранные товары:");
    lbTovaru->setStyleSheet("color:white;font-size:20px;");

    QPushButton* delProduct=new QPushButton("Удалить");
    connect(delProduct,SIGNAL(clicked(bool)),SLOT(delTovar()));

    boxTovar=new QComboBox;
    boxTovar->setMinimumWidth(100);


    QPushButton* addProduct=new QPushButton("Добавить");
    connect(addProduct,SIGNAL(clicked(bool)),SLOT(addTovar()));

    QHBoxLayout* HBox=new QHBoxLayout;
    HBox->addWidget(label);
    HBox->addWidget(&namepSalesProducts);
    //HBox->addWidget(addProduct);
    //HBox->addWidget(lbTovaru);
    //HBox->addWidget(boxTovar);
    //HBox->addWidget(delProduct);
    HBox->addStretch(1);

    QHBoxLayout* kolPrognoz=new QHBoxLayout;
    kolPrognoz->addWidget(label2);
    kolPrognoz->addWidget(&inMonth);
    kolPrognoz->addWidget(settingName);
    kolPrognoz->addStretch(1);


    QLabel* lb=new QLabel("Продажи за текущий год");
    lb->setStyleSheet("color:white;font-size:20px;");

    QLabel* lb2=new QLabel("Прогноз объема продаж на следующие месяцы");
    lb2->setStyleSheet("color:white;font-size:20px;");

    QLabel* lb3=new QLabel("Товар "+tovar+" закончится на складе в месяце "+month);
    lb3->setStyleSheet("color:white;font-size:20px;");

    QPushButton* prodazaOstatcov=new QPushButton("Расчет продажи остатков");
       // prodazaOstatcov->setFixedWidth(200);
    QPushButton* kolProdaz=new QPushButton("Расчет объема продаж");
       //  kolProdaz->setFixedWidth(200);

    QHBoxLayout* Hbox=new QHBoxLayout;
        //Hbox->addSpacing(400);
    Hbox->addWidget(prodazaOstatcov);
    Hbox->addWidget(kolProdaz);
      //  Hbox->addSpacing(400);
    salesTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ostatkiTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    QPushButton* buttonAnalisPdf=new QPushButton("Создать отчет");
    connect(buttonAnalisPdf,SIGNAL(clicked(bool)),this,SLOT(analisPdf()));


     QHBoxLayout* tovaruForPrognoz=new QHBoxLayout;
     //tovaruForPrognoz->addWidget(lbTovaru);
     //tovaruForPrognoz->addWidget(boxTovar);
    // tovaruForPrognoz->addWidget(delProduct);
     tovaruForPrognoz->addWidget(buttonAnalisPdf);
     tovaruForPrognoz->addStretch(1);

     customplotSales=salesAnalysis.getChartSales();
     customplotOstatki=salesAnalysis.getChartOstatki();

     connect(customplotSales, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));
     connect(customplotOstatki, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));


        QVBoxLayout* layout=new QVBoxLayout;
    layout->addLayout(HBox);
    layout->addLayout(kolPrognoz);
    layout->addLayout(tovaruForPrognoz);
    layout->addWidget(lb);
    layout->addWidget(salesTableView);
    layout->addWidget(customplotSales);
    layout->addWidget(lb2);
    layout->addWidget(ostatkiTableView);
    layout->addWidget(customplotOstatki);
    //layout->addWidget(lb3);
     //layout->addStretch(1);


    Analis->setLayout(layout);
    scrollAreaAnalis->setWidget(Analis);
    scrollAreaAnalis->setWidgetResizable(true);

}

void MainWindow::addTovar(){
    for(int i=0;i<boxTovar->count();i++){
        if(boxTovar->itemText(i)==namepSalesProducts.text()){
            return;
        }
    }
    boxTovar->addItem(namepSalesProducts.text());
    namepSalesProducts.clear();
}

void MainWindow::delTovar(){
    boxTovar->removeItem(boxTovar->currentIndex());
}

void MainWindow::analisPdf(){

    QPixmap pixmap1(salesTableView->size());
    salesTableView->render(&pixmap1);
    pixmap1.save("gr1.png");

    QPixmap pixmap2(customplotSales->size());
    customplotSales->render(&pixmap2);
    pixmap2.save("gr2.png");

    QPixmap pixmap3(ostatkiTableView->size());
    ostatkiTableView->render(&pixmap3);
    pixmap3.save("gr3.png");

    QPixmap pixmap4(customplotOstatki->size());
    customplotOstatki->render(&pixmap4);
    pixmap4.save("gr4.png");



       // QString Time=Ti.toString();
       // QString Date=Dt.toString();
       // QString k=ui->comboBoxKRyad->currentText();
       // QString tr=ui->comboBoxKTr->currentText();
       // QString metod=ui->comboBoxMetods->currentText();
        QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
           if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
           QPrinter printer(QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setPaperSize(QPrinter::A4);
           printer.setOutputFileName(fileName);

           QTextDocument doc;
           doc.setHtml("<h2>Прогноз прадажи товара "+namepSalesProducts.text()+" на "+inMonth.currentText()+" месяцев</h2>"
                       //"<h3>"
                       "<p align='center'>Таблица продаж продукта за текущий год </p>\n"
                       "<p align='center'><img src='gr1.png' height='30' width='500'></p>\n"

                       "<p align='center'>График продаж продукта за текущий год </p>\n"
                       "<p align='center'><img src='gr2.png' height='150' width='500'></p>\n"
                       //"<br>"
                      // "<br>"
                      // "<br>"
                      // "<br>"
                      // "<br>"
                       "<p align='center'>Таблица прогноза продаж продукта на cледующие "+inMonth.currentText()+" месяцев</p>\n"
                       "<p align='center'><img src='gr3.png' height='30' width='500'></p>\n"

                       "<p align='center'>График прогноза продаж</p>\n"
                       "<p align='center'><img src='gr4.png' height='150' width='500'></p>\n");

           doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
           doc.print(&printer);

}

void MainWindow::rulesPdf(){
    QPixmap pixmap1(rulesTableView->size());
    rulesTableView->render(&pixmap1);
    pixmap1.save("gr1.png");


       // QString Time=Ti.toString();
       // QString Date=Dt.toString();
       // QString k=ui->comboBoxKRyad->currentText();
       // QString tr=ui->comboBoxKTr->currentText();
       // QString metod=ui->comboBoxMetods->currentText();
        QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
           if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

           QPrinter printer(QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setPaperSize(QPrinter::A4);
           printer.setOutputFileName(fileName);

           QTextDocument doc;
           doc.setHtml("<h3>Шаблонные покупки для товаров категории "+categoryline.currentText()+"</h3>"
                       "<p>Минимальная поддержка:"+minsupline.text()+"%</p>\n"
                       "<p>Максимальная поддержка:"+maxsupline.text()+"%</p>\n"
                       "<p>Минимальная достоверность:"+minconfline.text()+"%</p>\n"
                       "<p>Максимальная достоверность:"+maxconfline.text()+"%</p>\n"
                       "<p align='center'><img src='gr1.png'  width='500'></p>\n");

           /*QString text("<table><thead>");
                       text.append("<tr>");
                       for (int i = 0; i < rulesTableView->model()->columnCount(); i++) {
                           text.append("<th>").append(rulesTableView->->model()->headerData(i, Qt::DisplayRole).toString()).append("</th>");
                       }
                       text.append("</tr></thead>");
                       text.append("<tbody>");
                       for (int i = 0; i < rulesTableView->model()->rowCount(); i++) {
                           text.append("<tr>");
                           for (int j = 0; j < rulesTableView->model()->columnCount(); j++) {
                               QTableWidgetItem *item = rulesTableView->model()-> item(i, j);
                               if (!item || item->text().isEmpty()) {
                                   rulesTableView->setItem(i, j, new QTableWidgetItem("0"));
                               }
                               text.append("<td>").append(rulesTableView->item(i, j)->text()).append("</td>");
                           }
                           text.append("</tr>");
                       }
                       text.append("</tbody></table>");
                       doc.setHtml(text);*/

           doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
           doc.print(&printer);
}

void MainWindow::createTabWidgetRules(){
    Rules=new QWidget;
    rules=new AssociationRules;


    rulesTableView=new QTableView;
    rulesTableView->setStyleSheet(style->getTableViewStyleSheet());
    rulesTableView->setFont(f);
    rulesTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //rulesTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //rulesTableView->resizeRowsToContents();
    //rulesTableView->resizeColumnsToContents();
    //rulesTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
   // rulesTableView->setAlternatingRowColors(true);
   // rulesTableView->setSelectionMode(QAbstractItemView::SingleSelection);

    QPalette Pal(palette());

    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background,"#4C5866");
    Rules->setAutoFillBackground(true);
    Rules->setPalette(Pal);

    QWidget* setting=new QWidget;

    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background,"#4C5866");
    setting->setAutoFillBackground(true);
    setting->setPalette(Pal);


    QLabel* minsup=new QLabel("Поддержка:         min");
    minsup->setStyleSheet("font-size:20px;color:white;");

    QLabel* maxsup=new QLabel("  max");
    maxsup->setStyleSheet("font-size:20px;color:white;");

    QLabel* minconf=new QLabel("Достоверность:  min");
    minconf->setStyleSheet("font-size:20px;color:white;");

    QLabel* maxconf=new QLabel("  max");
    maxconf->setStyleSheet("font-size:20px;color:white;");

    QLabel* cat=new QLabel("Категория товаров:");
    cat->setStyleSheet("font-size:20px;color:white;");

    QPushButton* button_setttules=new QPushButton("Поиск");
    connect(button_setttules,SIGNAL(clicked()),this,SLOT(createRules()));

    QPushButton* buttonRulesPdf=new QPushButton("Создать отчет");
    connect(buttonRulesPdf,SIGNAL(clicked()),this,SLOT(rulesPdf()));

        QSqlQuery* query2=new QSqlQuery();
        query2->exec("select name from category;");

        while(query2->next()){
        categoryline.addItem(query2->value(0).toString());
        //cbox->addItem(query2->value(0).toString());
        }


        QGridLayout* gridLayout=new QGridLayout;
        gridLayout->addWidget(minsup,0,0);
        gridLayout->addWidget(&minsupline,0,1);
        gridLayout->addWidget(maxsup,0,2);
        gridLayout->addWidget(&maxsupline,0,3);

        gridLayout->addWidget(minconf,1,0);
        gridLayout->addWidget(&minconfline,1,1);
        gridLayout->addWidget(maxconf,1,2);
        gridLayout->addWidget(&maxconfline,1,3);
    gridLayout->addWidget(cat,2,0);
    gridLayout->addWidget(&categoryline,2,1,2,2);
    gridLayout->addWidget(buttonRulesPdf,1,4);
    gridLayout->addWidget(button_setttules,0,4);

    setting->setLayout(gridLayout);

    QHBoxLayout* hbox=new QHBoxLayout;
    hbox->addWidget(setting);
    hbox->addStretch(1);

    QVBoxLayout* layout=new QVBoxLayout;
    layout->addLayout(hbox);
    layout->addWidget(rulesTableView);

    Rules->setLayout(layout);
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
    //tabRules->removeTab(1);
   // tabRules->removeTab(1);
    //tabRules->removeTab(1);

    rules->setMinSup(minsupline.text().toInt());
    rules->setMaxSup(maxsupline.text().toInt());
    rules->setMinConf(minconfline.text().toInt());
    rules->setMaxConf(maxconfline.text().toInt());
    rules->setCategory(categoryline.currentText());
    rules->CreateRules();


  rulesTableView->setModel(rules->getModelRyles());
 // rulesTableView->resizeRowsToContents();
  //rulesTableView->resizeColumnsToContents();


}

void MainWindow::changeDiagram(){
    QString fdate=diagramFromDate.date().toString("yyyy-MM-dd");
    QString tdate=diagramToDate.date().toString("yyyy-MM-dd");
    int max=diagramToDate.date().month()+2;
    int min=diagramFromDate.date().month();
   // qDebug()<<max;

    //switch(variantDiagram.currentIndex()){
    //case 0:{
        chart.ChangeDiagram(*customplot,"select month(date),count(tid) from date where date(date) between '"+fdate+"' and '"+tdate+"' group by month(date);","Кол-вл чекла",min,max);
     //   break;
   // }
   // case 1:{
        chart.ChangeDiagram(*customplot1,"select month(date),sum(price*kol)/count(distinct tid) from transactions as t1 inner join products using(id) inner join date using(tid) where date(date) between '"+fdate+"' and '"+tdate+"' group by month(date);","Средняя цена чека",min,max);
     //   break;
   // }
   // case 2:{
        chart.ChangeDiagram(*customplot2,"select month(date),sum(price*kol) from transactions as t1 inner join products using(id) inner join date using(tid) where date(date) between '"+fdate+"' and '"+tdate+"' group by month(date);","Объем продаж в грн.",min,max);
     //   break;
   // }
   // case 3:{
     //   chart.ChangeDiagram(*customplot,"select table1.sum,count(table1.tid) from (select tid,sum(price*kol) as sum from transactions as t1 inner join products using(id) inner join date using(tid) where year(date)=2017 group by tid having sum(price*kol)>100 and sum(price*kol)<500) as table1 group by table1.sum;","Количество чеков.",100,500);
      //  break;
   // }
   // default:{
    //    break;
   // }
   // }

}

void MainWindow::showPointToolTip(QMouseEvent *event)
{

   // int x = customplot->xAxis->pixelToCoord(event->pos().x());
    double y = customplot->yAxis->pixelToCoord(event->pos().y());
    double y1 = customplot1->yAxis->pixelToCoord(event->pos().y());
    double y2 = customplot2->yAxis->pixelToCoord(event->pos().y());
    double y3 = customplotSales->yAxis->pixelToCoord(event->pos().y());
    double y4 = customplotOstatki->yAxis->pixelToCoord(event->pos().y());

    customplot->setToolTip(QString("%1").arg(y));
    customplot1->setToolTip(QString("%1").arg(y1));
    customplot2->setToolTip(QString("%1").arg(y2));
    customplotSales->setToolTip(QString("%1").arg(y3));
    customplotOstatki->setToolTip(QString("%1").arg(y4));;

}

void MainWindow::createWidgetDiagram(){
    Diagram=new QWidget;

    QPalette Pal(palette());

    QWidget* wgt=new QWidget(Diagram);
   // wgt->setMinimumHeight(100);
   // wgt->setMinimumWidth(100);
    wgt->resize(100,100);
    wgt->show();

    // устанавливаем цвет фона
    Pal.setColor(QPalette::Background,"#4C5866");
    Diagram->setAutoFillBackground(true);
    Diagram->setPalette(Pal);

    variantDiagram.addItem("Количество чеков за месяц");
    variantDiagram.addItem("Средняя цена чека за месяц");
    variantDiagram.addItem("Объем продаж в у.е. за месяц");
    //variantDiagram.addItem("Количество чеков");
    variantDiagram.setMaximumWidth(100);

    customplot->addGraph();
    customplot1->addGraph();
    customplot2->addGraph();


    QCPTextElement *titleSales = new QCPTextElement(customplot);
    titleSales->setText("Количество проданых чеков за месяц");
    titleSales->setFont(QFont("sans", 12));
    customplot->plotLayout()->insertRow(0);
    customplot->plotLayout()->addElement(0, 0, titleSales);

    QCPTextElement *titleSales1 = new QCPTextElement(customplot1);
    titleSales1->setText("Средняя цена чека за месяц");
    titleSales1->setFont(QFont("sans", 12));
    customplot1->plotLayout()->insertRow(0);
    customplot1->plotLayout()->addElement(0, 0, titleSales1);

    QCPTextElement *titleSales2 = new QCPTextElement(customplot2);
    titleSales2->setText("Объем продаж в грн. за месяц");
    titleSales2->setFont(QFont("sans", 12));
    customplot2->plotLayout()->insertRow(0);
    customplot2->plotLayout()->addElement(0, 0, titleSales2);

    connect(customplot, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));
    connect(customplot1, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));
    connect(customplot2, SIGNAL(mouseMove(QMouseEvent*)), this,SLOT(showPointToolTip(QMouseEvent*)));

        //select month(date),count(tid) from date where year(date)=2017 group by month(date);

        //средняя цена чека на месяц
        //select month(date),sum(price*kol)/count(distinct tid) from transactions as t1 inner join products using(id) inner join date using(tid) where year(date)=2018 group by month(date);

        //объем продаж за месяц в гривнах
        //select month(date),sum(price*kol) from transactions as t1 inner join products using(id) inner join date using(tid) where year(date)=2018 group by month(date);

    //customplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);

    QWidget* choiseGraph=new QWidget;

    QLabel* namegraph=new QLabel("График:");
    namegraph->setStyleSheet("font-size:17px;");

    QPushButton* buttonAnalitikPdf=new QPushButton("Создлать отчет");
    connect(buttonAnalitikPdf,SIGNAL(clicked(bool)),this,SLOT(chartsPdf()));
    //settgraph->setStyleSheet("background-color:#4547E8;color:white;");
   // settgraph->setPalette(QColor(69, 71, 232));
    //settgraph->setMaximumWidth(100);

   // variantDiagram.setStyleSheet(style->getComboBoxStyleSheet());

    connect(&variantDiagram,SIGNAL(activated(int)),SLOT(changeDiagram()));

    connect(&diagramFromDate,SIGNAL(dateChanged(QDate)),SLOT(changeDiagram()));
    connect(&diagramToDate,SIGNAL(dateChanged(QDate)),SLOT(changeDiagram()));

    diagramToDate.setDisplayFormat("dd-MMM-yyyy");
    diagramToDate.setCalendarPopup(true);

    //fromDate=new QDateEdit;
    diagramFromDate.setDisplayFormat("dd-MMM-yyyy");
    diagramFromDate.setCalendarPopup(true);

    QLabel* lb3=new QLabel("Период от:");
    lb3->setStyleSheet("font-size:15px;");

    QLabel* lb5=new QLabel("-");
    lb5->setStyleSheet("font-size:25px;");


    QHBoxLayout* hbox=new QHBoxLayout;
  //  hbox->addWidget(namegraph);
  //  hbox->addWidget(&variantDiagram);
    hbox->addWidget(lb3);
    hbox->addWidget(&diagramFromDate);
    hbox->addWidget(lb5);
    hbox->addWidget(&diagramToDate);
    hbox->addStretch(1);
    hbox->addWidget(buttonAnalitikPdf);


    Pal.setColor(QPalette::Background,"white");
    choiseGraph->setAutoFillBackground(true);
    choiseGraph->setPalette(Pal);
    choiseGraph->setMaximumHeight(50);
    choiseGraph->setLayout(hbox);


    QVBoxLayout* layout=new QVBoxLayout;
    layout->addWidget(choiseGraph);
    layout->addWidget(customplot);
    layout->addWidget(customplot1);
    layout->addWidget(customplot2);

    Diagram->setLayout(layout);

}

void MainWindow::chartsPdf(){
    QPixmap pixmap1(customplot->size());
    customplot->render(&pixmap1);
    pixmap1.save("gr1.png");

    QPixmap pixmap2(customplot1->size());
    customplot1->render(&pixmap2);
    pixmap2.save("gr2.png");

    QPixmap pixmap3(customplot2->size());
    customplot2->render(&pixmap3);
    pixmap3.save("gr3.png");




       // QString Time=Ti.toString();
       // QString Date=Dt.toString();
       // QString k=ui->comboBoxKRyad->currentText();
       // QString tr=ui->comboBoxKTr->currentText();
       // QString metod=ui->comboBoxMetods->currentText();
        QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
           if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
           QPrinter printer(QPrinter::PrinterResolution);
           printer.setOutputFormat(QPrinter::PdfFormat);
           printer.setPaperSize(QPrinter::A4);
           printer.setOutputFileName(fileName);

           QTextDocument doc;
           doc.setHtml(//"<h2>Прогноз прадажи товара "+namepSalesProducts.text()+" на "+inMonth.currentText()+" месяцев</h2>"
                       //"<h3>"
                       //"<p align='center'>Таблица продаж продукта за текущий год </p>\n"
                       "<p align='center'><img src='gr1.png' height='150' width='500'></p>\n"

                       //"<p align='center'>График продаж продукта за текущий год </p>\n"
                       "<p align='center'><img src='gr2.png' height='150' width='500'></p>\n"

                       //"<p align='center'>Таблица прогноза продаж продукта на cледующие месяцев</p>\n"
                       "<p align='center'><img src='gr3.png' height='150' width='500'></p>\n");

           doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
           doc.print(&printer);

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
        scrollAreaAnalis->setHidden(false);
        prevopen=4;
    }else
    if(item->text()=="Поиск шаболных покупок"){//"Поиск шаболных покупок"
        isOpenItem="Поиск шаболных покупок";
        mainGbox->itemAt(prevopen)->widget()->setHidden(true);
        Rules->setHidden(false);
        prevopen=5;
    }else
    if(item->text()=="Аналитика"){//"Диаграммы"
        isOpenItem="Аналитика";
        mainGbox->itemAt(prevopen)->widget()->setHidden(true);
        Diagram->setHidden(false);
        prevopen=6;
    }/*else
    if(item->text()=="Склад"){//"Склад"
        isOpenItem="Склад";
        mainGbox->itemAt(prevopen)->widget()->setHidden(true);
        Sclad->setHidden(false);
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
