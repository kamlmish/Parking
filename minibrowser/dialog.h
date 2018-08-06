#ifndef DIALOG_H
#define DIALOG_H

#include <QObject>
#include <QDebug>

class Dialog : public QObject
{
    Q_OBJECT

public:
    explicit Dialog(QObject *parent = 0)
        : QObject(parent)
    {

    }

    void displayMessage(const QString &message)
    {
        qDebug()<<"Display Message:"<<message;
    }

signals:
    /*!
        This signal is emitted from the C++ side and the text displayed on the HTML client side.
    */
    void sendText(const QString &text);
    void sendToDb(const QString& text);

public slots:
    /*!
        This slot is invoked from the HTML client side and the text displayed on the server side.
    */
    void receiveText(const QString &text)
    {
        keyinp = text;
        emit sendToDb(text);
        displayMessage(tr("Received messageKAM: %1").arg(keyinp));
    }

private slots:
    /*!
        Note that this slot is private and thus not accessible to HTML clients.
    */
    void clicked()
    {
        const QString text = "websocket complete";
        emit sendText(text);
        displayMessage(tr("Sent message: %1").arg(text));
    }

public:
    QString keyinp;

};

#endif // DIALOG_H
