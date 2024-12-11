########
MOCK_LIB=../../../../mocks_library
########

QT += testlib
QT += gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qt warn_on depend_includepath testcase

CONFIG += c++17


SUBMISSION_PATH = ../submission

DEFINES += ILOVEQT_IMAGE_FULL_PATH=$$absolute_path("../submission/i-love-qt.png")

INCLUDEPATH += $$SUBMISSION_PATH

TEMPLATE = app

SOURCES +=  tests.cpp \
    $$SUBMISSION_PATH/mywindowwithimage.cpp
    $$SUBMISSION_PATH/main.cpp

HEADERS +=  \
    $$SUBMISSION_PATH/mywindowwithimage.h

FORMS += \
    $$SUBMISSION_PATH/mywindowwithimage.ui
