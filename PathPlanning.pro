TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_LFLAGS += -static -static-libgcc -static-libstdc++

SOURCES += \
        astar.cpp \
        dijkstra.cpp \
        input.cpp \
        main.cpp

HEADERS += \
    astar.h \
    dijkstra.h \
    input.h \
    structures.h
