#include "dbbrowser.h"
#include <QObject>
#include <QDebug>


int dbBrowser::nCount = 0;

dbBrowser::dbBrowser(QObject *parent):
    QObject(parent)
{

}

dbBrowser* dbBrowser::createInstance()
{
    if(nCount == 0)
    {
        nCount++;
        return new dbBrowser;
    }
    else
    {

    }
}

dbBrowser::~dbBrowser()
{
}

void dbBrowser::slotReceiveText(const QString &text)
{
    qDebug()<<"KAMLEHHAHAH:"<<text;
}
