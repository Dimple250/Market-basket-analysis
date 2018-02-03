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

void AssociationRules::CreateRules(){

    QString items="";
    QString baskets="";
    QString ravno="";
    QString mensh="";

    QSqlQuery* query2=new QSqlQuery();
    query2->exec("select count(tid) from transactions group by tid");
    //usless
    int kol_chek=query2->numRowsAffected();
    //fix next
    query2->exec("SELECT name,COUNT(*) FROm transactions GROUP BY name;");

    while(query2->next()){
            if(query2->value(1).toInt()>=min_sup){
                list<<query2->value(0).toString();
                condits[query2->value(0).toString()]=query2->value(1).toDouble()/kol_chek;
            }
        }

        int flag=1;
        int kol_items=4-1;

        while(flag>0){
          items="";
          baskets="";
          ravno="";
          mensh="";

        for(int i=1;i<kol_items;i++){
        items+="t"+QString::number(i)+".name,";
        }
        items=items.remove(items.length()-1,items.length()-1);

        for(int i=1;i<kol_items;i++){
        baskets+="transactions as t"+QString::number(i)+",";
        }
        baskets=baskets.remove(baskets.length()-1,baskets.length()-1);

        for(int i=1;i<kol_items-1;i++){
        ravno+="t"+QString::number(i)+".tid=t"+QString::number(i+1)+".tid ";
        ravno+="and ";
        }
        ravno=ravno.remove(ravno.length()-5,ravno.length()-1);

        for(int i=1;i<kol_items-1;i++){
        mensh+="t"+QString::number(i)+".name<t"+QString::number(i+1)+".name ";
        mensh+="and ";
        }
        mensh=mensh.remove(mensh.length()-5,mensh.length()-1);

        QString exec="select "+items+", COUNT(*) from "+baskets+" where "+ravno+" and "+mensh+" group by "+items+" having count(*)>="+QString::number(min_sup)+";";

        query2->exec(exec);
        QString ss="";

        while(query2->next()){
            ss="";
            for(int i=0;i<kol_items-1;i++){
            ss+=query2->value(i).toString()+",";
            }
            list<<ss.remove(ss.length()-1,ss.length()-1);
            //ss=ss.remove(ss.length()-1,ss.length()-1);
           //list<<query2->value(kol_items-1).toString();
            condits[ss]=query2->value(kol_items-1).toDouble()/kol_chek;
          //   qDebug()<<ss;
            }
            //qDebug()<<list;

            kol_items++;


            query2->last();
           flag=query2->at();
        }
}

QWidget *AssociationRules::getTextRyles(){

    textrules=new QWidget;
    QLabel* lb=new QLabel(textrules);
    int y=0;
    for(int i=5;i<list.length();i++){
        //lb=new QLabel(textrules);
        //y+=20;
    //lb->setStyleSheet("margin-top:"+QString::number(y)+"px;margin-left:0px;");
    double sup=condits[list[i]];
    double cond=condits[list[i]]/condits[list[i].split(",")[0]];
    //double lift=condits[list[2]]/(condits[list[2].split(",")[0]]*condits[list[2].split(",")[1]]);
    double supX=1;
    for(int k=0;k<list[i].split(",").length();k++){
        supX*=condits[list[i].split(",")[k]];
    }
    double improvement=sup/supX;
    QString st="";
    for(int k=1;k<list[i].split(",").length();k++){
        st+=list[i].split(",")[k];
        if(k!=list[i].split(",").length()-1){
        st+=",";
        }
    }
    lb->setText(lb->text()+list[i].split(",")[0]+"==>{"+st+"} {support:"+QString::number(sup,'f',2)+",confidence:"+QString::number(cond,'f',2)+",improvement:"+QString::number(improvement,'f',2)+"}\n");
  }
    return textrules;
}
