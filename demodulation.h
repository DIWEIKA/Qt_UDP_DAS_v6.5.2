#ifndef DEMODULATION_H
#define DEMODULATION_H

#include <QThread>
#include <mainwindow.h>

#define READ_LENGTH 1024*32 //从CHdataX里读取的数据长度
#define CHDATA_ALL_LENGTH 1024*8 //四个通道的十进制数数据长度
#define CHDATA_LENGTH 1024*2 //一个通道的十进制数长度
#define NUMTABLE 201

class Demodulation : public QThread
{
    Q_OBJECT
public:
    explicit Demodulation(shared_ptr<CirQueue<unsigned char>> CHdataX);

    shared_ptr<CirQueue<unsigned char>> CHdata;
    char demo_CHdata[4096*1000]= {'\0'};
    int Vi[4096*1000] = {0};
    int Vq[4096*1000]= {0};
    int Ph[4096*1000]= {0};
    float atanTable[NUMTABLE]= {0};
    int sizeoCHdata;
    int demo_CHdata_DEC_all[CHDATA_ALL_LENGTH]= {0};
    int sizeoCHdataDec;
    int demo_CHdata_DEC_1[CHDATA_LENGTH]= {0};
    int demo_CHdata_DEC_2[CHDATA_LENGTH]= {0};
    int demo_CHdata_DEC_3[CHDATA_LENGTH]= {0};
    int demo_CHdata_DEC_4[CHDATA_LENGTH]= {0};
    int sizeoDemoCHdata;

    void readAtanTable(float *roundNum);
    float demoduPh(float vi,float vq);

signals:
    void sendPhToWrite(int ph[]); //将解调的相位信号发送给writeToFiles类

protected:
        void run();

};

#endif // DEMODULATION_H
