#include "posthttp.h"
#include <QtGlobal>

PostHttp::PostHttp(QObject *parent)
    : QObject(parent),
     m_networkAccessManager(new QNetworkAccessManager(this))
{

}

void PostHttp::setUrl(const QUrl &iUrl)
{
    mUrl = iUrl;
    reply = m_networkAccessManager.get(QNetworkRequest(mUrl));
    ok =  connect(reply, SIGNAL(finished()), this, SLOT(onGetReply()));
}

void PostHttp::post(const QString &body)
  {
    qDebug()<<"KAMLESH POST";

    QNetworkRequest request(mUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

    request.setUrl(mUrl);

    QSslConfiguration config = request.sslConfiguration();
    config.setPeerVerifyMode(QSslSocket::VerifyNone);

    request.setSslConfiguration(config);

    m_networkAccessManager.post(QNetworkRequest(mUrl),body.toUtf8());

  }

void PostHttp::onGetReply()
 {
     qDebug()<<"KAMLESH 22POST";

     QString response;
     if (reply) {
         if (reply->error() == QNetworkReply::NoError) {
             const int available = reply->bytesAvailable();
             if (available > 0) {
                 const QByteArray buffer(reply->readAll());
                 response = QString::fromUtf8(buffer);
             }
         } else {
             response = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
             qDebug() << response;
         }

         reply->deleteLater();
     }

     if (response.trimmed().isEmpty()) {
         response = tr("Unable to retrieve post response");
     }

     emit complete(response);
 }

