TEMPLATE = app
TARGET = minibrowser

QT += qml quick network webchannel webview websockets  webenginewidgets

SOURCES +=  posthttp.cpp \
    winbrowser.cpp \
    websockettransport.cpp \
    websocketclientwrapper.cpp \
    main.cpp \
    dbbrowser.cpp

RESOURCES += qml.qrc

HEADERS += \
    posthttp.h \
    winbrowser.h \
    dialog.h \
    websockettransport.h \
    websocketclientwrapper.h \
    dbbrowser.h


