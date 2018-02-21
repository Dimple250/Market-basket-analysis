#include "associationrules.h"

AssociationRules::AssociationRules(QWidget *parent) : QWidget(parent)
{

}

AssociationRules::~AssociationRules(){
    delete textrules;
}

int AssociationRules::getListSize(){

    return list.length();
}

void AssociationRules::setMinSup(int sup){
    min_sup=sup;
}

void AssociationRules::setMinConf(int conf){
    min_conf=conf;
}

void AssociationRules::setMaxSup(int sup){
    max_sup=sup;
}

void AssociationRules::setMaxConf(int conf){
    max_conf=conf;
}


void AssociationRules::CreateRules(){

    QString items="";
    QString baskets="";
    QString ravno="";
    QString mensh="";

    QSqlQuery* query2=new QSqlQuery();
    query2->exec("select count(distinct tid) from transactions");

    double kol_chek=0;
    while(query2->next()){
    kol_chek=query2->value(0).toInt();
    }
    min_sup=(kol_chek*min_sup)/100;
    //fix next
    query2->exec("SELECT name,COUNT(*) FROm transactions GROUP BY name having count(*)>="+QString::number(min_sup)+";");
    propuck=0;

    while(query2->next()){
                condits[query2->value(0).toString()]=query2->value(1).toDouble()/kol_chek;
        }

    int flag=1;
    int kol_items=4;

    int lenght=1;
    while(lenght<kol_items){
      items="";
      baskets="";
      ravno="";
      mensh="";

    for(int i=0;i<=lenght;i++){
    items+="t"+QString::number(i)+".name,";
    }
    items=items.remove(items.length()-1,items.length()-1);

    for(int i=0;i<=lenght;i++){
    baskets+="transactions as t"+QString::number(i)+",";
    }
    baskets=baskets.remove(baskets.length()-1,baskets.length()-1);

    for(int i=0;i<lenght;i++){
    ravno+="t"+QString::number(i)+".tid=t"+QString::number(i+1)+".tid ";
    ravno+="and ";
    }
    ravno=ravno.remove(ravno.length()-5,ravno.length()-1);

    for(int i=0;i<lenght;i++){
    mensh+="t"+QString::number(i)+".name>t"+QString::number(i+1)+".name ";
    mensh+="and ";
    }
    mensh=mensh.remove(mensh.length()-5,mensh.length()-1);

    QString exec="select "+items+", COUNT(*) from "+baskets+" where "+ravno+" and "+mensh+" group by "+items+" having count(*)>="+QString::number(min_sup)+";";

    query2->exec(exec);
    QString ss="";

        while(query2->next()){
            flag=1;
            ss="";
            for(int i=0;i<=lenght;i++){
            if(condits[query2->value(i).toString()]==0){
                flag=0;
            }
            }
            if(flag==1){
            for(int i=0;i<=lenght;i++){
            ss+=query2->value(i).toString()+",";
            }
            QString st="";
            QString cond=ss.remove(ss.length()-1,ss.length()-1);;

            for(int k=0;k<cond.split(",").length()-1;k++){
                st+=cond.split(",")[k];
                if(k!=cond.split(",").length()-2){
                st+=",";
                }
            }
            double sup=query2->value(lenght+1).toDouble()/kol_chek;
            if((sup/condits[st])*100>=min_conf){
            list<<cond;
            condits[ss]=query2->value(lenght+1).toDouble()/kol_chek;
            }
            }
        }
     lenght++;
        }

}

QWidget *AssociationRules::getTextRyles(){

    textrules=new QWidget;
    QLabel* lb=new QLabel(textrules);
    int y=0;
    for(int i=propuck;i<list.length();i++){
    double sup=condits[list[i]];
    //qDebug()<<cond;
    //double lift=condits[list[2]]/(condits[list[2].split(",")[0]]*condits[list[2].split(",")[1]]);
    double supX=1;
    for(int k=0;k<list[i].split(",").length();k++){
        supX*=condits[list[i].split(",")[k]];
    }
    double improvement=sup/supX;
    QString st="";
    for(int k=0;k<list[i].split(",").length()-1;k++){
        st+=list[i].split(",")[k];
        if(k!=list[i].split(",").length()-2){
        st+=",";
        }
    }
    double cond=(condits[list[i]]/condits[st])*100;
    lb->setText(lb->text()+st+"==>{"+list[i].split(",")[list[i].split(",").length()-1]+"} {поддержка:"+QString::number(sup*100,'f',2)+"% ,достоверность:"+QString::number(cond,'f',2)+"% ,improvement:"+QString::number(improvement,'f',2)+"}\n");
  }
    return textrules;
}

QWidget *AssociationRules::getTableRyles(){

        tablerules=new QWidget;

        QTableView* table=new QTableView(tablerules);
        QStandardItemModel *model = new QStandardItemModel;
        QStandardItem *item;

        QStringList horizontalHeader;
           horizontalHeader.append("Шаблон");
           horizontalHeader.append("Поддержка");
           horizontalHeader.append("Достоверность");
           horizontalHeader.append("Четвертый");

           model->setHorizontalHeaderLabels(horizontalHeader);
           //model->setVerticalHeaderLabels(verticalHeader);

           for(int i=propuck;i<list.length();i++){
           double sup=condits[list[i]];
           double cond=condits[list[i]]/condits[list[i].split(",")[0]];
           //double lift=condits[list[2]]/(condits[list[2].split(",")[0]]*condits[list[2].split(",")[1]]);
           double supX=1;
           for(int k=0;k<list[i].split(",").length();k++){
               supX*=condits[list[i].split(",")[k]];
           }
           double improvement=sup/supX;
           QString st="";
           for(int k=0;k<list[i].split(",").length()-1;k++){
               st+=list[i].split(",")[k];
               if(k!=list[i].split(",").length()-2){
               st+=",";
               }
           }
           //Первый ряд
           item = new QStandardItem(QString(st+"-->"+list[i].split(",")[list[i].split(",").length()-1]));
           model->setItem(i, 0, item);

           item = new QStandardItem(QString(QString::number(sup*100,'f',2)+"%"));
           model->setItem(i, 1, item);

           item = new QStandardItem(QString(QString::number(cond*100,'f',2)+"%"));
           model->setItem(i, 2, item);

           item = new QStandardItem(QString(QString::number(improvement,'f',2)));
           model->setItem(i, 3, item);
  }

           table->setModel(model);

           table->resizeRowsToContents();
           table->resizeColumnsToContents();

           return table;
}
