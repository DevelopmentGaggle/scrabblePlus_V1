QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    blankpopup.cpp \
    BoardTile.cpp \
    Game.cpp

HEADERS += \
    mainwindow.h \
    blankpopup.h \
    BoardTile.h \
    Game.h

FORMS += \
    mainwindow.ui \
    blankpopup.ui
RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../opencv/build/x64/vc15/lib/ -lopencv_world455
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../opencv/build/x64/vc15/lib/ -lopencv_world455d
else:unix: LIBS += -L$$PWD/../../../../opencv/build/x64/vc15/lib/ -lopencv_world455

INCLUDEPATH += $$PWD/../../../../opencv/build/include
DEPENDPATH += $$PWD/../../../../opencv/build/include

unix|win32: LIBS += -L$$PWD/../../../../../vcpkg/installed/x64-windows/lib/ -ltesseract41
LIBS += -L$$PWD/../../../../../vcpkg/installed/x64-windows/lib/ -lleptonica-1.81.1.lib

INCLUDEPATH += $$PWD/../../../../../vcpkg/installed/x64-windows/include
DEPENDPATH += $$PWD/../../../../../vcpkg/installed/x64-windows/include
