#include "recvdata.h"

Recvdata::Recvdata(QUdpSocket *socket, Ui::MainWindow *ui)
{
    udpSocket = socket;

    UI = ui;

    //CHdata初始化 。
    CHdata=make_shared<CirQueue<float>>(LenoUDP);

    CHdata2 = make_shared<CirQueue<unsigned char>>(LenoUDP);
}

Recvdata::~Recvdata()
{

}

void Recvdata:: dealMsg()
{
    while(udpSocket->hasPendingDatagrams()){
        //发送的UDP数据包的大小
        qDebug()<<"pending UDP datagram size = "<< udpSocket->pendingDatagramSize();

         UI->textEdit_Msg->insertPlainText("Pending...");

        //datagram << UDP
       readDatagram();

       //release bufPtr
        delete bufPtr;
        bufPtr = NULL;

       //define a new BYTE[]
       bufPtr = new BYTE[lenoDatagram]();

        //define a new RECORD_BUF
       RECORD_BUF = make_shared<BYTE*>(bufPtr);

       //RECORD_BUF << datagram
       memcpy(*RECORD_BUF,datagram.data(),sizeof(BYTE)*lenoDatagram);

       //CHData << RECORD_BUF
       getDatafromByteToFloat();

    }

}

void Recvdata::readDatagram()
{

}

void Recvdata:: changeFileNameOnce()
{

}

void Recvdata::getDatafromByteToFloat()
{

}

void Recvdata:: WriteToFilesWith3Channels()
{

}

void Recvdata::closeStream()
{

}


