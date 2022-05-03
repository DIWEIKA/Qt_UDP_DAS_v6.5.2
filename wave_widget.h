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

#define READ_LENGTH 40960
#define CHDATA_ALL_LENGTH 10240
#define CHDATA_LENGTH 2560

using namespace std;

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class wave_widget;
}

class wave_widget : public QWidget
{
    Q_OBJECT

public:
    explicit wave_widget(QWidget *parent = nullptr);
    ~wave_widget();

    QTimer* m_timer;
    QChart* m_chart;
    QValueAxis *m_axisX, *m_axisY;
    QSplineSeries* m_lineSeries;
     const int AXIS_MAX_X = 2560, AXIS_MAX_Y = 700;
      int pointCount = 0;

      QVector<QPointF> pointsSeries;
      QString saveFolder;//´æ´¢Ä¿Â¼£¨ÎÄ¼þ¼Ð£©
      QString saveFilenameAll;
      ifstream infileAll;
      char CHdata[READ_LENGTH];
      int CHdata_DEC_all[CHDATA_ALL_LENGTH] =  {0};
      int CHdata_DEC_1[CHDATA_LENGTH]= {0};
      int CHdata_DEC_2[CHDATA_LENGTH] =  {0};
      int CHdata_DEC_3[CHDATA_LENGTH] =  {0};
      int CHdata_DEC_4[CHDATA_LENGTH] =  {0};

      void slotTimeout();
      void ReadFromFiles();

private slots:

    void on_btnStartAndStop_clicked();

    void on_btnReset_clicked();

private:
    Ui::wave_widget *ui;
};

#endif // WAVE_WIDGET_H
