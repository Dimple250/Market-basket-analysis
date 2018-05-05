#include "salesanalysis.h"
#include "QCustomPlot/qcustomplot.h"

SalesAnalysis::SalesAnalysis()
{
    plotSales.setMinimumHeight(300);
    QCPTextElement *titleSales = new QCPTextElement(&plotSales);
    titleSales->setText("Количество продаж за месяц");
    titleSales->setFont(QFont("sans", 12));
    plotSales.plotLayout()->insertRow(0);
    plotSales.plotLayout()->addElement(0, 0, titleSales);


    plotOstatki.setMinimumHeight(300);
    QCPTextElement *titleOstatki = new QCPTextElement(&plotOstatki);
    titleOstatki->setText("Количество продаж за месяц");
    titleOstatki->setFont(QFont("sans", 12));
    plotOstatki.plotLayout()->insertRow(0);
    plotOstatki.plotLayout()->addElement(0, 0, titleOstatki);

}

QStandardItemModel* SalesAnalysis::getModelSales(QComboBox* boxTovar){
    x.clear();
    y.clear();
    ticks.clear();
    labels.clear();
    kolMonth=0;
    plotSales.clearPlottables();

    modelSales=new QStandardItemModel;

      QStandardItem *item;


    QStringList horizontalHeader;

       QStringList list;
       list<<"Январь"<<"Февраль"<<"Март"<<"Апрель"<<"Май"<<"Июнь"<<"Июль"<<"Август"<<"Сентябрь"<<"Октябрь"<<"Ноябрь"<<"Декабрь";


        int kol_month=0;
       QSqlQuery query;
       query.prepare("select month(date) from transactions inner join date using(tid) inner join products using(id) where products.name like '"+boxTovar->itemText(0)+"' and year(date)=year(now()) group by month(date);");
        query.exec();
        int k=0;
        while (query.next()) {
            kol_month=query.value(0).toInt();
            horizontalHeader.append(list[k++]);

            ticks<<k;
            labels<<list[k-1];

        }
        kolMonth=k;

         modelSales->setHorizontalHeaderLabels(horizontalHeader);

         QStringList verticalHeader;

   for(int j=0;j<boxTovar->count();j++){
       x.clear();
       y.clear();

       verticalHeader.append(boxTovar->itemText(j));


         for(int i=1;i<=kol_month;i++){
        QSqlQuery query;
            query.prepare("select count(*) from transactions inner join date using(tid) inner join products using(id) where products.name like '"+boxTovar->itemText(j)+"' and month(date)="+QString::number(i)+" and year(date)=year(now()) group by products.name;");
             query.exec();

           while (query.next()) {
           item = new QStandardItem(query.value(0).toString());
           modelSales->setItem(j, i-1, item);

           y.append(query.value(0).toDouble());
         }

           x.append(i);

    }
   // qDebug()<<x<<y;
    setChartSales(x,y,ticks,labels,j);
    }
   modelSales->setVerticalHeaderLabels(verticalHeader);


    return modelSales;
}

void SalesAnalysis::setChartSales(QVector<double> x, QVector<double> y, QVector<double> ticks, QVector<QString> labels,int j){


    plotSales.addGraph();

    plotSales.xAxis->setRange(0,x.size()*1.1);

    double minY = y[0], maxY = y[0];
    for (int i=1; i<x.size(); i++)
    {
        if (y[i]<minY) minY = y[i];
        if (y[i]>maxY) maxY = y[i];
    }

    plotSales.yAxis->setRange(minY*0.8, maxY*1.1);

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    plotSales.xAxis->setTicker(textTicker);

   /* QCPBars *bars1 = new QCPBars(plotSales.xAxis, plotSales.yAxis);
    bars1->setData(x, y);
    bars1->setWidth(0.5);
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(69, 71, 232));
    bars1->rescaleAxes();*/
    plotSales.graph()->setData(x, y);

    plotSales.xAxis->setLabel("Месяцы");
    plotSales.yAxis->setLabel("Кол-во продаж");
    plotSales.graph(j)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
    plotSales.graph(j)->setPen(QPen(QColor(0, 17, 230), 2));

    plotSales.replot();

}

QCustomPlot* SalesAnalysis::getChartSales(){
    return &plotSales;
}

QStandardItemModel* SalesAnalysis::getModelOstatki(QComboBox* boxTovar,int inMonth){
    x.clear();
    y.clear();
    ticks.clear();
    labels.clear();
    kolMonth=0;
    plotOstatki.clearPlottables();


    int beg=2017;
    int end=2018;

    double Tt=0;
    double Lt1=0;
    double Lt2=0;
    double sale=0;

    double k=0.5;
    double b=0.1;
    double q=0.9;

    QStringList list;
    list<<"Январь"<<"Февраль"<<"Март"<<"Апрель"<<"Май"<<"Июнь"<<"Июль"<<"Август"<<"Сентябрь"<<"Октябрь"<<"Ноябрь"<<"Декабрь";


    QSqlQuery query;
     query.exec("select distinct year(date) from date;");
    int count_years=0;

    while (query.next()) {
    count_years=query.value(0).toInt();;
    }

    double St[(end-beg+1)*12];
    double avg=0;
    int i=0;
    int lastMonth=0;

    for(int year=beg;year<=end;year++){
    for(int month=1;month<=12;month++){
    QSqlQuery query;
        query.prepare("select products.name,count(*) from transactions inner join date using(tid) inner join products using(id) where products.name like '"+boxTovar->itemText(0)+"' and year(date)="+QString::number(year)+" and month(date)="+QString::number(month)+" group by products.name;");
         query.exec();

           while (query.next()) {
            if(year==beg && month==1){
                sale=query.value(1).toDouble();
                Lt1=sale;
                double ozenka=Lt1+Tt;
                int fail=sale-ozenka;
                avg+=(fail*fail)/(sale*sale);
                 St[0]=1.0;
            }else{

                double ozenka=Lt1+Tt;
                int fail=sale-ozenka;
                avg+=(fail*fail)/(sale*sale);

                sale=query.value(1).toDouble();;
                Lt2=(k*sale/1)+(1-k)*(Lt1+Tt);
                Tt=b*(Lt2-Lt1)+(1-b)*Tt;
                Lt1=Lt2;

                if(i<=12){//year==2017){
                    St[i]=1.0;
                }else{
                St[i]=q*(sale/Lt2)+(1-q)*St[i-13];
                }
            }

        //   qDebug()<<month<<"sale="<<QString::number(sale,'f',2)<<" Lt="<<QString::number(Lt1,'f',2)<<" Tt="<<QString::number(Tt,'f',2)<<" St"<<QString::number(St[i],'f',2);
            i++;
            lastMonth=month;
           }
        }
    }



    modelOstatki=new QStandardItemModel;

     QStandardItem *item;

     QStringList verticalHeader;
            verticalHeader.append(boxTovar->itemText(0));

      QStringList horizontalHeader;

       // horizontalHeader.append("На складе");
        int kol_on_sclad=0;

          for(int t=1;t<=inMonth;t++){

              lastMonth++;

              if(lastMonth>12){
                  lastMonth=1;
              }
              ticks<<++kolMonth;
              labels<<list[lastMonth-1];
              x.append(kolMonth);


              switch (lastMonth) {
              case 1:{
                   horizontalHeader.append("Январь");
                  break;
              }
              case 2:{
                   horizontalHeader.append("Февраль");
                  break;
              }
              case 3:{
                   horizontalHeader.append("Март");
                  break;
              }
              case 4:{
                   horizontalHeader.append("Апрель");
                  break;
              }
              case 5:{
                  horizontalHeader.append("Май");
                  break;
              }
              case 6:{
                   horizontalHeader.append("Июнь");
                  break;
              }
              case 7:{
                  horizontalHeader.append("Июль");
                  break;
              }
              case 8:{
                   horizontalHeader.append("Август");
                  break;
              }
              case 9:{
                   horizontalHeader.append("Сентябрь");
                  break;
              }
              case 10:{
                   horizontalHeader.append("Октябрь");
                  break;
              }
              case 11:{
                   horizontalHeader.append("Ноябрь");
                  break;
              }
              case 12:{
                    horizontalHeader.append("Декабрь");
                  break;
              }
              default:
                  break;
              }
          }
          modelOstatki->setHorizontalHeaderLabels(horizontalHeader);
          modelOstatki->setVerticalHeaderLabels(verticalHeader);


          //QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
          //textTicker->addTicks(ticks, labels);
          //plot.xAxis->setTicker(textTicker);



          query.exec("select kol_on_sclad from products where name like '"+boxTovar->itemText(0)+"';");
          while (query.next()) {
             kol_on_sclad=query.value(0).toInt();
          }

        //  item = new QStandardItem(QString::number(kol_on_sclad));
          // modelOstatki->setItem(0, 0, item);


        int pr=0;
        int ostatok=0;
        for(int t=1;t<=inMonth;t++){

            pr=(Lt2+Tt*t)*St[i-(13-t)];
            y.append(pr);

            //if(t==1){
            //ostatok=kol_on_sclad-pr;
           // }else{
          //  ostatok=ostatok-pr;
           // }
            //qDebug()<<ostatok;

            item = new QStandardItem(QString::number(pr));
             modelOstatki->setItem(0, t-1, item);

           // qDebug()<<QString::number(pr,'d',2);
        }
   // qDebug()<<1-(avg/i)
        setChartOstatki(x,y,ticks,labels);

        return modelOstatki;
}

void SalesAnalysis::setChartOstatki(QVector<double> x, QVector<double> y, QVector<double> ticks, QVector<QString> labels){


    plotOstatki.addGraph();

    plotOstatki.xAxis->setRange(0,x.size()*1.1);

    double minY = y[0], maxY = y[0];
    for (int i=1; i<x.size(); i++)
    {
        if (y[i]<minY) minY = y[i];
        if (y[i]>maxY) maxY = y[i];
    }

    plotOstatki.yAxis->setRange(minY*0.8, maxY*1.1);

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    plotOstatki.xAxis->setTicker(textTicker);

   /* QCPBars *bars1 = new QCPBars(plotSales.xAxis, plotSales.yAxis);
    bars1->setData(x, y);
    bars1->setWidth(0.5);
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(69, 71, 232));
    bars1->rescaleAxes();*/
    plotOstatki.graph()->setData(x, y);

    plotOstatki.xAxis->setLabel("Месяцы");
    plotOstatki.yAxis->setLabel("Кол-во продаж");
    plotOstatki.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
    plotOstatki.graph(0)->setPen(QPen(QColor(0, 17, 230), 2));

    plotOstatki.replot();

}

QCustomPlot* SalesAnalysis::getChartOstatki(){
    return &plotOstatki;
}

