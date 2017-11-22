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
    static QString getAddDataButtonStyleSheet();
    static QString getTableViewStyleSheet();
};

#endif // STYLE_H
