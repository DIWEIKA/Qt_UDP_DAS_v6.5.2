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
#include <mainwindow.h>

#define READ_DEMO_LENGTH 4096*8 //从DEMOdata里读取的数据长度
#define DEMODATA_LENGTH 4096*2 //一个通道的十进制数长度
#define DISPLAY_LENGTH_DEMO 512*2 //展示在widget上的数据长度

using namespace std;

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class demowave_widget;
}

class demowave_widget : public QWidget
{
    Q_OBJECT

public:
    explicit demowave_widget(QWidget *parent = nullptr);
    ~demowave_widget();

    QChart* m_chart;
    QValueAxis *m_axisX, *m_axisY;
    QLineSeries* m_lineSeries;
    int RegionIndex = 0;
    const int AXIS_MAX_X = DISPLAY_LENGTH_DEMO, AXIS_MAX_Y = 10;
    int peakNum=1;

    float **DemodataArray = NULL; //存放Demodata[]的数组(二维数组)
    float Demodata_1[DEMODATA_LENGTH] = {0}; //region1
    float Demodata_2[DEMODATA_LENGTH] = {0}; //region2
    float Demodata_3[DEMODATA_LENGTH] = {0};
    float Demodata_4[DEMODATA_LENGTH] = {0};
    float Demodata_5[DEMODATA_LENGTH] = {0};
    float Demodata_6[DEMODATA_LENGTH] = {0};
    float Demodata_7[DEMODATA_LENGTH] = {0};
    float Demodata_8[DEMODATA_LENGTH] = {0};
    float Demodata_9[DEMODATA_LENGTH] = {0};
    float Demodata_10[DEMODATA_LENGTH] = {0};

    void initWidget();
    void readConfigFile();
    void initComboBox_Region();

public slots:
    void FlashWave(shared_ptr<CirQueue<float>>);

private slots:

    void on_pushButton_reset_clicked();

private:
    Ui::demowave_widget *ui;
};

#endif // DEMOWAVE_WIDGET_H
