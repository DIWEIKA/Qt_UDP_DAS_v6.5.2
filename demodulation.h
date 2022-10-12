#ifndef DEMODULATION_H
#define DEMODULATION_H

#include <QThread>
#include <mainwindow.h>

#define READ_LENGTH 16*300
#define CHDATA_ALL_LENGTH 4*300
#define CHDATA_LENGTH 1*300
#define NUMTABLE 201
#define FILTERODR 6
#define LPFILTERODR 10

class UDP_Recv;

class Demodulation : public QThread
{
    Q_OBJECT
public:
    Demodulation(UDP_Recv* udp_Recv,int DemoFlashTime, int DemoFlashFreq, int freq, int peaknum);
    ~Demodulation();

    UDP_Recv* udp_recv;
    shared_ptr<CirQueue<float>> DEMOdata_flash;
    shared_ptr<CirQueue<float>> DEMOdata_save;
//    CirQueue<float> DEMOdata_save2;
    float DEMOdata_display[2048];
    char* demo_CHdatax= new char[2048];

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
    char demo_CHdata[READ_LENGTH];
    float Vi[CHDATA_LENGTH];
    float Vq[CHDATA_LENGTH];
    float Ph[CHDATA_LENGTH];
    float atanTable[NUMTABLE];
    int sizeoCHdata;
    int sizeoCHdataDec;
    const static int FrameLen = 2048; //最大区域数目
    int demo_CHdata_DEC_all[FrameLen/4];
    int demo_CHdata_DEC_1[FrameLen/16];
    int demo_CHdata_DEC_2[FrameLen/16];
    int demo_CHdata_DEC_3[FrameLen/16];
    int demo_CHdata_DEC_4[FrameLen/16];

    int demoFlashTime;
    int demoFlashFreq;
    int Freq;
    int peakNum;

    float* RealPh;
    float* PriorPh;
    float* K;
    float* PriorK;

    int count = 0;

    void readAtanTable(float *roundNum);
    float demoduPh(float vi,float vq);
    float Unwrap(float Ph, int i);

    float (*RealPhReg)[FILTERODR];
    float (*RealPhOut)[FILTERODR];
//    float (*FilterReg)[LPFILTERODR];
    float *HPFilterCoeff;
//    float *LPFilterCoeff;
    unsigned long *cnt; //滤波执行计数
    float *FirstRealPh;
    int *FirstIn_n;

    void FreeMemory();

    void ReadFilterCoeff(float *HPFcoeff/*,float *LPFcoeff*/);

    void Hpfilter(int i);

protected:
    void run();

};

#endif // DEMODULATION_H
