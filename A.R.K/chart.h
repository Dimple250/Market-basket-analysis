#ifndef CHART_H
#define CHART_H

#include<QtWidgets>
#include<QtSql>
#include"QCustomPlot/qcustomplot.h"

class Chart
{
public:
    Chart();
    void ChangeDiagram(QCustomPlot& customplot,QString query,QString yLable,int min,int max);
private:

};

#endif // CHART_H
