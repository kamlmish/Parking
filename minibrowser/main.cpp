
#include <QtCore/QUrl>
#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include <QGuiApplication>
#include <QStyleHints>
#include <QScreen>
#include <QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QtWebView/QtWebView>
#include <QWebChannel>
#include <QWebSocketServer>
#include "winbrowser.h"
#include "websocketclientwrapper.h"
#include "websockettransport.h"
#include "dialog.h"

// Workaround: As of Qt 5.4 QtQuick does not expose QUrl::fromUserInput.
class Utils : public QObject {
    Q_OBJECT
public:
    Utils(QObject* parent = 0) : QObject(parent) { }
    Q_INVOKABLE static QUrl fromUserInput(const QString& userInput);
};

QUrl Utils::fromUserInput(const QString& userInput)
{
    if (userInput.isEmpty())
        return QUrl::fromUserInput("about:blank");
    const QUrl result = QUrl::fromUserInput(userInput);
    return result.isValid() ? result : QUrl::fromUserInput("about:blank");
}

#include "main.moc"

int main(int argc, char *argv[])
{
//! [0]
    QGuiApplication app(argc, argv);

    winBrowser wBrowser;

    QWebSocketServer wbServer("trafficware",QWebSocketServer::NonSecureMode);
    QHostAddress address("localhost");
    if(!wbServer.listen(address,8080))
      {
          qFatal("Failed to open web socket server.");
          return 1;
      }
    const QString initialUrl = "http://localhost:80/index.html";

    // setup the channel
    WebSocketClientWrapper clientWrapper(&wbServer);
    QWebChannel channel;

    QObject::connect(&clientWrapper,&WebSocketClientWrapper::clientConnected,&channel,&QWebChannel::connectTo);

    // setup the dialog and publish it to the QWebChannel

    channel.registerObject(QStringLiteral("core"), wBrowser.dialog);


    QQmlApplicationEngine engine;
    QQmlContext *context = engine.rootContext();
    context->setContextProperty(QStringLiteral("utils"), new Utils(&engine));
    context->setContextProperty(QStringLiteral("initialUrl"),
                                Utils::fromUserInput(initialUrl));
    QRect geometry = QGuiApplication::primaryScreen()->availableGeometry();
    if (!QGuiApplication::styleHints()->showIsFullScreen()) {
        const QSize size = geometry.size() * 4 / 5;
        const QSize offset = (geometry.size() - size) / 2;
        const QPoint pos = geometry.topLeft() + QPoint(offset.width(), offset.height());
        geometry = QRect(pos, size);
    }
    wBrowser.setUrl(initialUrl);
    context->setContextProperty(QStringLiteral("initialX"), geometry.x());
    context->setContextProperty(QStringLiteral("initialY"), geometry.y());
    context->setContextProperty(QStringLiteral("initialWidth"), geometry.width());
    context->setContextProperty(QStringLiteral("initialHeight"), geometry.height());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
