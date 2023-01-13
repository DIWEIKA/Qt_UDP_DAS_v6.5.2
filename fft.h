#ifndef FFT_H
#define FFT_H

#include <QThread>
#include <mainwindow.h>
#include <math.h>

#define NN 60000 //fft容器长度 2s的数据长度，和采样率有关
#define N1 2048 //做fft的长度 为2的整数次幂
#define N2 695 //fft显示长度

class Demodulation;

class FFT : public QThread
{
    Q_OBJECT

public:
    explicit FFT(Demodulation* _demodulation);
    ~FFT();

    Demodulation* m_demodulation;

    float xreal[N1], ximag[N1];//初始化容器
    int n; //做FFT的长度

    int N = NN;
    float FFT_result[NN]={};
    int regionNum;
    int regionIndex = 1;

    void FFT_t(float xreal [], float ximag [], int n);
    void  IFFT_t (float xreal [], float ximag [], int n);
    inline void swap (float &a, float &b);
    void bitrp (float xreal [], float ximag [], int n);

    //存放解调结果
    float** DemodataArray = new float*[4]; //test regionNum = 4
    float Demodata_1[NN]; //region1
    float Demodata_2[NN]; //region2
    float Demodata_3[NN]; //region3
    float Demodata_4[NN]; //region4

    //存放fft结果
    float** fft_result_array = new float*[4]; //test regionNum = 4
    float fft_result_1[N1/2]; //region1
    float fft_result_2[N1/2]; //region2
    float fft_result_3[N1/2]; //region3
    float fft_result_4[N1/2]; //region4


    //存放FFT处理结果 发送给前端界面瀑布图显示
    //每2s的数据量一个容器 一分钟30个容器
    //容器的长度是0~2000个点中选取的N2长度的点数
    float FFTData_1[N2];
    float FFTData_2[N2];
    float FFTData_3[N2];
    float FFTData_4[N2];
    float FFTData_5[N2];
    float FFTData_6[N2];
    float FFTData_7[N2];
    float FFTData_8[N2];
    float FFTData_9[N2];
    float FFTData_10[N2];
    float FFTData_11[N2];
    float FFTData_12[N2];
    float FFTData_13[N2];
    float FFTData_14[N2];
    float FFTData_15[N2];
    float FFTData_16[N2];
    float FFTData_17[N2];
    float FFTData_18[N2];
    float FFTData_19[N2];
    float FFTData_20[N2];
    float FFTData_21[N2];
    float FFTData_22[N2];
    float FFTData_23[N2];
    float FFTData_24[N2];
    float FFTData_25[N2];
    float FFTData_26[N2];
    float FFTData_27[N2];
    float FFTData_28[N2];
    float FFTData_29[N2];
    float FFTData_30[N2];
    float FFTData_31[N2];
    float FFTData_32[N2];
    float FFTData_33[N2];
    float FFTData_34[N2];
    float FFTData_35[N2];
    float FFTData_36[N2];
    float FFTData_37[N2];
    float FFTData_38[N2];
    float FFTData_39[N2];
    float FFTData_40[N2];
    float FFTData_41[N2];
    float FFTData_42[N2];
    float FFTData_43[N2];
    float FFTData_44[N2];
    float FFTData_45[N2];
    float FFTData_46[N2];
    float FFTData_47[N2];
    float FFTData_48[N2];
    float FFTData_49[N2];
    float FFTData_50[N2];
    float FFTData_51[N2];
    float FFTData_52[N2];
    float FFTData_53[N2];
    float FFTData_54[N2];
    float FFTData_55[N2];
    float FFTData_56[N2];
    float FFTData_57[N2];
    float FFTData_58[N2];
    float FFTData_59[N2];
    float FFTData_60[N2];
    float FFTData_61[N2];
    float FFTData_62[N2];
    float FFTData_63[N2];
    float FFTData_64[N2];
    float FFTData_65[N2];
    float FFTData_66[N2];
    float FFTData_67[N2];
    float FFTData_68[N2];
    float FFTData_69[N2];
    float FFTData_70[N2];
    float FFTData_71[N2];
    float FFTData_72[N2];
    float FFTData_73[N2];
    float FFTData_74[N2];
    float FFTData_75[N2];
    float FFTData_76[N2];
    float FFTData_77[N2];
    float FFTData_78[N2];
    float FFTData_79[N2];
    float FFTData_80[N2];
    float FFTData_81[N2];
    float FFTData_82[N2];
    float FFTData_83[N2];
    float FFTData_84[N2];
    float FFTData_85[N2];
    float FFTData_86[N2];
    float FFTData_87[N2];
    float FFTData_88[N2];
    float FFTData_89[N2];
    float FFTData_90[N2];
    float FFTData_91[N2];
    float FFTData_92[N2];
    float FFTData_93[N2];
    float FFTData_94[N2];
    float FFTData_95[N2];
    float FFTData_96[N2];
    float FFTData_97[N2];
    float FFTData_98[N2];
    float FFTData_99[N2];
    float FFTData_100[N2];
    float FFTData_101[N2];
    float FFTData_102[N2];
    float FFTData_103[N2];
    float FFTData_104[N2];
    float FFTData_105[N2];
    float FFTData_106[N2];
    float FFTData_107[N2];
    float FFTData_108[N2];
    float FFTData_109[N2];
    float FFTData_110[N2];
    float FFTData_111[N2];
    float FFTData_112[N2];
    float FFTData_113[N2];
    float FFTData_114[N2];
    float FFTData_115[N2];
    float FFTData_116[N2];
    float FFTData_117[N2];
    float FFTData_118[N2];
    float FFTData_119[N2];
    float FFTData_120[N2];
    float FFTData_121[N2];
    float FFTData_122[N2];
    float FFTData_123[N2];
    float FFTData_124[N2];
    float FFTData_125[N2];
    float FFTData_126[N2];
    float FFTData_127[N2];
    float FFTData_128[N2];
    float FFTData_129[N2];
    float FFTData_130[N2];
    float FFTData_131[N2];
    float FFTData_132[N2];
    float FFTData_133[N2];
    float FFTData_134[N2];
    float FFTData_135[N2];
    float FFTData_136[N2];
    float FFTData_137[N2];
    float FFTData_138[N2];
    float FFTData_139[N2];
    float FFTData_140[N2];
    float FFTData_141[N2];
    float FFTData_142[N2];
    float FFTData_143[N2];
    float FFTData_144[N2];
    float FFTData_145[N2];
    float FFTData_146[N2];
    float FFTData_147[N2];
    float FFTData_148[N2];
    float FFTData_149[N2];
    float FFTData_150[N2];

public slots:
    void on_comboBox_region_currentIndexChangedSlot(int _regionIndex);

signals:

protected:
    void run();

};

#endif // FFT_H
