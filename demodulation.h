#ifndef DEMODULATION_H
#define DEMODULATION_H

#include <QThread>
#include <mainwindow.h>

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

protected:
        void run();

};

#endif // DEMODULATION_H
