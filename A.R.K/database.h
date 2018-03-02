#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QString>
#include <QStringList>
#include <QtWidgets>

class Database:public QObject
{
public:
    Database();
    void Connect(QString);
    QString getNameBase();
    QStringList tables();
    QStandardItemModel* getModelProducts(QString querystr);
    QStandardItemModel* getModelTransactions(QString querystr);
private:
    QSqlDatabase db;
    QStandardItemModel* modelProducts;
     QStandardItemModel* modelTransactions;
};

#endif // DATABASE_H
