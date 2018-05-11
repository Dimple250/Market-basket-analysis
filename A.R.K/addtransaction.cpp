#include "addtransaction.h"
#include "ui_addtransaction.h"

AddTransaction::AddTransaction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTransaction)
{
    ui->setupUi(this);

    QListWidget* list=new QListWidget;

    QSqlQuery query;
    query.exec("select name from products;");

    ui->Products->clear();

    while(query.next()){
        ui->Products->addItem(query.value(0).toString());
        list->addItem(query.value(0).toString());
    }

    QCompleter* completer = new QCompleter( this );
    completer->setModel(list->model());
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    completer->setMaxVisibleItems(6);

    ui->Products->setCompleter(completer);
    ui->Products->view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    ui->dateTimeEdit->setDate(QDate::currentDate());
    ui->dateTimeEdit->setTime(QTime::currentTime());

    connect(ui->buttonAddKorzina,SIGNAL(clicked(bool)),this,SLOT(addProducts()));
    connect(ui->Korzina,SIGNAL(currentTextChanged(QString)),this,SLOT(changeKolProduct()));
    connect(ui->KolKorzina,SIGNAL(valueChanged(int)),this,SLOT(changeKolKorzina()));
    connect(ui->buttonDelKorzina,SIGNAL(clicked(bool)),this,SLOT(delProduct()));
    connect(ui->buttonAddTrans,SIGNAL(clicked(bool)),this,SLOT(addTrans()));

}

void AddTransaction::addProducts(){
     QString name=ui->Products->currentText();

    for(int i=0;i<ui->Korzina->count();i++){
        if(name==ui->Korzina->itemText(i)){
            return;
        }
    }

    korzina[name]=ui->KolTovar->value();
    list<<name;
    ui->Korzina->addItem(name);
    //ui->KolKorzina->setValue();
}

void AddTransaction::changeKolProduct(){
    ui->KolKorzina->setValue(korzina[ui->Korzina->currentText()]);
}

void AddTransaction::changeKolKorzina(){
     korzina[ui->Korzina->currentText()]=ui->KolKorzina->value();
}

void AddTransaction::delProduct(){
    korzina.remove(ui->Korzina->currentText());
    ui->Korzina->removeItem(ui->Korzina->currentIndex());

}

void AddTransaction::addTrans(){
    QSqlQuery query;
    query.exec("select distinct tid from transactions order by tid desc limit 1;");
    int tid=0;
    while(query.next()){
        tid=query.value(0).toInt();
    }
    tid++;
    int id=0;

    for(int i=0;i<ui->Korzina->count();i++){
        QString name=ui->Korzina->itemText(i);
        int kol=korzina[name];

        query.exec("select id from products where name like '"+name+"';");

        while(query.next()){
            id=query.value(0).toInt();
        }

        QString exec="INSERT INTO transactions (tid, id, name, kol) VALUES ("+QString::number(tid)+","+QString::number(id)+",'"+name+"',"+QString::number(kol)+");";
        query.exec(exec);

        QString date=ui->dateTimeEdit->dateTime().toString("yyyy-mm-dd HH:MM:ss'");
        exec="INSERT INTO date (tid, date) VALUES ("+QString::number(tid)+",'"+date+"');";
        query.exec(exec);
    }
}

AddTransaction::~AddTransaction()
{
    delete ui;
}
