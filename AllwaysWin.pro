#-------------------------------------------------
#
# Project created by QtCreator 2018-06-21T12:30:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AllwaysWin
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++14
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp \
    MainWindow.cpp \
    OdbData/OdbContext.cpp

HEADERS += MainWindow.h \
    OdbData/OdbContext.h \

FORMS += MainWindow.ui
# List of header files that should be compiled with the ODB compiler.
ODB_FILES_PRIVATE += $$files(*.hxx, true)

# ODB compiler flags.
ODB_FLAGS = --database sqlite --profile qt --generate-schema --generate-query --generate-session --std c++14

# Suppress unknown pragmas GCC warnings.
QMAKE_CXXFLAGS_WARN_ON = $$QMAKE_CXXFLAGS_WARN_ON -Wno-unknown-pragmas
QMAKE_CXXFLAGS = $$QMAKE_CXXFLAGS

# Link to the ODB runtime libraries.
LIBS += -lodb-sqlite
LIBS += -lodb-qt
LIBS += -lodb

# Add the Qt headers directory to the ODB include directory list.
ODB_FLAGS += -I$$[QT_INSTALL_HEADERS]

# Newer versions of QtCreator do builds in a separate directory. As a
# result, we need to append the source directory to ODB files.
for(dir, ODB_FILES_PRIVATE) {
    found = $$find(dir, -odb)
    isEmpty(found) {
        ODB_PWD_FILES += $$PWD/$${dir}
        HEADERS += $$dir
    }
}

defineReplace(generateFileNamesClean) {
    return($${1}/$${2}-odb.hxx $${1}/$${2}-odb.cxx $${1}/$${2}-odb.ixx $${1}/$${2}.sql)
}

odb.name = odb ${QMAKE_FILE_IN}
odb.input = ODB_PWD_FILES
odb.output = ${QMAKE_FILE_PATH}/${QMAKE_FILE_BASE}-odb.cxx
odb.commands = odb -x -fPIC --output-dir ${QMAKE_FILE_PATH} $$ODB_FLAGS ${QMAKE_FILE_IN}
odb.depends = $$ODB_PWD_FILES
odb.variable_out = SOURCES
odb.clean = $$generateFileNamesClean(${QMAKE_FILE_PATH}, ${QMAKE_FILE_BASE})
QMAKE_EXTRA_COMPILERS += odb
