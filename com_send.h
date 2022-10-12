#ifndef COM_SEND_H
#define COM_SEND_H

#include <QThread>
#include <mainwindow.h>
#include "win_qextserialport.h"
#include "qextserialbase.h"

class COM_Send : public QThread
{
    Q_OBJECT
public:
    COM_Send(MainWindow*);

    MainWindow* mainWindow;
    Win_QextSerialPort* myCom;
    QString filePath;
    QFile* configFile;
    QByteArray peakData;

protected:
        void run();

signals:

};

#endif // COM_SEND_H
