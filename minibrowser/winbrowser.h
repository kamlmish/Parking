#ifndef WINBROWSER_H
#define WINBROWSER_H

#include <QObject>
#include <QQuickView>
#include "posthttp.h"
#include "dialog.h"
#include "dbbrowser.h"

class winBrowser : public QQuickView
{
    Q_OBJECT
public:
    winBrowser(QWindow* parent = 0);
    ~winBrowser();
    void setUrl(const QString& sUrl);
    void connections();
public:
    PostHttp* pHttp;
    QUrl* mUrl;
    Dialog* dialog;
    dbBrowser* mdbBrowser;
};

#endif // WINBROWSER_H
