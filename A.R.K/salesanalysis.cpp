#include "salesanalysis.h"

SalesAnalysis::SalesAnalysis()
{

}

QStandardItemModel* SalesAnalysis::getModelSales(QString tovar){

    modelSales=new QStandardItemModel;

      QStandardItem *item;

       QStringList verticalHeader;
       verticalHeader.append(tovar);

    QStringList horizontalHeader;
     /*  horizontalHeader.append("Январь");
       horizontalHeader.append("Февраль");
       horizontalHeader.append("Март");
       horizontalHeader.append("Апрель");
       horizontalHeader.append("Май");
       horizontalHeader.append("Июнь");
       horizontalHeader.append("Июль");
       horizontalHeader.append("Август");
       horizontalHeader.append("Сентябрь");
       horizontalHeader.append("Октябрь");
       horizontalHeader.append("Ноябрь");
       horizontalHeader.append("Декабрь");*/

       QStringList list;
       list<<"Январь"<<"Февраль"<<"Март"<<"Апрель"<<"Май"<<"Июнь"<<"Июль"<<"Август"<<"Сентябрь"<<"Октябрь"<<"Ноябрь"<<"Декабрь";


       modelSales->setVerticalHeaderLabels(verticalHeader);

       int kol_month=0;
       QSqlQuery query;
       query.prepare("select month(date) from transactions inner join date using(tid) inner join products using(id) where products.name like '"+tovar+"' and year(date)=year(now()) group by month(date);");
        query.exec();
        int k=0;
        while (query.next()) {
            kol_month=query.value(0).toInt();
            horizontalHeader.append(list[k++]);
        }
         modelSales->setHorizontalHeaderLabels(horizontalHeader);

    for(int i=1;i<=kol_month;i++){
        QSqlQuery query;
            query.prepare("select count(*) from transactions inner join date using(tid) inner join products using(id) where products.name like '"+tovar+"' and month(date)="+QString::number(i)+" and year(date)=year(now()) group by products.name;");
             query.exec();
        int j=0;

           while (query.next()) {
           item = new QStandardItem(query.value(0).toString());
           modelSales->setItem(j, i-1, item);

           j++;
         }
           if(j==0){
               item = new QStandardItem("0");
               modelSales->setItem(j, i-1, item);
           }

    }
    return modelSales;
}

QStandardItemModel* SalesAnalysis::getModelOstatki(QString tovar,int inMonth){

    int beg=2017;
    int end=2018;

    double Tt=0;
    double Lt1=0;
    double Lt2=0;
    double sale=0;

    double k=0.5;
    double b=0.1;
    double q=0.9;


    QSqlQuery query;
     query.exec("select distinct year(date) from date;");
    int count_years=0;

    while (query.next()) {
    count_years=query.value(0).toInt();;
    }

    double St[(end-beg+1)*12];
    double avg=0;
    int i=0;
    int lastMonth=0;

    for(int year=beg;year<=end;year++){
    for(int month=1;month<=12;month++){
    QSqlQuery query;
        query.prepare("select products.name,count(*) from transactions inner join date using(tid) inner join products using(id) where products.name like '"+QString(tovar)+"' and year(date)="+QString::number(year)+" and month(date)="+QString::number(month)+" group by products.name;");
         query.exec();

           while (query.next()) {
            if(year==beg && month==1){
                sale=query.value(1).toDouble();
                Lt1=sale;
                double ozenka=Lt1+Tt;
                int fail=sale-ozenka;
                avg+=(fail*fail)/(sale*sale);
                 St[0]=1.0;
            }else{

                double ozenka=Lt1+Tt;
                int fail=sale-ozenka;
                avg+=(fail*fail)/(sale*sale);

                sale=query.value(1).toDouble();;
                Lt2=(k*sale/1)+(1-k)*(Lt1+Tt);
                Tt=b*(Lt2-Lt1)+(1-b)*Tt;
                Lt1=Lt2;

                if(i<=12){//year==2017){
                    St[i]=1.0;
                }else{
                St[i]=q*(sale/Lt2)+(1-q)*St[i-13];
                }
            }

        //   qDebug()<<month<<"sale="<<QString::number(sale,'f',2)<<" Lt="<<QString::number(Lt1,'f',2)<<" Tt="<<QString::number(Tt,'f',2)<<" St"<<QString::number(St[i],'f',2);
            i++;
            lastMonth=month;
           }
        }
    }



    modelOstatki=new QStandardItemModel;

     QStandardItem *item;

     QStringList verticalHeader;
            verticalHeader.append(tovar);

      QStringList horizontalHeader;

       // horizontalHeader.append("На складе");
        int kol_on_sclad=0;

          for(int t=1;t<=inMonth;t++){

              lastMonth++;

              if(lastMonth>12){
                  lastMonth=1;
              }

              switch (lastMonth) {
              case 1:{
                   horizontalHeader.append("Январь");
                  break;
              }
              case 2:{
                   horizontalHeader.append("Февраль");
                  break;
              }
              case 3:{
                   horizontalHeader.append("Март");
                  break;
              }
              case 4:{
                   horizontalHeader.append("Апрель");
                  break;
              }
              case 5:{
                  horizontalHeader.append("Май");
                  break;
              }
              case 6:{
                   horizontalHeader.append("Июнь");
                  break;
              }
              case 7:{
                  horizontalHeader.append("Июль");
                  break;
              }
              case 8:{
                   horizontalHeader.append("Август");
                  break;
              }
              case 9:{
                   horizontalHeader.append("Сентябрь");
                  break;
              }
              case 10:{
                   horizontalHeader.append("Октябрь");
                  break;
              }
              case 11:{
                   horizontalHeader.append("Ноябрь");
                  break;
              }
              case 12:{
                    horizontalHeader.append("Декабрь");
                  break;
              }
              default:
                  break;
              }
          }
          modelOstatki->setHorizontalHeaderLabels(horizontalHeader);
          modelOstatki->setVerticalHeaderLabels(verticalHeader);

          query.exec("select kol_on_sclad from products where name like '"+tovar+"';");
          while (query.next()) {
             kol_on_sclad=query.value(0).toInt();
          }

        //  item = new QStandardItem(QString::number(kol_on_sclad));
          // modelOstatki->setItem(0, 0, item);


        int pr=0;
        int ostatok=0;
        for(int t=1;t<=inMonth;t++){

            pr=(Lt2+Tt*t)*St[i-(13-t)];

            //if(t==1){
            //ostatok=kol_on_sclad-pr;
           // }else{
          //  ostatok=ostatok-pr;
           // }
            //qDebug()<<ostatok;

            item = new QStandardItem(QString::number(pr));
             modelOstatki->setItem(0, t-1, item);

           // qDebug()<<QString::number(pr,'d',2);
        }
   // qDebug()<<1-(avg/i)
        return modelOstatki;
}

QString SalesAnalysis::getZnach(){
    const int n=60;
    //Индексная переменная:
    int i;
    //Массивы статистических значений:
    //объем продаж в рублях за каждый месяц
    double y[n]={  17986229,
                   23571965,
                   25537589,
                   24630951,
                   24429696,
                   26116377,
                   27931501,
                   25914893,
                   24904130,
                   22360354,
                   23825299,
                   22241744,
                   21149853,
                   23770186,
                   29608386,
                   28588548,
                   29712036,
                   31191793,
                   28311730,
                   27438262,
                   26166319,
                   25916207,
                   23168086,
                   27707909,
                   25379305,
                   27823570,
                   28518039,
                   33971886,
                   31577081,
                   29328611,
                   34312920,
                   31364478,
                   29046432,
                   27244171,
                   24353446,
                   25447525,
                   24255101,
                   22391876,
                   27902911,
                   24102028,
                   24939643,
                   25401741,
                   22817314,
                   23554471,
                   21219769,
                   21144903,
                   19185427,
                   20507490,
                   16116508,
                   20363081,
                   24924310,
                   23881278,
                   24039243,
                   29292943,
                   25244289,
                   26986987,
                   26856798,
                   27051059,
                   23474916,
                   32610182

};
    //номер месяца
    double x[n]={1,
                 2,
                 3,
                 4,
                 5,
                 6,
                 7,
                 8,
                 9,
                 10,
                 11,
                 12,
                 13,
                 14,
                 15,
                 16,
                 17,
                 18,
                 19,
                 20,
                 21,
                 22,
                 23,
                 24,
                 25,
                 26,
                 27,
                 28,
                 29,
                 30,
                 31,
                 32,
                 33,
                 34,
                 35,
                 36,
                 37,
                 38,
                 39,
                 40,
                 41,
                 42,
                 43,
                 44,
                 45,
                 46,
                 47,
                 48,
                 49,
                 50,
                 51,
                 52,
                 53,
                 54,
                 55,
                 56,
                 57,
                 58,
                 59,
                 60

};
    //Параметры модели:
   long double a,b;
    //Средние значения:
    double Sx=0,Sy=0,Sxy=0,Sxx=0;

    //Вычисление параметров модели:
    for(i=0; i < n; i++){
     Sx+=x[i];
     Sy+=y[i];
     Sxy+=x[i]*y[i];
     Sxx+=x[i]*x[i];
    }
    Sx/=n;
    Sy/=n;
    Sxy/=n;
    Sxx/=n;
    a=(Sx*Sy-Sxy)/(Sx*Sx-Sxx);
    b=(Sxy-a*Sxx)/Sx;
   // qDebug()<<a;
    //qDebug()<<b;
    QString st=QString::number(a,'d',5)+","+QString::number(b,'f',5)+"\n";
    QString ss="Отклонение знач.";
    st+="Месяц         Продажи руб.         Значения тренда         "+ss+"        Среднее отклонение \n";
    //Значения тренда
    double ztr[n];
    for(int i=0;i<n;i++){
        ztr[i]=a*(i+1)+b;
    }

    //Отклонение фактических значений от значений тренда
    double zt[n];
    for(int i=0;i<n;i++){
        zt[i]=y[i]/(a*(i+1)+b);
    }

   //Среднее отклонение для каждого месяца
     double g[12];
     int k=0;
     while(k<12){
         int t=k;
         int kol=0;
        while(t<n){
            g[k]+=zt[t];
            kol++;
            t+=12;
        }
        g[k]/=kol;
         k++;
     }
     for(int i=0;i<12;i++){
       //   qDebug()<<g[i];
     }
     //Общий индекс сезонности
     double sr=0;
     for(int i=0;i<12;i++){
          sr+=g[i];
     }
     sr=sr/12;
  //   qDebug()<<"Общий индекс сезонности:"<<sr;
    // Коэффициенты сезонности очищенные от роста
     double ghy[12];
     for(int i=0;i<12;i++){
          ghy[i]=g[i]/sr;
     //    qDebug()<<ghy[i];
     }

     for(int i=0;i<n;i++){
         st+=QString::number(i)+"              "+QString::number(y[i],'d',5)+"           "+QString::number(ztr[i],'d',5)+"                "+QString::number(zt[i],'d',5)+"\n";
     }




    return st;

    //Результат:
    //cout << "a = " << a << endl;
    //cout << "b = " << b << endl;
}

