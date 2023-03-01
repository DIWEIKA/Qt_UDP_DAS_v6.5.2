#include "writetofiles.h"

WriteToFiles::WriteToFiles(UDP_Recv* udp_Recv, int peaknum):
    udp_recv(udp_Recv),
    saveFlag(false),
    peakNum(peaknum)
{

}

/*----------------保存模式二中的四通道原始数据----------------*/
void WriteToFiles::run()
{
    qDebug() << "TimeUpdate" << endl;

    dateTime = QDateTime::currentDateTime();

    //change savetime to last minute
    QString mm = dateTime.toString("mm");
    bool odk;
    int m1 = mm.toInt(&odk,10);
    int m2 = m1-1;
    if(m2<0) m2 = 59;
    QString mm2 = QString::number(m2,10);
    if(m2 < 10) mm2 = QString("0") + mm2;

    //文件目录+[4CH]+[peakNum]+时间.txt
    saveFilenameAll = QString("D:/Qt_UDP_DAS/data/")+QString("[4CH][")+QString::number(peakNum)+QString("]")
            + dateTime.toString("yyyyMMddhh")+ mm2 + QString("00.txt");

    outfileAll.open(saveFilenameAll.toStdString().data(), ofstream::binary);

    if (!outfileAll.is_open()) return;

    for(int i = 0; i< SaveNum; i++){

        if(udp_recv->Get_CHdataArray()[i]->isEmpty())
            break;
        else
        {
            unsigned int sizeoCHdata = udp_recv->Get_CHdataArray()[i]->size();

            for(unsigned int j=0; j<sizeoCHdata; ++j){
                outfileAll.write((const char*)udp_recv->Get_CHdataArray()[i]->begin(),sizeof(unsigned char));

                //如果队列为空，延迟一会，若依然为空，说明没有数据了
                 if(udp_recv->Get_CHdataArray()[i]->isEmpty()){
                     msleep(3);
                     if(udp_recv->Get_CHdataArray()[i]->isEmpty())
                         break;
                 }

                udp_recv->Get_CHdataArray()[i]->pop();
            }

        }
    }

    outfileAll.close();

    qDebug()<< "WriteToFiles Thread is Finished ! "<<endl;
    qDebug()<<"-----------------------------------"<<endl;
}


