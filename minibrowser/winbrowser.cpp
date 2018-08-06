#include "winbrowser.h"
#include <QtWebView>


winBrowser::winBrowser(QWindow* parent):
    QQuickView(parent)
{
    QtWebView::initialize();
    dialog = new Dialog(this);
    pHttp = new PostHttp(this);
    mdbBrowser = dbBrowser::createInstance();
    connections();

}

winBrowser::~winBrowser()
{
    delete pHttp;
}

void winBrowser::connections()
{
    connect(dialog,SIGNAL(sendToDb(QString)),mdbBrowser,SLOT(slotReceiveText(QString)));
}


void winBrowser::setUrl(const QString &sUrl)
{
    mUrl = new QUrl(sUrl);
    pHttp->setUrl(sUrl);
}
