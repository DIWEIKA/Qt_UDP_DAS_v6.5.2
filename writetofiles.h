#ifndef WRITETOFILES_H
#define WRITETOFILES_H

#include <QThread>
#include <QDebug>
#include "ui_mainwindow.h"
#include "mainwindow.h"

class WriteToFiles;
class UDP_Recv;

class WriteToFiles : public QThread
{
public:
    WriteToFiles(UDP_Recv* udp_Recv, int peaknum);
    ~WriteToFiles();
    QString& SaveFilenameAll() {return saveFilenameAll;}
private:
    UDP_Recv* udp_recv;
    QDateTime dateTime; //当前系统时间
    QString saveFilenameAll;
    QString fileAll;
    ofstream outfileAll;
    bool saveFlag;
    int peakNum;


protected:
    //QThread的虚函数
    //线程处理函数
    //不能直接调用，通过start()间接调用
    void run();

signals:

public slots:

};

#endif // WRITETOFILES_H
