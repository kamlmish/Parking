#ifndef DBBROWSER_H
#define DBBROWSER_H

#include <QObject>

class dbBrowser : public QObject
{
    Q_OBJECT
public:
    dbBrowser(QObject* parent = 0);
    static int nCount;

public:
    ~dbBrowser();
      static dbBrowser* createInstance();

signals:

public slots:
    void slotReceiveText(const QString& text);
};

#endif // DBBROWSER_H
