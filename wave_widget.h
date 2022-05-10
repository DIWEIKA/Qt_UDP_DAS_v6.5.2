#ifndef WAVE_WIDGET_H
#define WAVE_WIDGET_H

#include <QWidget>
#include <QMainWindow>
#include <qmainwindow.h>
#include <QTimer>
#include <QChartView>
#include <QValueAxis>
#include <QLineSeries>
#include <QSplineSeries>
#include <fstream>
#include <sstream>
#include <mainwindow.h>
#include "udp_recv.h"
#include <ctime>

#define READ_LENGTH 1024*32 //从CHdataX里读取的数据长度
#define PULSEDATA_ALL_LENGTH 1024*8 //四个通道的十进制数数据长度
#define PULSEDATA_LENGTH 1024*2 //一个通道的十进制数长度
#define DISPLAY_LENGTH 512*2 //展示在widget上的数据长度
#define SaveNumber 40 //存储容器的个数

using namespace std;

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class wave_widget;
}

class wave_widget : public QWidget
{
    Q_OBJECT

public:
    wave_widget();
    ~wave_widget();

    QTimer* m_timer;
    QChart* m_chart;
    QValueAxis *m_axisX, *m_axisY;
    QSplineSeries* m_lineSeries;
    int index = 0;
    const int AXIS_MAX_X = DISPLAY_LENGTH, AXIS_MAX_Y = 800;
    int sizeoPulsedata ;
    int sizeoPulsedataDec;
    qint64 LenoUDP = READ_LENGTH;
    int ChannelIndex;

    QVector<QPointF> pointsSeries;
    QString saveFolder;
    QString saveFilenameAll;
    ifstream infileAll;
    //    //ASCII接收
    //    char Pulsedata[READ_LENGTH]= {'\0'};
    //    int Pulsedata_DEC_all[PULSEDATA_ALL_LENGTH] =  {0};
    //    int Pulsedata_DEC_1[PULSEDATA_LENGTH]= {0};
    //    int Pulsedata_DEC_2[PULSEDATA_LENGTH] =  {0};
    //    int Pulsedata_DEC_3[PULSEDATA_LENGTH] =  {0};
    //    int Pulsedata_DEC_4[PULSEDATA_LENGTH] =  {0};
    //HEX接收
    char PulsedataHEX[READ_LENGTH*2] = {'\0'};
    int Pulsedata_DEC_all_HEX[PULSEDATA_ALL_LENGTH*2] =  {0};
    int Pulsedata_DEC_1_HEX[PULSEDATA_LENGTH*2]= {0};
    int Pulsedata_DEC_2_HEX[PULSEDATA_LENGTH*2] =  {0};
    int Pulsedata_DEC_3_HEX[PULSEDATA_LENGTH*2] =  {0};
    int Pulsedata_DEC_4_HEX[PULSEDATA_LENGTH*2] =  {0};

    int Pulsedata_DEC_disp[PULSEDATA_LENGTH] = {0};

    void initWidget();
    void DisplayWave();

    Ui::wave_widget *ui;

public slots:
    //    void FlashWave(char[]);
    //    void FlashWave2(QByteArray);
    void FlashWave3(char[]);
//    void on_comboBox_Channel_currentIndexChangedSlot();

private slots:
    void on_btnReset_clicked();



private:

};

#endif // WAVE_WIDGET_H
