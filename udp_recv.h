#ifndef UDP_RECV_H
#define UDP_RECV_H

#include <QThread>
#include <winsock2.h>
#include <mainwindow.h>

#define SaveNumber 40 //定义的CHdata的数量


class UDP_Recv : public QThread
{
    Q_OBJECT
public:
    explicit UDP_Recv(MainWindow* mainwindow);

    MainWindow* mainWindow;


    //winSocket API
    WSADATA wsaData;
    WORD sockVersion;
    SOCKET echo_socket_WIN;
    sockaddr_in addr_WIN;
    sockaddr_in src_addr_WIN;
    int src_addr_len = sizeof(src_addr_WIN);
    int net_pack_size;
    int net_pack_size_HEX;    
    QByteArray p_echo_net_pack_HEX;
    QByteArray p_echo_net_pack_array;
    char p_echo_net_pack[1024];
    char p_echo_net_pack_HEX_data[2048];
    char bufPtr[1024];
    char bufPtrHEX[2048];
    shared_ptr<char*> RECORD_BUF;

    bool isStart;
    bool isASCII;
    bool isHEX;
    bool isStartFrame = 0; //起始帧标识
    QHostAddress clientAddr;
    quint16 clientPort;
    int lenoRecv = 1024;
    qint64 lenoRecvHEX;
    qint64 LenoUDP = 4096*1000; //1s发送的数据个数(Bytes)
    int pack_count = 0;
    int emit_count = 0; //用于计数发送信号的频率
    char pack_HEX_32[2048*32]; //用于存放32帧数据
//    QByteArray pack_HEX_32;

    shared_ptr<CirQueue<unsigned char>> CHdata2;
    shared_ptr<CirQueue<unsigned char>> CHdata3;
    shared_ptr<CirQueue<unsigned char>> CHdata4;
    shared_ptr<CirQueue<unsigned char>> CHdata5;
    shared_ptr<CirQueue<unsigned char>> CHdata6;
    shared_ptr<CirQueue<unsigned char>> CHdata7;
    shared_ptr<CirQueue<unsigned char>> CHdata8;
    shared_ptr<CirQueue<unsigned char>> CHdata9;
    shared_ptr<CirQueue<unsigned char>> CHdata10;
    shared_ptr<CirQueue<unsigned char>> CHdata11;
    shared_ptr<CirQueue<unsigned char>> CHdata12;
    shared_ptr<CirQueue<unsigned char>> CHdata13;
    shared_ptr<CirQueue<unsigned char>> CHdata14;
    shared_ptr<CirQueue<unsigned char>> CHdata15;
    shared_ptr<CirQueue<unsigned char>> CHdata16;
    shared_ptr<CirQueue<unsigned char>> CHdata17;
    shared_ptr<CirQueue<unsigned char>> CHdata18;
    shared_ptr<CirQueue<unsigned char>> CHdata19;
    shared_ptr<CirQueue<unsigned char>> CHdata20;
    shared_ptr<CirQueue<unsigned char>> CHdata21;
    shared_ptr<CirQueue<unsigned char>> CHdata22;
    shared_ptr<CirQueue<unsigned char>> CHdata23;
    shared_ptr<CirQueue<unsigned char>> CHdata24;
    shared_ptr<CirQueue<unsigned char>> CHdata25;
    shared_ptr<CirQueue<unsigned char>> CHdata26;
    shared_ptr<CirQueue<unsigned char>> CHdata27;
    shared_ptr<CirQueue<unsigned char>> CHdata28;
    shared_ptr<CirQueue<unsigned char>> CHdata29;
    shared_ptr<CirQueue<unsigned char>> CHdata30;
    shared_ptr<CirQueue<unsigned char>> CHdata31;
    shared_ptr<CirQueue<unsigned char>> CHdata32;
    shared_ptr<CirQueue<unsigned char>> CHdata33;
    shared_ptr<CirQueue<unsigned char>> CHdata34;
    shared_ptr<CirQueue<unsigned char>> CHdata35;
    shared_ptr<CirQueue<unsigned char>> CHdata36;
    shared_ptr<CirQueue<unsigned char>> CHdata37;
    shared_ptr<CirQueue<unsigned char>> CHdata38;
    shared_ptr<CirQueue<unsigned char>> CHdata39;
    shared_ptr<CirQueue<unsigned char>> CHdata40;
    shared_ptr<CirQueue<unsigned char>> CHdata41;

    shared_ptr<CirQueue<unsigned char>> CHdataArray[SaveNumber]; //存放CHdata的数组

    void clearCHdata();

protected:
    void run();

signals:
    void SendtoWidget(char datagram[]);
//    void SendtoWidget2(QByteArray datagramHEX);
};

#endif // UDP_RECV_H
