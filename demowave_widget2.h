#ifndef DEMOWAVE_WIDGET2_H
#define DEMOWAVE_WIDGET2_H

#include <QWidget>
#include <QMainWindow>
#include <qmainwindow.h>
#include "qcustomplot.h"
#include <QTimer>
#include <QThread>
#include <demodulation.h>
#include <mainwindow.h>

#define READ_FLASH_LENGTH 256*1000
#define REGION_DATA_LENGTH 256*100
#define DISPLAY_LENGTH_DEMO 100

using namespace std;

namespace Ui {
class demowave_widget2;
}

class Demodulation;

class demowave_widget2: public QWidget
{
public:
    demowave_widget2(Demodulation *demodulation);
    ~demowave_widget2();

    Ui::demowave_widget2 *ui;
    Demodulation *demodu;
    QTimer* timer_flash;
    int RegionIndex = 0;
    int peakNum=1;
    QCustomPlot *m_customPlot;

    float **DemodataArray = NULL; //存放Demodata[]的数组(二维数组)
    //静态数组
    float Demodata_1[REGION_DATA_LENGTH]={'\0'}; //region1
    float Demodata_2[REGION_DATA_LENGTH]={'\0'}; //region2
    float Demodata_3[REGION_DATA_LENGTH]={'\0'};
    float Demodata_4[REGION_DATA_LENGTH]={'\0'};
    float Demodata_5[REGION_DATA_LENGTH]={'\0'};
    float Demodata_6[REGION_DATA_LENGTH]={'\0'};
    float Demodata_7[REGION_DATA_LENGTH]={'\0'};
    float Demodata_8[REGION_DATA_LENGTH]={'\0'};
    float Demodata_9[REGION_DATA_LENGTH]={'\0'};
    float Demodata_10[REGION_DATA_LENGTH]={'\0'};

    void initWidget();
    void readConfigFile();
    void initComboBox_Region();

public slots:
    void FlashWave();

private slots:
    void on_pushButton_reset_clicked();

};

#endif // DEMOWAVE_WIDGET2_H
