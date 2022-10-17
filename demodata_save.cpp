#include "demodata_save.h"

DemoData_Save::DemoData_Save(Demodulation* demodulation)
    :m_demodulation(demodulation),
    peakNum(m_demodulation->peakNum)
{

}



void DemoData_Save::run()
{
    /*------------存储解调数据DEMOdata到本地---------------*/
    dateTime = QDateTime::currentDateTime();

    //change savetime to last minute
    QString mm = dateTime.toString("mm");
    bool odk;
    int m1 = mm.toInt(&odk,10);
//    qDebug()<<"m1 = "<<m1<<endl;
    int m2 = m1-1;
    if(m2<0) m2 = 59;
//    qDebug() <<"m2 = "<<m2<<endl;
    QString mm2 = QString::number(m2,10);
    if(m2 < 10) mm2 = QString("0") + mm2;
//    qDebug() <<"mm2:"<<mm2<<endl;

    //文件目录+[Demo]+[peakNum]+时间.bin
    saveFileDemo = QString("D:/Qt_UDP_DAS/data/")+QString("[Demo][")+QString::number(peakNum)+QString("]")
            + dateTime.toString("yyyyMMddhh")+ mm2 + QString("00.bin");

    outfileDemo.open(saveFileDemo.toStdString().data(), ofstream::binary);

    if (!outfileDemo.is_open()) return;

    int sizeofDEMOdata = m_demodulation->DEMOdata_save->size();

//    qDebug()<<"sizeofDEMOdata = "<<sizeofDEMOdata<<endl;

    for(int i = 0; i<sizeofDEMOdata; i++){
        outfileDemo.write((const char*)m_demodulation->DEMOdata_save->begin(),sizeof(float));

        //如果队列为空，延迟一会，若依然为空，说明没有数据了
         if(m_demodulation->DEMOdata_save->isEmpty()){
             msleep(3);
             if(m_demodulation->DEMOdata_save->isEmpty())
                 break;
         }

        m_demodulation->DEMOdata_save->pop();
    }

    outfileDemo.close();

    //clear DEMOdata_save
//    m_demodulation->DEMOdata_save->clear();
}
