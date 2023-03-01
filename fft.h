#ifndef FFT_H
#define FFT_H

#include <QThread>
#include <mainwindow.h>
#include <math.h>

#define NN 20000 //fft容器长度 2s的数据长度，和采样率有关
#define N1 2048 //做fft的长度 为2的整数次幂
#define N2 695 //fft显示长度

class Demodulation;

class FFT : public QThread
{
    Q_OBJECT

public:
    explicit FFT(Demodulation* _demodulation);
    ~FFT();
    void FFT_t(float xreal [], float ximag [], int n);
    void  IFFT_t (float xreal [], float ximag [], int n);
    inline void swap (float &a, float &b);
    void bitrp (float xreal [], float ximag [], int n);
    float* fftData_1() {return FFTData_1;}
    float* fftData_2() {return FFTData_2;}
    float* fftData_3() {return FFTData_3;}
    float* fftData_4() {return FFTData_4;}
    float* fftData_5() {return FFTData_5;}
    float* fftData_6() {return FFTData_6;}
    float* fftData_7() {return FFTData_7;}
    float* fftData_8() {return FFTData_8;}
    float* fftData_9() {return FFTData_9;}
    float* fftData_10() {return FFTData_10;}
    float* fftData_11() {return FFTData_11;}
    float* fftData_12() {return FFTData_12;}
    float* fftData_13() {return FFTData_13;}
    float* fftData_14() {return FFTData_14;}
    float* fftData_15() {return FFTData_15;}
    float* fftData_16() {return FFTData_16;}
    float* fftData_17() {return FFTData_17;}
    float* fftData_18() {return FFTData_18;}
    float* fftData_19() {return FFTData_19;}
    float* fftData_20() {return FFTData_20;}
    float* fftData_21() {return FFTData_21;}
    float* fftData_22() {return FFTData_22;}
    float* fftData_23() {return FFTData_23;}
    float* fftData_24() {return FFTData_24;}
    float* fftData_25() {return FFTData_25;}
    float* fftData_26() {return FFTData_26;}
    float* fftData_27() {return FFTData_27;}
    float* fftData_28() {return FFTData_28;}
    float* fftData_29() {return FFTData_29;}
    float* fftData_30() {return FFTData_30;}
    float* fftData_31() {return FFTData_31;}
    float* fftData_32() {return FFTData_32;}
    float* fftData_33() {return FFTData_33;}
    float* fftData_34() {return FFTData_34;}
    float* fftData_35() {return FFTData_35;}
    float* fftData_36() {return FFTData_36;}
    float* fftData_37() {return FFTData_37;}
    float* fftData_38() {return FFTData_38;}
    float* fftData_39() {return FFTData_39;}
    float* fftData_40() {return FFTData_40;}
    float* fftData_41() {return FFTData_41;}
    float* fftData_42() {return FFTData_42;}
    float* fftData_43() {return FFTData_43;}
    float* fftData_44() {return FFTData_44;}
    float* fftData_45() {return FFTData_45;}
    float* fftData_46() {return FFTData_46;}
    float* fftData_47() {return FFTData_47;}
    float* fftData_48() {return FFTData_48;}
    float* fftData_49() {return FFTData_49;}
    float* fftData_50() {return FFTData_50;}
    float* fftData_51() {return FFTData_51;}
    float* fftData_52() {return FFTData_52;}
    float* fftData_53() {return FFTData_53;}
    float* fftData_54() {return FFTData_54;}
    float* fftData_55() {return FFTData_55;}
    float* fftData_56() {return FFTData_56;}
    float* fftData_57() {return FFTData_57;}
    float* fftData_58() {return FFTData_58;}
    float* fftData_59() {return FFTData_59;}
    float* fftData_60() {return FFTData_60;}
    float* fftData_61() {return FFTData_61;}
    float* fftData_62() {return FFTData_62;}
    float* fftData_63() {return FFTData_63;}
    float* fftData_64() {return FFTData_64;}
    float* fftData_65() {return FFTData_65;}
    float* fftData_66() {return FFTData_66;}
    float* fftData_67() {return FFTData_67;}
    float* fftData_68() {return FFTData_68;}
    float* fftData_69() {return FFTData_69;}
    float* fftData_70() {return FFTData_70;}
    float* fftData_71() {return FFTData_71;}
    float* fftData_72() {return FFTData_72;}
    float* fftData_73() {return FFTData_73;}
    float* fftData_74() {return FFTData_74;}
    float* fftData_75() {return FFTData_75;}
    float* fftData_76() {return FFTData_76;}
    float* fftData_77() {return FFTData_77;}
    float* fftData_78() {return FFTData_78;}
    float* fftData_79() {return FFTData_79;}
    float* fftData_80() {return FFTData_80;}
    float* fftData_81() {return FFTData_81;}
    float* fftData_82() {return FFTData_82;}
    float* fftData_83() {return FFTData_83;}
    float* fftData_84() {return FFTData_84;}
    float* fftData_85() {return FFTData_85;}
    float* fftData_86() {return FFTData_86;}
    float* fftData_87() {return FFTData_87;}
    float* fftData_88() {return FFTData_88;}
    float* fftData_89() {return FFTData_89;}
    float* fftData_90() {return FFTData_90;}
    float* fftData_91() {return FFTData_91;}
    float* fftData_92() {return FFTData_92;}
    float* fftData_93() {return FFTData_93;}
    float* fftData_94() {return FFTData_94;}
    float* fftData_95() {return FFTData_95;}
    float* fftData_96() {return FFTData_96;}
    float* fftData_97() {return FFTData_97;}
    float* fftData_98() {return FFTData_98;}
    float* fftData_99() {return FFTData_99;}
    float* fftData_100() {return FFTData_100;}
    float* fftData_101() {return FFTData_101;}
    float* fftData_102() {return FFTData_102;}
    float* fftData_103() {return FFTData_103;}
    float* fftData_104() {return FFTData_104;}
    float* fftData_105() {return FFTData_105;}
    float* fftData_106() {return FFTData_106;}
    float* fftData_107() {return FFTData_107;}
    float* fftData_108() {return FFTData_108;}
    float* fftData_109() {return FFTData_109;}
    float* fftData_110() {return FFTData_110;}
    float* fftData_111() {return FFTData_111;}
    float* fftData_112() {return FFTData_112;}
    float* fftData_113() {return FFTData_113;}
    float* fftData_114() {return FFTData_114;}
    float* fftData_115() {return FFTData_115;}
    float* fftData_116() {return FFTData_116;}
    float* fftData_117() {return FFTData_117;}
    float* fftData_118() {return FFTData_118;}
    float* fftData_119() {return FFTData_119;}
    float* fftData_120() {return FFTData_120;}
    float* fftData_121() {return FFTData_121;}
    float* fftData_122() {return FFTData_122;}
    float* fftData_123() {return FFTData_123;}
    float* fftData_124() {return FFTData_124;}
    float* fftData_125() {return FFTData_125;}
    float* fftData_126() {return FFTData_126;}
    float* fftData_127() {return FFTData_127;}
    float* fftData_128() {return FFTData_128;}
    float* fftData_129() {return FFTData_129;}
    float* fftData_130() {return FFTData_130;}
    float* fftData_131() {return FFTData_131;}
    float* fftData_132() {return FFTData_132;}
    float* fftData_133() {return FFTData_133;}
    float* fftData_134() {return FFTData_134;}
    float* fftData_135() {return FFTData_135;}
    float* fftData_136() {return FFTData_136;}
    float* fftData_137() {return FFTData_137;}
    float* fftData_138() {return FFTData_138;}
    float* fftData_139() {return FFTData_139;}
    float* fftData_140() {return FFTData_140;}
    float* fftData_141() {return FFTData_141;}
    float* fftData_142() {return FFTData_142;}
    float* fftData_143() {return FFTData_143;}
    float* fftData_144() {return FFTData_144;}
    float* fftData_145() {return FFTData_145;}
    float* fftData_146() {return FFTData_146;}
    float* fftData_147() {return FFTData_147;}
    float* fftData_148() {return FFTData_148;}
    float* fftData_149() {return FFTData_149;}
    float* fftData_150() {return FFTData_150;}

private:
    Demodulation* m_demodulation;
    float xreal[N1], ximag[N1];//初始化容器
    int n; //做FFT的长度
    int N = NN;
    float FFT_result[NN]={};
    int regionNum;
    int regionIndex = 1;

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
