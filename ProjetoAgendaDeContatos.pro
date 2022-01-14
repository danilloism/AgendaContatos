#-------------------------------------------------
#
# Project created by QtCreator 2018-11-01T07:27:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjetoAgendaDeContatos
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    teladelistagem.cpp \
    contatodao.cpp \
    mapeardados.cpp \
    geradorid.cpp \
    contato.cpp \
    telefone.cpp \
    endereco.cpp \
    email.cpp \
    teladeedicao.cpp

HEADERS += \
        mainwindow.h \
    teladelistagem.h \
    crud.h \
    contatodao.h \
    mapeardados.h \
    geradorid.h \
    contato.h \
    telefone.h \
    endereco.h \
    email.h \
    teladeedicao.h

FORMS += \
        mainwindow.ui \
    teladelistagem.ui \
    teladeedicao.ui
