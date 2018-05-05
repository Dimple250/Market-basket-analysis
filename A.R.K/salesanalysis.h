#ifndef SALESANALYSIS_H
#define SALESANALYSIS_H

#include <QtWidgets>
#include <QtSql>
#include "QCustomPlot/qcustomplot.h"

class SalesAnalysis
{
public:
    SalesAnalysis();
    QStandardItemModel* getModelSales(QComboBox* box);
    QStandardItemModel* getModelOstatki(QComboBox* box,int inMonth);
    QCustomPlot* getChartSales();
    QCustomPlot* getChartOstatki();
private:
    QString str;
    QStandardItemModel* modelSales;
    QStandardItemModel* modelOstatki;

    void setChartSales(QVector<double> x,QVector<double> y,QVector<double> ticks,QVector<QString> labels,int j);
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
