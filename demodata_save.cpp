#include "demodata_save.h"

DemoData_Save::DemoData_Save(Demodulation* demodulation)
{
    m_demodulation = demodulation;

    readConfigFile();
}

void DemoData_Save::readConfigFile()
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

void DemoData_Save::run()
{
    /*------------存储解调数据DEMOdata到本地---------------*/
    dateTime = QDateTime::currentDateTime();

    //文件目录+[Demo]+[peakNum]+时间.bin
    saveFileDemo = QString("D:/Qt_UDP_DAS/data/")+QString("[Demo][")+QString::number(peakNum)+QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");

    outfileDemo.open(saveFileDemo.toStdString().data(), ofstream::binary);

    if (!outfileDemo.is_open()) return;

    int sizeofDEMOdata = m_demodulation->DEMOdata_save->size();

//    qDebug()<<"sizeofDEMOdata = "<<sizeofDEMOdata<<endl;

    for(int i = 0; i<sizeofDEMOdata; i++){
        outfileDemo.write((const char*)m_demodulation->DEMOdata_save->begin(),sizeof(float));

        //如果队列为空，延迟一会，若依然为空，说明没有数据了
         if(m_demodulation->DEMOdata_save->isEmpty()){
             msleep(50);
             if(m_demodulation->DEMOdata_save->isEmpty())
                 break;
         }

        m_demodulation->DEMOdata_save->pop();
    }

    outfileDemo.close();

    //clear DEMOdata_save
//    m_demodulation->DEMOdata_save->clear();
}
