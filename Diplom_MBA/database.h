#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QString>
#include <QStringList>

class Database:public QObject
{
public:
    Database();
    void Connect(QString);
    QString getNameBase();
    QStringList tables();
private:
    QSqlDatabase db;
};

#endif // DATABASE_H
