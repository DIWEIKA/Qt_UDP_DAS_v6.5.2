#ifndef WAVE_WIDGET_H
#define WAVE_WIDGET_H

#include <QWidget>
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
#define CHDATA_ALL_LENGTH 1024*8 //四个通道的十进制数数据长度
#define CHDATA_LENGTH 1024*2 //一个通道的十进制数长度
#define DISPLAY_LENGTH 256*2 //展示在widget上的数据长度
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
    const int AXIS_MAX_X = DISPLAY_LENGTH, AXIS_MAX_Y = 700;
    int sizeoCHdata ;
    int sizeoCHdataDec;
    qint64 LenoUDP = READ_LENGTH;

    QVector<QPointF> pointsSeries;
    QString saveFolder;
    QString saveFilenameAll;
    ifstream infileAll;
    //ASCII接收
    char CHdata[READ_LENGTH]= {'\0'};
    int CHdata_DEC_all[CHDATA_ALL_LENGTH] =  {0};
    int CHdata_DEC_1[CHDATA_LENGTH]= {0};
    int CHdata_DEC_2[CHDATA_LENGTH] =  {0};
    int CHdata_DEC_3[CHDATA_LENGTH] =  {0};
    int CHdata_DEC_4[CHDATA_LENGTH] =  {0};
    //HEX接收
    char CHdataHEX[READ_LENGTH*2] = {'\0'};
    int CHdata_DEC_all_HEX[CHDATA_ALL_LENGTH*2] =  {0};
    int CHdata_DEC_1_HEX[CHDATA_LENGTH*2]= {0};
    int CHdata_DEC_2_HEX[CHDATA_LENGTH*2] =  {0};
    int CHdata_DEC_3_HEX[CHDATA_LENGTH*2] =  {0};
    int CHdata_DEC_4_HEX[CHDATA_LENGTH*2] =  {0};

    int CHdata_DEC_disp[CHDATA_LENGTH] = {0};

    void initWidget();
    void ReadFromFiles();
    void DisplayWave();

public slots:
    void FlashWave(char[]);
    void FlashWave2(QByteArray);
    void FlashWave3(char[]);

private slots:
    void on_btnReset_clicked();


private:
    Ui::wave_widget *ui;
};

#endif // WAVE_WIDGET_H
