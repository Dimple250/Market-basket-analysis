#include "database.h"

Database::Database()
{
    this->db=QSqlDatabase::addDatabase("QMYSQL");
}

void Database::Connect(QString namebd){

    db.setHostName("localhost");
    db.setDatabaseName(namebd);
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

QStandardItemModel* Database::getModelProducts(QString querystr){
    QSqlQuery query;
        query.exec(querystr);

       modelProducts = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
           horizontalHeader.append("");
           horizontalHeader.append("Категория");
           horizontalHeader.append("Продукты");
           horizontalHeader.append("Цена");

           modelProducts->setHorizontalHeaderLabels(horizontalHeader);

           int i=0;
           while (query.next()) {
           //Первый ряд
           item = new QStandardItem(query.value(0).toString());
           modelProducts->setItem(i, 1, item);

           item = new QStandardItem(query.value(1).toString());
           modelProducts->setItem(i, 2, item);

           item = new QStandardItem(QString::number(query.value(2).toFloat()));
           modelProducts->setItem(i, 3, item);
           i++;
  }

        return modelProducts;
}


QStandardItemModel* Database::getModelTransactions(QString querystr){
    QSqlQuery query;
        query.exec(querystr);

       modelTransactions = new QStandardItemModel;
       QStandardItem *item;

       // используется для объединения ячеек таблицы, к ячейкам заголовков он неприменим...
       //QTableView::setSpan ( int row, int column, int rowSpanCount, int columnSpanCount )

       QStringList horizontalHeader;
        //  horizontalHeader.append("Номер");
          horizontalHeader.append("Продукты");
          horizontalHeader.append("Кол-во");
          horizontalHeader.append("Дата");
          horizontalHeader.append("Время");

          modelTransactions->setHorizontalHeaderLabels(horizontalHeader);

          int tid=0;
          int i=0;
          while (query.next()) {

            if(tid!=query.value(0).toInt()){
                tid=query.value(0).toInt();
                item = new QStandardItem("Транзакция №"+QString::number(tid));
                modelTransactions->setItem(i, 0, item);
                i++;
            }

         // item = new QStandardItem(QString::number(query.value(0).toInt()));
         // modelTransactions->setItem(i, 0, item);

          item = new QStandardItem(query.value(1).toString());
          modelTransactions->setItem(i, 0, item);

          item = new QStandardItem(QString::number(query.value(2).toInt()));
          modelTransactions->setItem(i, 1, item);

          item = new QStandardItem(query.value(3).toString());
          modelTransactions->setItem(i, 2, item);

          item = new QStandardItem(query.value(4).toString());
          modelTransactions->setItem(i, 3, item);
          i++;
 }
      /* query.exec("select tid,name,kol,price,DATE_FORMAT(date,GET_FORMAT(DATE,'EUR')),time(date) from transactions inner join date using(tid) natural join products where tid=1025;");
      QStringList horizontalHeader;
                 horizontalHeader.append("Чек №"+QString::number(query.value(0).toInt()));
                // horizontalHeader.append("Продукты");
                 //horizontalHeader.append("Кол-во");
                 //horizontalHeader.append("Дата");
                 //horizontalHeader.append("Время");

                 modelTransactions->setHorizontalHeaderLabels(horizontalHeader);
                // modelTransactions->

                 int i=0;
                 while (query.next()) {
                // Первый ряд
                 item = new QStandardItem(QString::number(query.value(0).toInt()));
                 modelTransactions->setItem(i, 0, item);

                 item = new QStandardItem(query.value(1).toString());
                 modelTransactions->setItem(i, 0, item);

                 item = new QStandardItem(QString::number(query.value(2).toInt()));
                 modelTransactions->setItem(i, 2, item);

                 item = new QStandardItem(query.value(3).toString());
                 modelTransactions->setItem(i, 3, item);


                // item = new QStandardItem(query.value(4).toString());
                 //modelTransactions->setItem(i, 4, item);
                 i++;
                 }*/


        return modelTransactions;
}
