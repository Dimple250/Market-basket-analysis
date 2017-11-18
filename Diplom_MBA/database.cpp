#include "database.h"

Database::Database()
{
    this->db=QSqlDatabase::addDatabase("QMYSQL");
}

void Database::Connect(QString namebd){

    db.setHostName("localhost");
    db.setDatabaseName("journal");
    db.setUserName("root");
    db.setPassword("233685614");

    if(!db.open() ){
        qDebug()<<"NO";
    }
}

QString Database::getNameBase(){
    return db.databaseName();
}

QStringList Database::tables(){
    return db.tables();
}

