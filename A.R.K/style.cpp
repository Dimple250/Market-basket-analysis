#include "style.h"

Style::Style()
{

}

QString Style::getWindowStyleSheet(){
    return "QWidget { "
           "background-color: #4C5866; "
           "border: 0px solid black; "
            "width:100px;"
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
           "QTabWidget{"

           "height:100px;"
           "}"
            "QTabBar::tab:selected {"
            "margin-top:0px;"
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
            "}"
            /*"QTabWidget::tab-bar"
            "{"
            "alignment: center;"
            "}"*/;
}

QString Style::getTableViewStyleSheet(){
    return  "QTableView{"
            "border: 0px solid white;"
            "background-color:#4C5866;"
            "font-size:17px;"
            //"margin-top:10px;"
            //"margin-left:10px;"
            //"margin-bottom:10px;"
            "}"

            "QTableView::item{"
            "border:0px solid white;"
            "background-color :white;"
            "selection-background-color:yellow;"
            //"padding-right: 40px;"
           // "padding-top: 0px;"
             "color:black;"
            //"padding-bottom: 10px;"
            "}"

            //"QTableView::item {selection-color: black; selection-background-color:green;}"

            //"QTableView::item::hover{"
            //"background-color:#0ABAB5;"
            //"color:black;"
            //"}"

            "QTableView QHeaderView{"
            "font-size:15px;"
            "background-color:#4C5866;"

          "}"
          /* " QHeaderView::section {"
            "background-color:white;"
           " color: white;"
           " border: 0px solid white"
           " padding-left: 4px;"
           " margin-left  : 25px;"

        "}"*/
            "QTableView::selected"
    "{"
  //  "   selection-background-color: yellow;"
    "}"
           ;

}
QString Style::getTreeviewleftStyleSheet(){
    return "QListWidget::item"
    "{"
            //"background-color:#292E3D;"
          //  "border-bottom:2px solid #292E3D;"
            "background-color:#4C5866;"
            "color:white;"
            //style2
           // "background-color:#292E2D;"
           // "color:white;"

            //"color:#FF8229;"
           //"width:100%;"
           "height:60%;"
            "padding-left:20%;"
            "margin-bottom:5px;"
    "}"
      "QListWidget::item::hover"
                "{"
                       //"background-color:#022027;"
                        "background-color:#0ABAB5;"
                       // "background-color:#09ba5d;"
                        //  "background-color:#EB630A;"
                        //"background-color:#013d56;"
                        "color:black;"
                "}"
     "QListWidget::item:selected"
             "{"
                        "background-color:#0ABAB5;"
                        "color:black;"
           " }"
    "QListWidget"
        "{"
                "background-color:#4C5866;"
            //style2
           // "background-color:#4d5655;"
            //style3
            //"background-color:#015645;"
               // "padding-left:-21%;"
                "padding-top:5px;"
                "font-size:20px;"
                "border:0px solid #102C54;"
            //"width:500px;"
              //"margin-right:250px;"
        "}"
         ;
}

QString Style::getComboBoxStyleSheet(){
    return "QComboBox::item"
    "{"
            "background-color:#647387;color:white;"
            "selection-background-color:#0ABAB5;"
            "selection-color:black;"
    "}"

    "QComboBox"
        "{"
               // "background-color:#4C5866;"
                "font-size:15px;"
                //"border:0px solid #102C54;"

        "}"
            "QComboBox::selection"
                "{"
                    "color:black;"
                "}"
    "QComboBox:editable {"
         // " background-color: red;"
          // "color:red;"
        "}"
         ;
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
