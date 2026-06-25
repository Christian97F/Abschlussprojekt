QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    database.cpp

HEADERS += \
    mainwindow.h \
    database.h \
    queryresult.h \
    config.h

FORMS += \
    mainwindow.ui

# =====================================================================
#  MySQL C API (Connector/C) anbinden
#  ---------------------------------------------------------------------
#  Pfad wurde auf dieser Installation gefunden:
#     C:/Program Files/MySQL/MySQL Server 8.0
#  Darin:
#     include/mysql.h        (Header)
#     lib/libmysql.dll       (Bibliothek)
#
#  MinGW linkt am zuverlaessigsten DIREKT gegen die DLL (-l:libmysql.dll),
#  weil die mitgelieferte libmysql.lib im MSVC-Format vorliegt.
#
# =====================================================================
MYSQL_DIR = "C:/Program Files/MySQL/MySQL Server 8.0"

INCLUDEPATH += "$$MYSQL_DIR/include"
LIBS += -L"$$MYSQL_DIR/lib" -l:libmysql.dll

# Ausgabeordner festlegen, damit klar ist, wo die .exe landet.
CONFIG(debug, debug|release) {
    DESTDIR = $$OUT_PWD/debug
} else {
    DESTDIR = $$OUT_PWD/release
}

# libmysql.dll nach dem Linken automatisch neben die .exe kopieren,
# sonst startet das Programm nicht.
QMAKE_POST_LINK += $$quote(cmd /c copy /Y \"$$shell_path($$MYSQL_DIR/lib/libmysql.dll)\" \"$$shell_path($$DESTDIR)\"$$escape_expand(\\n\\t))

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
