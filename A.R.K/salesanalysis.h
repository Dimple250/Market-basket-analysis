#ifndef SALESANALYSIS_H
#define SALESANALYSIS_H

#include <QtWidgets>
#include <QtSql>

class SalesAnalysis
{
public:
    SalesAnalysis();
    QString getZnach();
    QStandardItemModel* getModelSales(QString name);
    QStandardItemModel* getModelOstatki(QString name,int inMonth);
private:
    QString str;
    QStandardItemModel* modelSales;
    QStandardItemModel* modelOstatki;
};

#endif // SALESANALYSIS_H
