#ifndef DEMODULATION_H
#define DEMODULATION_H

#include <QThread>
#include <mainwindow.h>

#define READ_LENGTH 4096*1000
#define CHDATA_ALL_LENGTH 1024*1000
#define CHDATA_LENGTH 256*1000
#define NUMTABLE 201

class UDP_Recv;

class Demodulation : public QThread
{
    Q_OBJECT
public:
    explicit Demodulation(UDP_Recv* udp_Recv);

    UDP_Recv* udp_recv;
    shared_ptr<CirQueue<float>> DEMOdata_flash;
    shared_ptr<CirQueue<float>> DEMOdata_save;
    float DEMOdata_display[2048];

    //动态数组
//    unsigned char *demo_CHdata;
//    float *Vi;
//    float *Vq;
//    float *Ph;
//    float *atanTable;
//    int sizeoCHdata;
//    int sizeoCHdataDec;
//    int *demo_CHdata_DEC_all;
//    int *demo_CHdata_DEC_1;
//    int *demo_CHdata_DEC_2;
//    int *demo_CHdata_DEC_3;
//    int *demo_CHdata_DEC_4;

    //静态数组
    unsigned char demo_CHdata[READ_LENGTH];
    float Vi[CHDATA_LENGTH];
    float Vq[CHDATA_LENGTH];
    float Ph[CHDATA_LENGTH];
    float atanTable[NUMTABLE];
    int sizeoCHdata;
    int sizeoCHdataDec;
    int demo_CHdata_DEC_all[CHDATA_ALL_LENGTH];
    int demo_CHdata_DEC_1[CHDATA_LENGTH];
    int demo_CHdata_DEC_2[CHDATA_LENGTH];
    int demo_CHdata_DEC_3[CHDATA_LENGTH];
    int demo_CHdata_DEC_4[CHDATA_LENGTH];

    int Freq = 10*1000; //采样率10KHz
    int peakNum;
    unsigned long LenoDemo = 256*100;
    unsigned long LenoDemoSave = 256*1000*100;

    float* RealPh;
    float* PriorPh;
    float* K;
    float* PriorK;

    int count = 0;

    void readConfigFile();
    void readAtanTable(float *roundNum);
    float demoduPh(float vi,float vq);
    float Unwrap(float Ph, int i);

protected:
    void run();

};

#endif // DEMODULATION_H
