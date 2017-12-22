#-------------------------------------------------
#
# Project created by QtCreator 2017-12-12T21:24:01
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia multimediawidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bledard
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
    rubble.cpp \
    player.cpp \
    soundicon.cpp \
    police.cpp \
    drowning_man.cpp \
    game.cpp \
    button.cpp \
    lifebuoy.cpp \
    health.cpp \
    target.cpp \
    score.cpp

HEADERS += \
    player.h \
    declarations.h \
    drowning_man.h \
    police.h \
    rubble.h \
    game.h \
    lifebuoy.h \
    soundicon.h \
    button.h \
    target.h \
    health.h \
    score.h
RC_ICONS = myappico.ico
FORMS +=

RESOURCES += \
    resources.qrc

