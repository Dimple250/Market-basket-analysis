#ifndef ADDTRANSACTION_H
#define ADDTRANSACTION_H

#include <QDialog>
#include <QtWidgets>
#include <QtSql>

namespace Ui {
class AddTransaction;
}

class AddTransaction : public QDialog
{
    Q_OBJECT

public:
    explicit AddTransaction(QWidget *parent = 0);
    ~AddTransaction();

private:
    Ui::AddTransaction *ui;
    QMap<QString,int> korzina;
    QStringList list;
public slots:
    void addProducts();
    void changeKolProduct();
    void changeKolKorzina();
    void delProduct();
    void addTrans();
};

#endif // ADDTRANSACTION_H
