#include "writetofiles.h"

WriteToFiles::WriteToFiles(UDP_Recv* udp_Recv)
{
    udp_recv = udp_Recv;

    CHdata = make_shared<CirQueue<unsigned char>>(udp_recv->LenoUDP);
}

void WriteToFiles::run()
{
    qDebug() << "TimeUpdate" << endl;

    //更新当前时间
    dateTime = QDateTime::currentDateTime();

    saveFilenameAll = QString("F:/Desktop/UDPConnect/data/")+QString("[All]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");

    //存储三通道原始数据
    outfileAll.open(saveFilenameAll.toStdString().data(), ofstream::binary);

    //打开文件失败则结束运行
    if (!outfileAll.is_open()) return;

    for(int i = 0; i< SaveNumber; i++){

        if(udp_recv->CHdataArray[i]->isEmpty())
            continue;
        else
        {
            unsigned int sizeoCHdata = udp_recv->CHdataArray[i]->size();

            for(unsigned int j=0; j<sizeoCHdata; ++j){
                outfileAll.write((const char*)udp_recv->CHdataArray[i]->begin(),sizeof(unsigned char));
                udp_recv->CHdataArray[i]->pop();
            }
            udp_recv->CHdataArray[i]->clear();
        }
    }

    outfileAll.close();

    qDebug()<< "WriteToFiles Thread is Finished ! "<<endl;
    qDebug()<<"-----------------------------------"<<endl;
}


