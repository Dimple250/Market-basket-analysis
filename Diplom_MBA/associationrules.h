#ifndef ASSOCIATIONRULES_H
#define ASSOCIATIONRULES_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QtSql>

class AssociationRules : public QWidget
{
    Q_OBJECT
public:
    explicit AssociationRules(QWidget *parent = 0);
    void CreateRules();
    int getListSize();
    void setMinSup(int sup);
private:
    QList<QString> list;
    int min_sup;
    int length;
    QMap<QString,double> condits;
signals:

public slots:
};

#endif // ASSOCIATIONRULES_H
