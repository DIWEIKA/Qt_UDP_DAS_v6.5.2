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
#include <fft.h>


#define REGION_DATA_LENGTH 256*100*3

#define MAXREGION 100 //最大区域数

using namespace std;

namespace Ui {
class demowave_widget2;
}

class Demodulation;
class WebClass;
class FFT;

class demowave_widget2: public QWidget
{
public:
    demowave_widget2(Demodulation *demodulation, FFT *_fft);
    ~demowave_widget2();
    void setHtmlPages();
    void initComboBox_Region();
    QVector<double> labelPositions(const QVector<QString> &labels, double offset);
    void FreeMemory();
    WebClass* GetWebobj4() const {return webobj4;}

private:
    Ui::demowave_widget2 *ui;

    QWebEngineView *m_demowave_widget;
    QWebChannel *webChannel4;
    WebClass *webobj4;

    Demodulation *demodu;
    QTimer* timer_flash;
    int RegionIndex;
    int peakNum;
    QVector<QString> Region; //存放区域label的容器
    QVector<QString> Sampledots; //存放采样点label的容器
    FFT* m_fft;

    //存放Demodata[]的数组(二维数组) 二维数组最大为20000*20000*4Bytes(总容量不能超过2GBytes)
    float **DemodataArray = new float*[MAXREGION];
    //静态数组
    float Demodata_1[REGION_DATA_LENGTH]; //region1
    float Demodata_2[REGION_DATA_LENGTH]; //region2
    float Demodata_3[REGION_DATA_LENGTH];
    float Demodata_4[REGION_DATA_LENGTH];
    float Demodata_5[REGION_DATA_LENGTH];
    float Demodata_6[REGION_DATA_LENGTH];
    float Demodata_7[REGION_DATA_LENGTH];
    float Demodata_8[REGION_DATA_LENGTH];
    float Demodata_9[REGION_DATA_LENGTH];
    float Demodata_10[REGION_DATA_LENGTH];
    float Demodata_11[REGION_DATA_LENGTH]; //region11
    float Demodata_12[REGION_DATA_LENGTH];
    float Demodata_13[REGION_DATA_LENGTH];
    float Demodata_14[REGION_DATA_LENGTH];
    float Demodata_15[REGION_DATA_LENGTH];
    float Demodata_16[REGION_DATA_LENGTH];
    float Demodata_17[REGION_DATA_LENGTH];
    float Demodata_18[REGION_DATA_LENGTH];
    float Demodata_19[REGION_DATA_LENGTH];
    float Demodata_20[REGION_DATA_LENGTH];
    float Demodata_21[REGION_DATA_LENGTH]; //region21
    float Demodata_22[REGION_DATA_LENGTH];
    float Demodata_23[REGION_DATA_LENGTH];
    float Demodata_24[REGION_DATA_LENGTH];
    float Demodata_25[REGION_DATA_LENGTH];
    float Demodata_26[REGION_DATA_LENGTH];
    float Demodata_27[REGION_DATA_LENGTH];
    float Demodata_28[REGION_DATA_LENGTH];
    float Demodata_29[REGION_DATA_LENGTH];
    float Demodata_30[REGION_DATA_LENGTH];
    float Demodata_31[REGION_DATA_LENGTH]; //region31
    float Demodata_32[REGION_DATA_LENGTH];
    float Demodata_33[REGION_DATA_LENGTH];
    float Demodata_34[REGION_DATA_LENGTH];
    float Demodata_35[REGION_DATA_LENGTH];
    float Demodata_36[REGION_DATA_LENGTH];
    float Demodata_37[REGION_DATA_LENGTH];
    float Demodata_38[REGION_DATA_LENGTH];
    float Demodata_39[REGION_DATA_LENGTH];
    float Demodata_40[REGION_DATA_LENGTH];
    float Demodata_41[REGION_DATA_LENGTH]; //region41
    float Demodata_42[REGION_DATA_LENGTH];
    float Demodata_43[REGION_DATA_LENGTH];
    float Demodata_44[REGION_DATA_LENGTH];
    float Demodata_45[REGION_DATA_LENGTH];
    float Demodata_46[REGION_DATA_LENGTH];
    float Demodata_47[REGION_DATA_LENGTH];
    float Demodata_48[REGION_DATA_LENGTH];
    float Demodata_49[REGION_DATA_LENGTH];
    float Demodata_50[REGION_DATA_LENGTH];
    float Demodata_51[REGION_DATA_LENGTH]; //region51
    float Demodata_52[REGION_DATA_LENGTH];
    float Demodata_53[REGION_DATA_LENGTH];
    float Demodata_54[REGION_DATA_LENGTH];
    float Demodata_55[REGION_DATA_LENGTH];
    float Demodata_56[REGION_DATA_LENGTH];
    float Demodata_57[REGION_DATA_LENGTH];
    float Demodata_58[REGION_DATA_LENGTH];
    float Demodata_59[REGION_DATA_LENGTH];
    float Demodata_60[REGION_DATA_LENGTH];
    /*报错：编译器堆空间不足*/
    float Demodata_61[REGION_DATA_LENGTH]; //region61
    float Demodata_62[REGION_DATA_LENGTH];
    float Demodata_63[REGION_DATA_LENGTH];
    float Demodata_64[REGION_DATA_LENGTH];
    float Demodata_65[REGION_DATA_LENGTH];
    float Demodata_66[REGION_DATA_LENGTH];
    float Demodata_67[REGION_DATA_LENGTH];
    float Demodata_68[REGION_DATA_LENGTH];
    float Demodata_69[REGION_DATA_LENGTH];
    float Demodata_70[REGION_DATA_LENGTH];
    float Demodata_71[REGION_DATA_LENGTH]; //region71
    float Demodata_72[REGION_DATA_LENGTH];
    float Demodata_73[REGION_DATA_LENGTH];
    float Demodata_74[REGION_DATA_LENGTH];
    float Demodata_75[REGION_DATA_LENGTH];
    float Demodata_76[REGION_DATA_LENGTH];
    float Demodata_77[REGION_DATA_LENGTH];
    float Demodata_78[REGION_DATA_LENGTH];
    float Demodata_79[REGION_DATA_LENGTH];
    float Demodata_80[REGION_DATA_LENGTH];
    float Demodata_81[REGION_DATA_LENGTH]; //region81
    float Demodata_82[REGION_DATA_LENGTH];
    float Demodata_83[REGION_DATA_LENGTH];
    float Demodata_84[REGION_DATA_LENGTH];
    float Demodata_85[REGION_DATA_LENGTH];
    float Demodata_86[REGION_DATA_LENGTH];
    float Demodata_87[REGION_DATA_LENGTH];
    float Demodata_88[REGION_DATA_LENGTH];
    float Demodata_89[REGION_DATA_LENGTH];
    float Demodata_90[REGION_DATA_LENGTH];
    float Demodata_91[REGION_DATA_LENGTH]; //region91
    float Demodata_92[REGION_DATA_LENGTH];
    float Demodata_93[REGION_DATA_LENGTH];
    float Demodata_94[REGION_DATA_LENGTH];
    float Demodata_95[REGION_DATA_LENGTH];
    float Demodata_96[REGION_DATA_LENGTH];
    float Demodata_97[REGION_DATA_LENGTH];
    float Demodata_98[REGION_DATA_LENGTH];
    float Demodata_99[REGION_DATA_LENGTH];
    float Demodata_100[REGION_DATA_LENGTH];//region100


public slots:
    void FlashWave();
    void on_comboBox_region_currentIndexChangedSlot(int _regionIndex);

private slots:

};

#endif // DEMOWAVE_WIDGET2_H
