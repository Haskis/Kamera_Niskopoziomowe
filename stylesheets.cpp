#include <stylesheets.h>


QString StyleSheetBadLineEdit = QString(   "QLineEdit {"
                                "\n color: black;"
                                "\n border-radius: 10px ;"
                                "\n background: qlineargradient(x1:1, y1:0, x2:1, y2:1,"
                                "\n stop:0 white, stop: 0.8 red, stop:1 white);"
                                "\n}"
                                "\n QLineEdit:hover{"
                                "\n background: qlineargradient(x1:1, y1:0, x2:1, y2:1,"
                                "\n stop:0 white, stop: 0.8 lightgreen, stop:1 white);"
                                "\n }");

QString StyleSheetGoodLineEdit = QString(  "QLineEdit {"
                                "\n color: black;"
                                "\n border-radius: 10px ;"
                                "\n background: qlineargradient(x1:1, y1:0, x2:1, y2:1,"
                                "\n stop:0 white, stop: 0.8 white, stop:1 white);"
                                "\n}"
                                "\n QLineEdit:hover{"
                                "\n background: qlineargradient(x1:1, y1:0, x2:1, y2:1,"
                                "\n stop:0 white, stop: 0.8 lightgreen, stop:1 white);"
                                "\n }");
