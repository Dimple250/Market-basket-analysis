#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>

class database
{
public:
    database();
    QSqlDatabase db;
    void Connect(QString);
};

#endif // DATABASE_H
