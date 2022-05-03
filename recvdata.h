#ifndef RECVDATA_H
#define RECVDATA_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QQueue>
#include "CirQueue.h"
#include <memory>
#include <QMutex>
#include <fstream>
#include <QtNetwork>
#include <sstream>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include "ui_mainwindow.h"
#include "mainwindow.h"

 typedef unsigned char BYTE;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow;
class DealMsg;
class  WriteToFiles;

class Recvdata : public QObject
{
public:
    Recvdata(QUdpSocket *socket, Ui::MainWindow *ui);
    ~Recvdata();

    void readDatagram();//读取udp信息
    void getDatafromByteToFloat();
    void changeFileNameOnce();//初次生成存储文件名

    void changeFileName(); //改变下一个文件的文件名
    void WriteToFilesWith3Channels();

    bool isTimeUpdate;
    void closeStream();

    Ui::MainWindow *UI;

    QUdpSocket *udpSocket;//udpSocket的声明
    qint64 lenoDatagram; //Datagram的长度
    QStringList BufArray;
    qint64 lenoBufArray;
    qint64 LenoUDP = 8192*6000;  //CHdata的长度 最大为9223372036854775807
    string saveFolder;//存储目录（文件夹）
    QString saveFilename1; //CH1存储文件名
    QString saveFilename2;
    QString saveFilename3;

    QString file1;
    QString file2;
    QString file3;

    ofstream outfile1;//CH1
    ofstream outfile2;
    ofstream outfile3;

    QDateTime dateTime; //当前系统时间
    QDateTime nextDateTime;
    bool hasNextFilename;
    QByteArray datagram; //接收UDP的容器
    QString buf; //存放接收数据的缓冲区
    QHostAddress clientAddr;
    quint16 clientPort;
    QMutex writeLock;
    QTimer* udpTimer; //定时器 用来计时1分钟
    BYTE* bufPtr;
    shared_ptr<BYTE*> RECORD_BUF; //接收数据的Buffer
    shared_ptr<CirQueue<float>> CHdata; //存放Channel数据的容器
    shared_ptr<CirQueue<unsigned char>> CHdata2; //测试
    char usCHDATA;

    int PeakNum = 31;//峰值数

public slots:
    void dealMsg(); //slot func
    void TimeUpdate();

private slots:


private:

signals:
    timeout();

};

#endif // RECVDATA_H
