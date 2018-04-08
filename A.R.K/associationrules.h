#ifndef ASSOCIATIONRULES_H
#define ASSOCIATIONRULES_H

#include <QObject>
#include <QWidget>
#include <QtWidgets>
#include <QtSql>

#include "style.h"

class AssociationRules : public QWidget
{
    Q_OBJECT
public:
    explicit AssociationRules(QWidget *parent = 0);
    ~AssociationRules();
    void CreateRules();
    int getListSize();
    void setMinSup(int sup);
    void setMinConf(int conf);
    void setMaxSup(int sup);
    void setMaxConf(int conf);
    void setCategory(QString cat);
    QWidget *getTextRyles();
    QWidget *getTableRyles();
private:
    QList<QString> list;
    int min_sup;
    int min_conf;
    int max_sup;
    int max_conf;
    int length;
    QString category;
    QMap<QString,double> condits;
    QWidget* textrules;
    QWidget* tablerules;
    int propuck;
signals:

public slots:
};

#endif // ASSOCIATIONRULES_H
