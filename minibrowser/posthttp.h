#ifndef POSTHTTP_H
#define POSTHTTP_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class QNetworkAccessManager;

class PostHttp : public QObject
{
    Q_OBJECT
public:
    PostHttp(QObject* parent = 0);
    void setUrl(const QUrl& iUrl);

public Q_SLOTS:
    void post(const QString &body);

Q_SIGNALS:
    void complete(const QString &info);

public slots:
    void onGetReply();

private:
    QNetworkAccessManager m_networkAccessManager;
    QNetworkReply* reply;
    QUrl mUrl;
    bool ok;
};

#endif // POSTHTTP_H
