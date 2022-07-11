/**
 *  使用QChart、QChartView和QLineSeries显示的折线图，弃用
 * */

#ifndef DEMOWAVE_WIDGET_H
#define DEMOWAVE_WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <qmainwindow.h>
#include <QTimer>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include <QSplineSeries>
#include <QLineSeries>
#include <QAbstractAxis>
#include <QThread>
#include <demodulation.h>
#include <mainwindow.h>

#define READ_FLASH_LENGTH 256*1000
#define REGION_DATA_LENGTH 256*100
#define DISPLAY_LENGTH_DEMO 100

using namespace std;

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class demowave_widget;
}

class Demodulation;

class demowave_widget : public QWidget
{
    Q_OBJECT

public:
    explicit demowave_widget(Demodulation *demodulation);
    ~demowave_widget();

    Demodulation *demodu;
    QTimer* timer_flash;
    QChart* m_chart;
    QValueAxis *m_axisX, *m_axisY;
    QLineSeries* m_lineSeries;
    int RegionIndex = 0;
    const int AXIS_MAX_X = DISPLAY_LENGTH_DEMO, AXIS_MAX_Y = 5;
    int peakNum=1;

    float **DemodataArray = NULL; //存放Demodata[]的数组(二维数组)

    //动态数组
//    float *Demodata_1; //region1
//    float *Demodata_2; //region2
//    float *Demodata_3;
//    float *Demodata_4;
//    float *Demodata_5;
//    float *Demodata_6;
//    float *Demodata_7;
//    float *Demodata_8;
//    float *Demodata_9;
//    float *Demodata_10;

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

private:
    Ui::demowave_widget *ui;
};

#endif // DEMOWAVE_WIDGET_H
