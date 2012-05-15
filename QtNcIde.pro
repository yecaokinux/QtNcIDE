 CONFIG += qt
 #LIBS += -L/usr/local/lib -lFanucCustom.so.1.0
 HEADERS += common/Colors.h
 HEADERS += common/FanucCustom.h
 HEADERS += gui/OutlineDock.h
 HEADERS += gui/MainWindow.h
 HEADERS += gui/CustomTabWidget.h
 
 SOURCES += common/Colors.cpp
 SOURCES += common/FanucCustomIF.cpp
 SOURCES += common/FanucCustom.cpp
 SOURCES += gui/OutlineDock.cpp
 SOURCES += gui/CustomTabWidget.cpp
 SOURCES += gui/MainWindow.cpp
 SOURCES += gui/MainWindowSlots.cpp
 SOURCES += Main.cpp
 RESOURCES       = dockwidgets.qrc

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/mainwindows/dockwidgets
 sources.files = $$SOURCES $$HEADERS $$RESOURCES dockwidgets.pro images
 sources.path = $$[QT_INSTALL_EXAMPLES]/mainwindows/dockwidgets
 INSTALLS += target sources

 symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)