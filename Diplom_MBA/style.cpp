#include "style.h"

Style::Style()
{

}

QString Style::getWindowStyleSheet(){
    return "QWidget { "
           "background-color: #454545; "
           "border: 0px solid black; "

           "}";
}

QString Style::getTreeviewStyleSheet(){
    return "QTreeView {"
           "font-size:15px;"
           "border:0px;"
           "border-top:1px solid gray;"
           "padding-top:7px;"
            //"background-color:red;"
           "}";
}

QString Style::getTabWidgetStyleSheet(){

    return "QTabBar::tab {"
            "width: 120px;"
            "margin-left: 0.5;"
            "margin-right: 0.5;"
            "border: 1px solid #7a7a7a;"
            "border-top-left-radius: 4px;"
            "border-top-right-radius: 4px;"
            "padding: 2px 6px 2px 6px;"
            "}"
            "QTabWidget::pane{"
            "border: 0px;"
            "border-width: 1px;"
            "border-style: solid;"
            "border-color: grey;"
            //"padding-left: 30px;"
            //"padding-top: 30px;"
            "background-color: white;"
            "}"
            "QTabBar::tab:selected {"
            "margin-top: -1px;"
            "background-color: lightblue;"
            "}"
            "QTabBar::tab:!selected:hover {"
            "    background: #999;"
            "}"
            "QTabBar::tab:top:!selected {"
            "    margin-top: 3px;"
            "}"
            "QTabBar::tab:bottom:!selected {"
            "    margin-bottom: 3px;"
            "}"
            "QTabBar::tab:top, QTabBar::tab:bottom {"
            "    min-width: 8ex;"
            "    margin-right: -1px;"
            "    padding: 5px 10px 5px 10px;"
            "}"
            "QTabBar::tab:top:last, QTabBar::tab:bottom:last,"
            "QTabBar::tab:top:only-one, QTabBar::tab:bottom:only-one {"
            "    margin-right: 0;"
            "}"
            "QTabBar::tab:left, QTabBar::tab:right {"
            "    min-height: 8ex;"
            "    margin-bottom: -1px;"
            "    padding: 10px 5px 10px 5px;"
            "}";
}

QString Style::getAddDataButtonStyleSheet(){
    return "QPushButton{ "
           "background-color: blue; "
           "margin-left:50%;"
           "margin-right:50%;"
           "font-size:15px;border:1 solid gray; "
           "border-radius:2%;"
           "}"
           "QPushButton:disabled{ "
           "background-color: yellow; "
           "}"
           "QPushButton:pressed{ "
           "background-color: orange; "
           "}"
           "QPushButton:focus:pressed{ "
           "background-color: black; "
           "}"
           "QPushButton:focus{ "
           "background-color: green; "
           "}"
           "QPushButton:hover{ "
           "background-color: red; "
           "}"
           "QPushButton:checked{ "
           "background-color: pink; "
           "}";
}

QString Style::getTableViewStyleSheet(){
    return  "QTableView{"
            "border: 0px;"
            "background-color:white;"
            "padding-left: 30px;"
            "padding-top: 30px;"
            "width:100px;"
            "}"
            "QTableView::item{"
            "}";

}






/*QScrollBar:vertical {
border: 2px solid green;
background: green;

}
QScrollBar::handle:vertical {
background: green;
min-width: 20px;
}
QScrollBar::add-line:vertical {
background: blue;
width: 16px;
subcontrol-position: right;
subcontrol-origin: margin;
border: 2px solid black;
}
QScrollBar::sub-line:vertical {
background: blue;
width: 16px;
subcontrol-position: top right;
subcontrol-origin: margin;
border: 2px solid black;
position: absolute;
right: 20px;
}
QScrollBar:left-arrow:vertical, QScrollBar::right-arrow:vertical {
width: 3px;
height: 3px;
background: pink;
}*/
