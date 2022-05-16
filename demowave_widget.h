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
    int ChannelIndex = 0;
    const int AXIS_MAX_X = DISPLAY_LENGTH_DEMO, AXIS_MAX_Y = 10;

    float Demodata_1[DEMODATA_LENGTH] = {0};
    float Demodata_2[DEMODATA_LENGTH] = {0};
    float Demodata_3[DEMODATA_LENGTH] = {0};
    float Demodata_4[DEMODATA_LENGTH] = {0};

    void initWidget();

public slots:
    void FlashWave(shared_ptr<CirQueue<float>>);

private slots:

    void on_pushButton_reset_clicked();

private:
    Ui::demowave_widget *ui;
};

#endif // DEMOWAVE_WIDGET_H
