#include "chart.h"

Chart::Chart()
{

}

void Chart::ChangeDiagram(QCustomPlot& customplot,QString exec,QString yLabel,int min,int max){

    customplot.clearPlottables();
    customplot.addGraph();


    QSqlQuery query;
       // query.exec("select month(date),count(tid) from date where year(date)=2017 group by month(date);");
        query.exec(exec);
     //  if(yLabel=="Количество чеков."){
        if(query.size()==0){
            return;
        }

            QVector<double> ticks;
            QStringList list;
            QVector<QString> labels;
            int sum=min;

            //ticks <<1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 <<10 <<11<<12;
            list <<"Январь"
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

            double N=query.size();
            QVector<double> x, y;
            int i=min;
            while (query.next()) {
               // ticks << query.value(0).toInt();
              //  labels <<QString::number(sum);
              //  sum+=5;
                   x.append(i);
                   y.append(query.value(1).toInt());
                   ticks<<i;
                   labels<<list[i-1];
                   i++;
               }
                customplot.xAxis->setRange(min-1,max);

                QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
                textTicker->addTicks(ticks, labels);
                customplot.xAxis->setTicker(textTicker);



            double minY = y[0], maxY = y[0];
                for (int i=0; i<N; i++)
                {
                    if (y[i]<minY) minY = y[i];
                    if (y[i]>maxY) maxY = y[i];
                }

                customplot.yAxis->setRange(minY*0.95, maxY*1.1);

                    /*QCPBars *bars1 = new QCPBars(customplot.xAxis, customplot.yAxis);
                    bars1->setData(x, y);
                    bars1->setWidth(0.5);
                    bars1->setPen(Qt::NoPen);
                    bars1->setBrush(QColor(69, 71, 232));
                    bars1->rescaleAxes();*/


                    customplot.xAxis->setLabel("Месяцы\n2017");
                    customplot.yAxis->setLabel(yLabel);
                   // customplot.xAxis->setRangeUpper(max);
                   // customplot.xAxis->setRangeLower(min);
                   // customplot.xAxis->setTickLabelRotation(90);
                    customplot.graph()->setData(x,y);
                    customplot.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
                    customplot.graph(0)->setPen(QPen(QColor(0, 17, 230), 2));

                    // customplot.
                   // customplot.rescaleAxes();
                   // customplot.xAxis->set


      /*  }else{

    double a = 1; //Начало интервала, где рисуем график по оси Ox
    double b =  13; //Конец интервала, где рисуем график по оси Ox
    double h = 1; //Шаг, с которым будем пробегать по оси Ox

    double N=(b-a)/h + 2;
    QVector<double> x(N), y(N);
    int i=0;
    while (query.next()) {
           x[i] =query.value(0).toDouble();
           y[i] =query.value(1).toDouble();
           i++;
       }

  //  customplot->graph(0)->setData(x,y);
   // customplot.graph(0)->setLineStyle(QCPGraph::lsImpulse);

    customplot.xAxis->setRange(a,b);



    double minY = y[0], maxY = y[0];
   // qDebug()<<minY;

        for (int i=0; i<query.size(); i++)
        {
           // qDebug()<<y[i];
            if (y[i]<minY) minY = y[i];
            if (y[i]>maxY) maxY = y[i];
        }
  //      customplot.yAxis->deleteLater();
    customplot.yAxis->setRange(minY*0.9, maxY*1.1);

    //QCPBars *bars1 = new QCPBars(customplot.xAxis, customplot.yAxis);
    //bars1->setData(x, y);
    //bars1->setWidth(9/(double)x.size());
    //bars1->setPen(Qt::NoPen);
    //bars1->setBrush(QColor(69, 71, 232));
    customplot.graph()->setData(x,y);


    customplot.xAxis->setLabel("Месяцы\n2017");
    customplot.yAxis->setLabel(yLabel);
    customplot.xAxis->setRangeUpper(13);
    customplot.xAxis->setRangeLower(0);


        //}

   // customplot->yAxis->setRangeUpper(maxY+200);
    //customplot->yAxis->setRangeUpper(maxY);*/

  // customplot->xAxis->setSelectableParts(QCPAxis::spAxis|QCPAxis::spTickLabels);

    //customplot.xAxis->grid()->setSubGridVisible(true);
    //customplot.yAxis->grid()->setSubGridVisible(true);


   //customplot->rescaleAxes();
  //  customplot->yAxis->setTickLength(1);
    customplot.replot();
}
