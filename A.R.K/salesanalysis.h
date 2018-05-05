#ifndef SALESANALYSIS_H
#define SALESANALYSIS_H

#include <QtWidgets>
#include <QtSql>
#include "QCustomPlot/qcustomplot.h"

class SalesAnalysis
{
public:
    SalesAnalysis();
    QStandardItemModel* getModelSales(QString name);
    QStandardItemModel* getModelOstatki(QString name,int inMonth);
    QCustomPlot* getChartSales();
    QCustomPlot* getChartOstatki();
private:
    QString str;
    QStandardItemModel* modelSales;
    QStandardItemModel* modelOstatki;

    void setChartSales(QVector<double> x,QVector<double> y,QVector<double> ticks,QVector<QString> labels);
    void setChartOstatki(QVector<double> x,QVector<double> y,QVector<double> ticks,QVector<QString> labels);

    QVector<double> x;
    QVector<double> y;
    QVector<double> ticks;
    QVector<QString> labels;
    int kolMonth;
    QCustomPlot plotSales;
    QCustomPlot plotOstatki;
};

#endif // SALESANALYSIS_H
