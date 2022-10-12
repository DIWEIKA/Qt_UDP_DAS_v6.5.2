#ifndef DEMOWAVE_WIDGET2_H
#define DEMOWAVE_WIDGET2_H

#include <mainwindow.h>
#include <QWidget>
#include <QMainWindow>
#include <qmainwindow.h>
#include "qcustomplot.h"
#include <QTimer>
#include <QThread>
#include <demodulation.h>


#define READ_FLASH_LENGTH 256*1000
#define REGION_DATA_LENGTH 256*100
#define DISPLAY_LENGTH_DEMO 100
#define MAXREGION 100

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
    int RegionIndex;
    int peakNum;
    QVector<QString> Region; //存放区域label的容器
    QVector<QString> Sampledots; //存放采样点label的容器
    QCustomPlot *m_customPlot; //解调波形的布局
    QCustomPlot *m_heatmapPlot; //瀑布图的布局
    QCPColorMap *heatmap; //瀑布图

    //存放Demodata[]的数组(二维数组) 二维数组最大为20000*20000*4Bytes(总容量不能超过2GBytes)
    float **DemodataArray = new float*[MAXREGION];
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
    float Demodata_11[REGION_DATA_LENGTH]={'\0'}; //region11
    float Demodata_12[REGION_DATA_LENGTH]={'\0'};
    float Demodata_13[REGION_DATA_LENGTH]={'\0'};
    float Demodata_14[REGION_DATA_LENGTH]={'\0'};
    float Demodata_15[REGION_DATA_LENGTH]={'\0'};
    float Demodata_16[REGION_DATA_LENGTH]={'\0'};
    float Demodata_17[REGION_DATA_LENGTH]={'\0'};
    float Demodata_18[REGION_DATA_LENGTH]={'\0'};
    float Demodata_19[REGION_DATA_LENGTH]={'\0'};
    float Demodata_20[REGION_DATA_LENGTH]={'\0'};
    float Demodata_21[REGION_DATA_LENGTH]={'\0'}; //region21
    float Demodata_22[REGION_DATA_LENGTH]={'\0'};
    float Demodata_23[REGION_DATA_LENGTH]={'\0'};
    float Demodata_24[REGION_DATA_LENGTH]={'\0'};
    float Demodata_25[REGION_DATA_LENGTH]={'\0'};
    float Demodata_26[REGION_DATA_LENGTH]={'\0'};
    float Demodata_27[REGION_DATA_LENGTH]={'\0'};
    float Demodata_28[REGION_DATA_LENGTH]={'\0'};
    float Demodata_29[REGION_DATA_LENGTH]={'\0'};
    float Demodata_30[REGION_DATA_LENGTH]={'\0'};
    float Demodata_31[REGION_DATA_LENGTH]={'\0'}; //region31
    float Demodata_32[REGION_DATA_LENGTH]={'\0'};
    float Demodata_33[REGION_DATA_LENGTH]={'\0'};
    float Demodata_34[REGION_DATA_LENGTH]={'\0'};
    float Demodata_35[REGION_DATA_LENGTH]={'\0'};
    float Demodata_36[REGION_DATA_LENGTH]={'\0'};
    float Demodata_37[REGION_DATA_LENGTH]={'\0'};
    float Demodata_38[REGION_DATA_LENGTH]={'\0'};
    float Demodata_39[REGION_DATA_LENGTH]={'\0'};
    float Demodata_40[REGION_DATA_LENGTH]={'\0'};
    float Demodata_41[REGION_DATA_LENGTH]={'\0'}; //region41
    float Demodata_42[REGION_DATA_LENGTH]={'\0'};
    float Demodata_43[REGION_DATA_LENGTH]={'\0'};
    float Demodata_44[REGION_DATA_LENGTH]={'\0'};
    float Demodata_45[REGION_DATA_LENGTH]={'\0'};
    float Demodata_46[REGION_DATA_LENGTH]={'\0'};
    float Demodata_47[REGION_DATA_LENGTH]={'\0'};
    float Demodata_48[REGION_DATA_LENGTH]={'\0'};
    float Demodata_49[REGION_DATA_LENGTH]={'\0'};
    float Demodata_50[REGION_DATA_LENGTH]={'\0'};
    float Demodata_51[REGION_DATA_LENGTH]={'\0'}; //region51
    float Demodata_52[REGION_DATA_LENGTH]={'\0'};
    float Demodata_53[REGION_DATA_LENGTH]={'\0'};
    float Demodata_54[REGION_DATA_LENGTH]={'\0'};
    float Demodata_55[REGION_DATA_LENGTH]={'\0'};
    float Demodata_56[REGION_DATA_LENGTH]={'\0'};
    float Demodata_57[REGION_DATA_LENGTH]={'\0'};
    float Demodata_58[REGION_DATA_LENGTH]={'\0'};
    float Demodata_59[REGION_DATA_LENGTH]={'\0'};
    float Demodata_60[REGION_DATA_LENGTH]={'\0'};
    float Demodata_61[REGION_DATA_LENGTH]={'\0'}; //region61
    float Demodata_62[REGION_DATA_LENGTH]={'\0'};
    float Demodata_63[REGION_DATA_LENGTH]={'\0'};
    float Demodata_64[REGION_DATA_LENGTH]={'\0'};
    float Demodata_65[REGION_DATA_LENGTH]={'\0'};
    float Demodata_66[REGION_DATA_LENGTH]={'\0'};
    float Demodata_67[REGION_DATA_LENGTH]={'\0'};
    float Demodata_68[REGION_DATA_LENGTH]={'\0'};
    float Demodata_69[REGION_DATA_LENGTH]={'\0'};
    float Demodata_70[REGION_DATA_LENGTH]={'\0'};
    float Demodata_71[REGION_DATA_LENGTH]={'\0'}; //region71
    float Demodata_72[REGION_DATA_LENGTH]={'\0'};
    float Demodata_73[REGION_DATA_LENGTH]={'\0'};
    float Demodata_74[REGION_DATA_LENGTH]={'\0'};
    float Demodata_75[REGION_DATA_LENGTH]={'\0'};
    float Demodata_76[REGION_DATA_LENGTH]={'\0'};
    float Demodata_77[REGION_DATA_LENGTH]={'\0'};
    float Demodata_78[REGION_DATA_LENGTH]={'\0'};
    float Demodata_79[REGION_DATA_LENGTH]={'\0'};
    float Demodata_80[REGION_DATA_LENGTH]={'\0'};
    float Demodata_81[REGION_DATA_LENGTH]={'\0'}; //region81
    float Demodata_82[REGION_DATA_LENGTH]={'\0'};
    float Demodata_83[REGION_DATA_LENGTH]={'\0'};
    float Demodata_84[REGION_DATA_LENGTH]={'\0'};
    float Demodata_85[REGION_DATA_LENGTH]={'\0'};
    float Demodata_86[REGION_DATA_LENGTH]={'\0'};
    float Demodata_87[REGION_DATA_LENGTH]={'\0'};
    float Demodata_88[REGION_DATA_LENGTH]={'\0'};
    float Demodata_89[REGION_DATA_LENGTH]={'\0'};
    float Demodata_90[REGION_DATA_LENGTH]={'\0'};
    float Demodata_91[REGION_DATA_LENGTH]={'\0'}; //region91
    float Demodata_92[REGION_DATA_LENGTH]={'\0'};
    float Demodata_93[REGION_DATA_LENGTH]={'\0'};
    float Demodata_94[REGION_DATA_LENGTH]={'\0'};
    float Demodata_95[REGION_DATA_LENGTH]={'\0'};
    float Demodata_96[REGION_DATA_LENGTH]={'\0'};
    float Demodata_97[REGION_DATA_LENGTH]={'\0'};
    float Demodata_98[REGION_DATA_LENGTH]={'\0'};
    float Demodata_99[REGION_DATA_LENGTH]={'\0'};
    float Demodata_100[REGION_DATA_LENGTH]={'\0'};//region100

    void initWidget();
    void initComboBox_Region();
    QVector<double> labelPositions(const QVector<QString> &labels, double offset);

    void FreeMemory();

public slots:
    void FlashWave();

private slots:
    void on_pushButton_reset_clicked();

};

#endif // DEMOWAVE_WIDGET2_H
