#include "demodata_save.h"

DemoData_Save::DemoData_Save(Demodulation* demodulation)
{
    m_demodulation = demodulation;

    readConfigFile();
}

void DemoData_Save::readConfigFile()
{
    QString filePath = QDir::currentPath()+QString("/peak.txt"); //build所在目录下
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the Configration file!"<<endl;
    }
    QByteArray configData = file.readAll(); //读取所有数据
    char peakNumChar = configData[3]; //peakNum存放在第四个位置
    bool ok;
    peakNum =  QString(peakNumChar).toInt(&ok,16);
}

void DemoData_Save::run()
{
    /*------------存储解调数据DEMOdata到本地---------------*/
    dateTime = QDateTime::currentDateTime();

    //文件目录+[Demo]+[peakNum]+时间.bin
    saveFileDemo = QString("F:/Desktop/Qt_UDP_DAS/data/")+QString("[Demo][")+QString::number(peakNum)+QString("]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");

    outfileDemo.open(saveFileDemo.toStdString().data(), ofstream::binary);

    if (!outfileDemo.is_open()) return;

    int sizeofDEMOdata = m_demodulation->DEMOdata_save->size();

    qDebug()<<"sizeofDEMOdata = "<<sizeofDEMOdata<<endl;

    for(unsigned int i = 0; i<sizeofDEMOdata/sizeof(float); i++){ //这里一次写入四个字节，因此写入次数要/4
        outfileDemo.write((const char*)m_demodulation->DEMOdata_save->begin(),sizeof(float));
        m_demodulation->DEMOdata_save->pop();
    }

    outfileDemo.close();

    //clear DEMOdata_save
    m_demodulation->DEMOdata_save->clear();
}
