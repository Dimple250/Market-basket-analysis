#ifndef STYLE_H
#define STYLE_H

#include <QString>

class Style
{
public:
    Style();
    static QString getWindowStyleSheet();
    static QString getTreeviewStyleSheet();
    static QString getTabWidgetStyleSheet();
    static QString getTableViewStyleSheet();
    static QString getTreeviewleftStyleSheet();
    static QString getComboBoxStyleSheet();
};

#endif // STYLE_H
