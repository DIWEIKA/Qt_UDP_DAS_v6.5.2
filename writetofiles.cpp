#include "writetofiles.h"

WriteToFiles::WriteToFiles(UDP_Recv* udp_Recv)
{
    udp_recv = udp_Recv;

    CHdata = make_shared<CirQueue<unsigned char>>(udp_recv->LenoUDP);

    readConfigFile();
}

void WriteToFiles::readConfigFile()
{
    QString filePath = QString("C:/Qt_UDP_DAS/peak.txt");
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the Configration file!"<<endl;
    }
   QByteArray configData = file.readAll(); //读取所有数据
   char peakNumChar_shiwei = configData[3]; //peakNum的十位存放在第四个位置
   char peakNumChar_gewei = configData[4]; //peakNum的个位存放在第四个位置
   bool ok;
   peakNum =  QString(peakNumChar_shiwei).toInt(&ok,16)*10 + QString(peakNumChar_gewei).toInt(&ok,16)*1;
}

void WriteToFiles::run()
{
    qDebug() << "TimeUpdate" << endl;

    dateTime = QDateTime::currentDateTime();

     //文件目录+[4CH]+[peakNum]+时间.bin
    saveFilenameAll = QString("D:/Qt_UDP_DAS/data/")+QString("[4CH][")+QString::number(peakNum)+QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");

    outfileAll.open(saveFilenameAll.toStdString().data(), ofstream::binary);

    if (!outfileAll.is_open()) return;

    for(int i = 0; i< SaveNumber; i++){

        if(udp_recv->CHdataArray[i]->isEmpty())
            break;
        else
        {
            unsigned int sizeoCHdata = udp_recv->CHdataArray[i]->size();

            for(unsigned int j=0; j<sizeoCHdata; ++j){
                outfileAll.write((const char*)udp_recv->CHdataArray[i]->begin(),sizeof(unsigned char));

                //如果队列为空，延迟一会，若依然为空，说明没有数据了
                 if(udp_recv->CHdataArray[i]->isEmpty()){
                     sleep(50);
                     if(udp_recv->CHdataArray[i]->isEmpty())
                         break;
                 }

                udp_recv->CHdataArray[i]->pop();
            }
//            udp_recv->CHdataArray[i]->clear();
        }
    }

    outfileAll.close();

    qDebug()<< "WriteToFiles Thread is Finished ! "<<endl;
    qDebug()<<"-----------------------------------"<<endl;
}


