#include "chart.h"

Chart::Chart()
{

}

void Chart::ChangeDiagram(QCustomPlot& customplot,QString exec,QString yLabel){

    customplot.clearPlottables();

    QSqlQuery query;
       // query.exec("select month(date),count(tid) from date where year(date)=2017 group by month(date);");
        query.exec(exec);

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

  //  customplot->graph(0)->setData(x,y);
   // customplot.graph(0)->setLineStyle(QCPGraph::lsImpulse);


    customplot.xAxis->setRange(a,b);
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
    customplot.xAxis->setTicker(textTicker);


    double minY = y[0], maxY = y[0];
        for (int i=1; i<N; i++)
        {
            if (y[i]<minY) minY = y[i];
            if (y[i]>maxY) maxY = y[i];
        }


  //      customplot.yAxis->deleteLater();
    customplot.yAxis->setRange(minY, maxY*1.1);

    QCPBars *bars1 = new QCPBars(customplot.xAxis, customplot.yAxis);
    bars1->setData(x, y);
    bars1->setWidth(9/(double)x.size());
    bars1->setPen(Qt::NoPen);
    bars1->setBrush(QColor(69, 71, 232));

    customplot.xAxis->setLabel("Месяцы\n2017");
    customplot.yAxis->setLabel(yLabel);
    customplot.xAxis->setRangeUpper(13);
    customplot.xAxis->setRangeLower(0);

   // customplot->yAxis->setRangeUpper(maxY+200);
    //customplot->yAxis->setRangeUpper(maxY);

  // customplot->xAxis->setSelectableParts(QCPAxis::spAxis|QCPAxis::spTickLabels);

    customplot.xAxis->grid()->setSubGridVisible(true);
    customplot.yAxis->grid()->setSubGridVisible(true);


   //customplot->rescaleAxes();
  //  customplot->yAxis->setTickLength(1);
    customplot.replot();
}
