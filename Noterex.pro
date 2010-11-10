#-------------------------------------------------
#
# Project created by QtCreator 2010-09-02T15:15:16
#
#-------------------------------------------------

QT       += core gui sql

TARGET = Noterex
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    noteedit.cpp \
    data/content.cpp \
    model\basketmodel.cpp \
    baskettree.cpp \
    data/basket.cpp \
    data/basketroot.cpp \
    model/contentmodel.cpp \
    widget/notewidget.cpp \
    application.cpp \
    model/noteviewmodel.cpp \
    index/document.cpp \
    index/tokenizer.cpp \
    model/notesearchmodel.cpp \
    note/notedata.cpp \
    note/notedb.cpp \
    note/notegui.cpp \
    note/noteindexor.cpp \
    note/standardnotedistributor.cpp \
    note/searchnotedistributor.cpp \
    index/standardsearcher.cpp \
    index/indexallaction.cpp \
    database/databasecreator.cpp \
    database/createdatabaseaction.cpp \
    database/opendatabaseaction.cpp \
    note/tagdata.cpp \
    note/daofactorysql.cpp \
    note/notedaosql.cpp

HEADERS  += mainwindow.h \
    noteedit.h \
    data/content.h \
    model\basketmodel.h \
    baskettree.h \
    data/basket.h \
    data/basketroot.h \
    model/contentmodel.h \
    widget/notewidget.h \
    application.h \
    data/data.h \
    data/Table.h \
    model/noteviewmodel.h \
    index/document.h \
    index/tokenizer.h \
    index/searcher.h \
    model/notesearchmodel.h \
    data/typedefs.h \
    note/notedata.h \
    note/notedb.h \
    note/notegui.h \
    note/noteindexor.h \
    note/notedistributor.h \
    note/standardnotedistributor.h \
    note/searchnotedistributor.h \
    index/standardsearcher.h \
    note/note.h \
    index/indexallaction.h \
    database/databasecreator.h \
    database/createdatabaseaction.h \
    database/opendatabaseaction.h \
    note/tagdata.h \
    note/notedao.h \
    note/daofactory.h \
    note/daofactorysql.h \
    note/notedaosql.h

FORMS    += mainwindow.ui
