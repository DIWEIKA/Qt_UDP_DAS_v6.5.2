#include "writetofiles.h"

WriteToFiles::WriteToFiles(UDP_Recv* udp_Recv)
{
    udp_recv = udp_Recv;

    CHdata = make_shared<CirQueue<unsigned char>>(udp_recv->LenoUDP);

    Phdata = make_shared<CirQueue<float>>(CHDATA_LENGTH);
}

void WriteToFiles::run()
{
    qDebug() << "TimeUpdate" << endl;

    //更新当前时间
    dateTime = QDateTime::currentDateTime();

    saveFolder =  string("F:/Desktop/UDPConnect/data/");

    saveFilenameAll = QString(saveFolder.c_str())+QString("[All][")+QString::number(PeakNum)
            +QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");

    saveFileDemo = QString(saveFolder.c_str())+QString("[Demo]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");

    //存储三通道原始数据
    if(saveFlag){
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
        qDebug()<<"3 Channels data writing over ! "<<endl;
    }

    //存储解调数据
    if(demoFlag){
        outfileDemo.open(saveFileDemo.toStdString().data(), ofstream::binary);

        if (!outfileDemo.is_open()) return;

        unsigned int sizeoPhata = Phdata->size();

        for(unsigned int j=0; j<sizeoPhata; ++j){
            outfileDemo.write((const char*)Phdata->begin(),sizeof(float));
            Phdata->pop();
        }

        Phdata->clear();

        outfileDemo.close();
        qDebug()<<"Phase data writing over ! "<<endl;
    }

    qDebug()<< "WriteToFiles Thread is Finished ! "<<endl;
    qDebug()<<"-----------------------------------"<<endl;
}

void WriteToFiles::recvPhSlot(float Ph[])
{
    qDebug()<<"RecvPhSlot Responsed ! "<<endl;

    //ph[] >> Phdata
    for(int i = 0; i<CHDATA_LENGTH; i++){
        float iPhdata = Ph[i];
        Phdata->push(iPhdata);
    }
}

