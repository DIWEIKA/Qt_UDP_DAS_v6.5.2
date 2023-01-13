#include "fft.h"

FFT::FFT(Demodulation* _demodulation)
    :m_demodulation(_demodulation)
{
    memset(xreal,0,sizeof(float)*N1);
    memset(ximag,0,sizeof(float)*N1);

    memset(Demodata_1,0,sizeof(float)*NN);
    memset(Demodata_2,0,sizeof(float)*NN);
    memset(Demodata_3,0,sizeof(float)*NN);
    memset(Demodata_4,0,sizeof(float)*NN);

    DemodataArray[0] = Demodata_1;
    DemodataArray[1] = Demodata_2;
    DemodataArray[2] = Demodata_3;
    DemodataArray[3] = Demodata_4;

    memset(fft_result_1,0,sizeof(float)*N1);
    memset(fft_result_2,0,sizeof(float)*N1);
    memset(fft_result_3,0,sizeof(float)*N1);
    memset(fft_result_4,0,sizeof(float)*N1);

    fft_result_array[0] = fft_result_1;
    fft_result_array[1] = fft_result_2;
    fft_result_array[2] = fft_result_3;
    fft_result_array[3] = fft_result_4;

    memset(FFTData_1, 0, sizeof(float)*N2);
    memset(FFTData_2, 0, sizeof(float)*N2);
    memset(FFTData_3, 0, sizeof(float)*N2);
    memset(FFTData_4, 0, sizeof(float)*N2);
    memset(FFTData_5, 0, sizeof(float)*N2);
    memset(FFTData_6, 0, sizeof(float)*N2);
    memset(FFTData_7, 0, sizeof(float)*N2);
    memset(FFTData_8, 0, sizeof(float)*N2);
    memset(FFTData_9, 0, sizeof(float)*N2);
    memset(FFTData_10, 0, sizeof(float)*N2);
    memset(FFTData_11, 0, sizeof(float)*N2);
    memset(FFTData_12, 0, sizeof(float)*N2);
    memset(FFTData_13, 0, sizeof(float)*N2);
    memset(FFTData_14, 0, sizeof(float)*N2);
    memset(FFTData_15, 0, sizeof(float)*N2);
    memset(FFTData_16, 0, sizeof(float)*N2);
    memset(FFTData_17, 0, sizeof(float)*N2);
    memset(FFTData_18, 0, sizeof(float)*N2);
    memset(FFTData_19, 0, sizeof(float)*N2);
    memset(FFTData_20, 0, sizeof(float)*N2);
    memset(FFTData_21, 0, sizeof(float)*N2);
    memset(FFTData_22, 0, sizeof(float)*N2);
    memset(FFTData_23, 0, sizeof(float)*N2);
    memset(FFTData_24, 0, sizeof(float)*N2);
    memset(FFTData_25, 0, sizeof(float)*N2);
    memset(FFTData_26, 0, sizeof(float)*N2);
    memset(FFTData_27, 0, sizeof(float)*N2);
    memset(FFTData_28, 0, sizeof(float)*N2);
    memset(FFTData_29, 0, sizeof(float)*N2);
    memset(FFTData_30, 0, sizeof(float)*N2);
    memset(FFTData_31, 0, sizeof(float)*N2);
    memset(FFTData_32, 0, sizeof(float)*N2);
    memset(FFTData_33, 0, sizeof(float)*N2);
    memset(FFTData_34, 0, sizeof(float)*N2);
    memset(FFTData_35, 0, sizeof(float)*N2);
    memset(FFTData_36, 0, sizeof(float)*N2);
    memset(FFTData_37, 0, sizeof(float)*N2);
    memset(FFTData_38, 0, sizeof(float)*N2);
    memset(FFTData_39, 0, sizeof(float)*N2);
    memset(FFTData_40, 0, sizeof(float)*N2);
    memset(FFTData_41, 0, sizeof(float)*N2);
    memset(FFTData_42, 0, sizeof(float)*N2);
    memset(FFTData_43, 0, sizeof(float)*N2);
    memset(FFTData_44, 0, sizeof(float)*N2);
    memset(FFTData_45, 0, sizeof(float)*N2);
    memset(FFTData_46, 0, sizeof(float)*N2);
    memset(FFTData_47, 0, sizeof(float)*N2);
    memset(FFTData_48, 0, sizeof(float)*N2);
    memset(FFTData_49, 0, sizeof(float)*N2);
    memset(FFTData_50, 0, sizeof(float)*N2);
    memset(FFTData_51, 0, sizeof(float)*N2);
    memset(FFTData_52, 0, sizeof(float)*N2);
    memset(FFTData_53, 0, sizeof(float)*N2);
    memset(FFTData_54, 0, sizeof(float)*N2);
    memset(FFTData_55, 0, sizeof(float)*N2);
    memset(FFTData_56, 0, sizeof(float)*N2);
    memset(FFTData_57, 0, sizeof(float)*N2);
    memset(FFTData_58, 0, sizeof(float)*N2);
    memset(FFTData_59, 0, sizeof(float)*N2);
    memset(FFTData_60, 0, sizeof(float)*N2);
    memset(FFTData_61, 0, sizeof(float)*N2);
    memset(FFTData_62, 0, sizeof(float)*N2);
    memset(FFTData_63, 0, sizeof(float)*N2);
    memset(FFTData_64, 0, sizeof(float)*N2);
    memset(FFTData_65, 0, sizeof(float)*N2);
    memset(FFTData_66, 0, sizeof(float)*N2);
    memset(FFTData_67, 0, sizeof(float)*N2);
    memset(FFTData_68, 0, sizeof(float)*N2);
    memset(FFTData_69, 0, sizeof(float)*N2);
    memset(FFTData_70, 0, sizeof(float)*N2);
    memset(FFTData_71, 0, sizeof(float)*N2);
    memset(FFTData_72, 0, sizeof(float)*N2);
    memset(FFTData_73, 0, sizeof(float)*N2);
    memset(FFTData_74, 0, sizeof(float)*N2);
    memset(FFTData_75, 0, sizeof(float)*N2);
    memset(FFTData_76, 0, sizeof(float)*N2);
    memset(FFTData_77, 0, sizeof(float)*N2);
    memset(FFTData_78, 0, sizeof(float)*N2);
    memset(FFTData_79, 0, sizeof(float)*N2);
    memset(FFTData_80, 0, sizeof(float)*N2);
    memset(FFTData_81, 0, sizeof(float)*N2);
    memset(FFTData_82, 0, sizeof(float)*N2);
    memset(FFTData_83, 0, sizeof(float)*N2);
    memset(FFTData_84, 0, sizeof(float)*N2);
    memset(FFTData_85, 0, sizeof(float)*N2);
    memset(FFTData_86, 0, sizeof(float)*N2);
    memset(FFTData_87, 0, sizeof(float)*N2);
    memset(FFTData_88, 0, sizeof(float)*N2);
    memset(FFTData_89, 0, sizeof(float)*N2);
    memset(FFTData_90, 0, sizeof(float)*N2);
    memset(FFTData_91, 0, sizeof(float)*N2);
    memset(FFTData_92, 0, sizeof(float)*N2);
    memset(FFTData_93, 0, sizeof(float)*N2);
    memset(FFTData_94, 0, sizeof(float)*N2);
    memset(FFTData_95, 0, sizeof(float)*N2);
    memset(FFTData_96, 0, sizeof(float)*N2);
    memset(FFTData_97, 0, sizeof(float)*N2);
    memset(FFTData_98, 0, sizeof(float)*N2);
    memset(FFTData_99, 0, sizeof(float)*N2);
    memset(FFTData_100, 0, sizeof(float)*N2);
    memset(FFTData_101, 0, sizeof(float)*N2);
    memset(FFTData_102, 0, sizeof(float)*N2);
    memset(FFTData_103, 0, sizeof(float)*N2);
    memset(FFTData_104, 0, sizeof(float)*N2);
    memset(FFTData_105, 0, sizeof(float)*N2);
    memset(FFTData_106, 0, sizeof(float)*N2);
    memset(FFTData_107, 0, sizeof(float)*N2);
    memset(FFTData_108, 0, sizeof(float)*N2);
    memset(FFTData_109, 0, sizeof(float)*N2);
    memset(FFTData_110, 0, sizeof(float)*N2);
    memset(FFTData_111, 0, sizeof(float)*N2);
    memset(FFTData_112, 0, sizeof(float)*N2);
    memset(FFTData_113, 0, sizeof(float)*N2);
    memset(FFTData_114, 0, sizeof(float)*N2);
    memset(FFTData_115, 0, sizeof(float)*N2);
    memset(FFTData_116, 0, sizeof(float)*N2);
    memset(FFTData_117, 0, sizeof(float)*N2);
    memset(FFTData_118, 0, sizeof(float)*N2);
    memset(FFTData_119, 0, sizeof(float)*N2);
    memset(FFTData_120, 0, sizeof(float)*N2);
    memset(FFTData_121, 0, sizeof(float)*N2);
    memset(FFTData_122, 0, sizeof(float)*N2);
    memset(FFTData_123, 0, sizeof(float)*N2);
    memset(FFTData_124, 0, sizeof(float)*N2);
    memset(FFTData_125, 0, sizeof(float)*N2);
    memset(FFTData_126, 0, sizeof(float)*N2);
    memset(FFTData_127, 0, sizeof(float)*N2);
    memset(FFTData_128, 0, sizeof(float)*N2);
    memset(FFTData_129, 0, sizeof(float)*N2);
    memset(FFTData_130, 0, sizeof(float)*N2);
    memset(FFTData_131, 0, sizeof(float)*N2);
    memset(FFTData_132, 0, sizeof(float)*N2);
    memset(FFTData_133, 0, sizeof(float)*N2);
    memset(FFTData_134, 0, sizeof(float)*N2);
    memset(FFTData_135, 0, sizeof(float)*N2);
    memset(FFTData_136, 0, sizeof(float)*N2);
    memset(FFTData_137, 0, sizeof(float)*N2);
    memset(FFTData_138, 0, sizeof(float)*N2);
    memset(FFTData_139, 0, sizeof(float)*N2);
    memset(FFTData_140, 0, sizeof(float)*N2);
    memset(FFTData_141, 0, sizeof(float)*N2);
    memset(FFTData_142, 0, sizeof(float)*N2);
    memset(FFTData_143, 0, sizeof(float)*N2);
    memset(FFTData_144, 0, sizeof(float)*N2);
    memset(FFTData_145, 0, sizeof(float)*N2);
    memset(FFTData_146, 0, sizeof(float)*N2);
    memset(FFTData_147, 0, sizeof(float)*N2);
    memset(FFTData_148, 0, sizeof(float)*N2);
    memset(FFTData_149, 0, sizeof(float)*N2);
    memset(FFTData_150, 0, sizeof(float)*N2);

    regionNum = m_demodulation->peakNum;
}

FFT::~FFT()
{

}

void FFT::run()
{

    //1.DEMOdata_fft split regions
    for(int k = 0; k<NN*regionNum; k+=regionNum){
        int p = k/regionNum;
        for(int q=0; q<regionNum;q++){
//            if(m_demodulation->DEMOdata_fft->isEmpty()) QThread::msleep(10);
            DemodataArray[q][p] = m_demodulation->DEMOdata_fft->pop();

//            DemodataArray[q][p] = 1; //ceshi
        }
    }

    //2.every region FFT, saving in fft_result_array
    n = NN;

    for(int k=0; k<regionNum; ++k){
        memset(xreal,0,sizeof(float)*N1);
        memset(ximag,0,sizeof(float)*N1);

        for(int i=0; i<n; i+=30){ //1/30的采样率 将60000个点采样成2000个
            int p=i/30;
            xreal[p] = DemodataArray[k][i];
            ximag[p] = 0;
        }

//        for(int i=0; i<N1; ++i){ //取前N1个点
//            int p=i/10;
//            xreal[i] = DemodataArray[k][i];
//            ximag[i] = 0;
//        }

        FFT_t (xreal, ximag, N1); //做fft的长度必须为2的整数次幂
        int N11 = N1/2;
        float xAbs[1024]; //长度为N11
        memset(xAbs,0,sizeof(float)*N1/2);
//        qDebug()<<xAbs[1];
        for(int s=1; s<(N11+1); ++s){
            xAbs[s-1] = sqrt(pow((xreal[s]/N1),2)+pow((ximag[s]/N1),2)) * 2;
        }
//        qDebug()<<xAbs[1]<<" ";
        std::copy(std::begin(xAbs),std::end(xAbs),fft_result_array[k]);
    }

//            QThread::sleep(2);
    //3.根据regionIndex选择区域
    //从30开始 将后一个容器的值复制到前一个容器
    //将fft_result_array[regionIndex]中的某400个点复制到FFTData_1
    memcpy(FFTData_150,FFTData_149,N2*sizeof(float));
    memcpy(FFTData_149,FFTData_148,N2*sizeof(float));
    memcpy(FFTData_148,FFTData_147,N2*sizeof(float));
    memcpy(FFTData_147,FFTData_146,N2*sizeof(float));
    memcpy(FFTData_146,FFTData_145,N2*sizeof(float));
    memcpy(FFTData_145,FFTData_144,N2*sizeof(float));
    memcpy(FFTData_144,FFTData_143,N2*sizeof(float));
    memcpy(FFTData_143,FFTData_142,N2*sizeof(float));
    memcpy(FFTData_142,FFTData_141,N2*sizeof(float));
    memcpy(FFTData_141,FFTData_140,N2*sizeof(float));
    memcpy(FFTData_140,FFTData_139,N2*sizeof(float));
    memcpy(FFTData_139,FFTData_138,N2*sizeof(float));
    memcpy(FFTData_138,FFTData_137,N2*sizeof(float));
    memcpy(FFTData_137,FFTData_136,N2*sizeof(float));
    memcpy(FFTData_136,FFTData_135,N2*sizeof(float));
    memcpy(FFTData_135,FFTData_134,N2*sizeof(float));
    memcpy(FFTData_134,FFTData_133,N2*sizeof(float));
    memcpy(FFTData_133,FFTData_132,N2*sizeof(float));
    memcpy(FFTData_132,FFTData_131,N2*sizeof(float));
    memcpy(FFTData_131,FFTData_130,N2*sizeof(float));
    memcpy(FFTData_130,FFTData_129,N2*sizeof(float));
    memcpy(FFTData_129,FFTData_128,N2*sizeof(float));
    memcpy(FFTData_128,FFTData_127,N2*sizeof(float));
    memcpy(FFTData_127,FFTData_126,N2*sizeof(float));
    memcpy(FFTData_126,FFTData_125,N2*sizeof(float));
    memcpy(FFTData_125,FFTData_124,N2*sizeof(float));
    memcpy(FFTData_124,FFTData_123,N2*sizeof(float));
    memcpy(FFTData_123,FFTData_122,N2*sizeof(float));
    memcpy(FFTData_122,FFTData_121,N2*sizeof(float));
    memcpy(FFTData_121,FFTData_120,N2*sizeof(float));
    memcpy(FFTData_120,FFTData_119,N2*sizeof(float));
    memcpy(FFTData_119,FFTData_118,N2*sizeof(float));
    memcpy(FFTData_118,FFTData_117,N2*sizeof(float));
    memcpy(FFTData_117,FFTData_116,N2*sizeof(float));
    memcpy(FFTData_116,FFTData_115,N2*sizeof(float));
    memcpy(FFTData_115,FFTData_114,N2*sizeof(float));
    memcpy(FFTData_114,FFTData_113,N2*sizeof(float));
    memcpy(FFTData_113,FFTData_112,N2*sizeof(float));
    memcpy(FFTData_112,FFTData_111,N2*sizeof(float));
    memcpy(FFTData_111,FFTData_110,N2*sizeof(float));
    memcpy(FFTData_110,FFTData_109,N2*sizeof(float));
    memcpy(FFTData_109,FFTData_108,N2*sizeof(float));
    memcpy(FFTData_108,FFTData_107,N2*sizeof(float));
    memcpy(FFTData_107,FFTData_106,N2*sizeof(float));
    memcpy(FFTData_106,FFTData_105,N2*sizeof(float));
    memcpy(FFTData_105,FFTData_104,N2*sizeof(float));
    memcpy(FFTData_104,FFTData_103,N2*sizeof(float));
    memcpy(FFTData_103,FFTData_102,N2*sizeof(float));
    memcpy(FFTData_102,FFTData_101,N2*sizeof(float));
    memcpy(FFTData_101,FFTData_100,N2*sizeof(float));
    memcpy(FFTData_100,FFTData_99,N2*sizeof(float));
    memcpy(FFTData_99,FFTData_98,N2*sizeof(float));
    memcpy(FFTData_98,FFTData_97,N2*sizeof(float));
    memcpy(FFTData_97,FFTData_96,N2*sizeof(float));
    memcpy(FFTData_96,FFTData_95,N2*sizeof(float));
    memcpy(FFTData_95,FFTData_94,N2*sizeof(float));
    memcpy(FFTData_94,FFTData_93,N2*sizeof(float));
    memcpy(FFTData_93,FFTData_92,N2*sizeof(float));
    memcpy(FFTData_92,FFTData_91,N2*sizeof(float));
    memcpy(FFTData_91,FFTData_90,N2*sizeof(float));
    memcpy(FFTData_90,FFTData_89,N2*sizeof(float));
    memcpy(FFTData_89,FFTData_88,N2*sizeof(float));
    memcpy(FFTData_88,FFTData_87,N2*sizeof(float));
    memcpy(FFTData_87,FFTData_86,N2*sizeof(float));
    memcpy(FFTData_86,FFTData_85,N2*sizeof(float));
    memcpy(FFTData_85,FFTData_84,N2*sizeof(float));
    memcpy(FFTData_84,FFTData_83,N2*sizeof(float));
    memcpy(FFTData_83,FFTData_82,N2*sizeof(float));
    memcpy(FFTData_82,FFTData_81,N2*sizeof(float));
    memcpy(FFTData_81,FFTData_80,N2*sizeof(float));
    memcpy(FFTData_80,FFTData_79,N2*sizeof(float));
    memcpy(FFTData_79,FFTData_78,N2*sizeof(float));
    memcpy(FFTData_78,FFTData_77,N2*sizeof(float));
    memcpy(FFTData_77,FFTData_76,N2*sizeof(float));
    memcpy(FFTData_76,FFTData_75,N2*sizeof(float));
    memcpy(FFTData_75,FFTData_74,N2*sizeof(float));
    memcpy(FFTData_74,FFTData_73,N2*sizeof(float));
    memcpy(FFTData_73,FFTData_72,N2*sizeof(float));
    memcpy(FFTData_72,FFTData_71,N2*sizeof(float));
    memcpy(FFTData_71,FFTData_70,N2*sizeof(float));
    memcpy(FFTData_70,FFTData_69,N2*sizeof(float));
    memcpy(FFTData_69,FFTData_68,N2*sizeof(float));
    memcpy(FFTData_68,FFTData_67,N2*sizeof(float));
    memcpy(FFTData_67,FFTData_66,N2*sizeof(float));
    memcpy(FFTData_66,FFTData_65,N2*sizeof(float));
    memcpy(FFTData_65,FFTData_64,N2*sizeof(float));
    memcpy(FFTData_64,FFTData_63,N2*sizeof(float));
    memcpy(FFTData_63,FFTData_62,N2*sizeof(float));
    memcpy(FFTData_62,FFTData_61,N2*sizeof(float));
    memcpy(FFTData_61,FFTData_60,N2*sizeof(float));
    memcpy(FFTData_60,FFTData_59,N2*sizeof(float));
    memcpy(FFTData_59,FFTData_58,N2*sizeof(float));
    memcpy(FFTData_58,FFTData_57,N2*sizeof(float));
    memcpy(FFTData_57,FFTData_56,N2*sizeof(float));
    memcpy(FFTData_56,FFTData_55,N2*sizeof(float));
    memcpy(FFTData_55,FFTData_54,N2*sizeof(float));
    memcpy(FFTData_54,FFTData_53,N2*sizeof(float));
    memcpy(FFTData_53,FFTData_52,N2*sizeof(float));
    memcpy(FFTData_52,FFTData_51,N2*sizeof(float));
    memcpy(FFTData_51,FFTData_50,N2*sizeof(float));
    memcpy(FFTData_50,FFTData_49,N2*sizeof(float));
    memcpy(FFTData_49,FFTData_48,N2*sizeof(float));
    memcpy(FFTData_48,FFTData_47,N2*sizeof(float));
    memcpy(FFTData_47,FFTData_46,N2*sizeof(float));
    memcpy(FFTData_46,FFTData_45,N2*sizeof(float));
    memcpy(FFTData_45,FFTData_44,N2*sizeof(float));
    memcpy(FFTData_44,FFTData_43,N2*sizeof(float));
    memcpy(FFTData_43,FFTData_42,N2*sizeof(float));
    memcpy(FFTData_42,FFTData_41,N2*sizeof(float));
    memcpy(FFTData_41,FFTData_40,N2*sizeof(float));
    memcpy(FFTData_40,FFTData_39,N2*sizeof(float));
    memcpy(FFTData_39,FFTData_38,N2*sizeof(float));
    memcpy(FFTData_38,FFTData_37,N2*sizeof(float));
    memcpy(FFTData_37,FFTData_36,N2*sizeof(float));
    memcpy(FFTData_36,FFTData_35,N2*sizeof(float));
    memcpy(FFTData_35,FFTData_34,N2*sizeof(float));
    memcpy(FFTData_34,FFTData_33,N2*sizeof(float));
    memcpy(FFTData_33,FFTData_32,N2*sizeof(float));
    memcpy(FFTData_32,FFTData_31,N2*sizeof(float));
    memcpy(FFTData_31,FFTData_30,N2*sizeof(float));
    memcpy(FFTData_30,FFTData_29,N2*sizeof(float));
    memcpy(FFTData_29,FFTData_28,N2*sizeof(float));
    memcpy(FFTData_28,FFTData_27,N2*sizeof(float));
    memcpy(FFTData_27,FFTData_26,N2*sizeof(float));
    memcpy(FFTData_26,FFTData_25,N2*sizeof(float));
    memcpy(FFTData_25,FFTData_24,N2*sizeof(float));
    memcpy(FFTData_24,FFTData_23,N2*sizeof(float));
    memcpy(FFTData_23,FFTData_22,N2*sizeof(float));
    memcpy(FFTData_22,FFTData_21,N2*sizeof(float));
    memcpy(FFTData_21,FFTData_20,N2*sizeof(float));
    memcpy(FFTData_20,FFTData_19,N2*sizeof(float));
    memcpy(FFTData_19,FFTData_18,N2*sizeof(float));
    memcpy(FFTData_18,FFTData_17,N2*sizeof(float));
    memcpy(FFTData_17,FFTData_16,N2*sizeof(float));
    memcpy(FFTData_16,FFTData_15,N2*sizeof(float));
    memcpy(FFTData_15,FFTData_14,N2*sizeof(float));
    memcpy(FFTData_14,FFTData_13,N2*sizeof(float));
    memcpy(FFTData_13,FFTData_12,N2*sizeof(float));
    memcpy(FFTData_12,FFTData_11,N2*sizeof(float));
    memcpy(FFTData_11,FFTData_10,N2*sizeof(float));
    memcpy(FFTData_10,FFTData_9,N2*sizeof(float));
    memcpy(FFTData_9,FFTData_8,N2*sizeof(float));
    memcpy(FFTData_8,FFTData_7,N2*sizeof(float));
    memcpy(FFTData_7,FFTData_6,N2*sizeof(float));
    memcpy(FFTData_6,FFTData_5,N2*sizeof(float));
    memcpy(FFTData_5,FFTData_4,N2*sizeof(float));
    memcpy(FFTData_4,FFTData_3,N2*sizeof(float));
    memcpy(FFTData_3,FFTData_2,N2*sizeof(float));
    memcpy(FFTData_2,FFTData_1,N2*sizeof(float));
    //        //test
    //        for(int i=0; i<N2; ++i){
    //            FFTData_1[i] = rand()%10;
    //        }
    //选择将ReginIndex区域的fft_result存入FFTData_1
    //选择存哪一段数据
    float temp[1105];
    memset(temp,0,sizeof (float)*1105);
    std::copy(fft_result_array[regionIndex],fft_result_array[regionIndex]+1024,temp);
    std::copy(fft_result_array[regionIndex]+410,fft_result_array[regionIndex]+1024+81,FFTData_1);

//    qDebug()<<"bb"<<endl;

}

void FFT::FFT_t(float xreal [], float ximag [], int n)
{
    // 快速傅立叶变换，将复数 x 变换后仍保存在 x 中，xreal, ximag 分别是 x 的实部和虚部
    float wreal[NN/2], wimag[NN / 2], treal, timag, ureal, uimag, arg;
    int m, k, j, t, index1, index2;

    bitrp (xreal, ximag, n);

    // 计算 1 的前 n / 2 个 n 次方根的共轭复数 W'j = wreal [j] + i * wimag [j] , j = 0, 1, ... , n / 2 - 1
    arg = - 2 * M_PI / n;
    treal = cos (arg);
    timag = sin (arg);
    wreal [0] = 1.0;
    wimag [0] = 0.0;
    for (j = 1; j < n / 2; j ++)
    {
        wreal [j] = wreal [j - 1] * treal - wimag [j - 1] * timag;
        wimag [j] = wreal [j - 1] * timag + wimag [j - 1] * treal;
    }

    for (m = 2; m <= n; m *= 2)
    {
        for (k = 0; k < n; k += m)
        {
            for (j = 0; j < m / 2; j ++)
            {
                index1 = k + j;
                index2 = index1 + m / 2;
                t = n * j / m;    // 旋转因子 w 的实部在 wreal [] 中的下标为 t
                treal = wreal [t] * xreal [index2] - wimag [t] * ximag [index2];
                timag = wreal [t] * ximag [index2] + wimag [t] * xreal [index2];
                ureal = xreal [index1];
                uimag = ximag [index1];
                xreal [index1] = ureal + treal;
                ximag [index1] = uimag + timag;
                xreal [index2] = ureal - treal;
                ximag [index2] = uimag - timag;
            }
        }
    }
}

void FFT::IFFT_t(float xreal[], float ximag[], int n)
{
    // 快速傅立叶逆变换
    float wreal [NN / 2], wimag [NN / 2], treal, timag, ureal, uimag, arg;
    int m, k, j, t, index1, index2;

    bitrp (xreal, ximag, n);

    // 计算 1 的前 n / 2 个 n 次方根 Wj = wreal [j] + i * wimag [j] , j = 0, 1, ... , n / 2 - 1
    arg = 2 * M_PI / n;
    treal = cos (arg);
    timag = sin (arg);
    wreal [0] = 1.0;
    wimag [0] = 0.0;
    for (j = 1; j < n / 2; j ++)
    {
        wreal [j] = wreal [j - 1] * treal - wimag [j - 1] * timag;
        wimag [j] = wreal [j - 1] * timag + wimag [j - 1] * treal;
    }

    for (m = 2; m <= n; m *= 2)
    {
        for (k = 0; k < n; k += m)
        {
            for (j = 0; j < m / 2; j ++)
            {
                index1 = k + j;
                index2 = index1 + m / 2;
                t = n * j / m;    // 旋转因子 w 的实部在 wreal [] 中的下标为 t
                treal = wreal [t] * xreal [index2] - wimag [t] * ximag [index2];
                timag = wreal [t] * ximag [index2] + wimag [t] * xreal [index2];
                ureal = xreal [index1];
                uimag = ximag [index1];
                xreal [index1] = ureal + treal;
                ximag [index1] = uimag + timag;
                xreal [index2] = ureal - treal;
                ximag [index2] = uimag - timag;
            }
        }
    }

    for (j=0; j < n; j ++)
    {
        xreal [j] /= n;
        ximag [j] /= n;
    }
}

void FFT::swap(float &a, float &b)
{
    float t;
    t = a;
    a = b;
    b = t;
}

void FFT::bitrp(float xreal[], float ximag[], int n)
{
    // 位反转置换 Bit-reversal Permutation
    int i, j, a, b, p;

    for (i = 1, p = 0; i < n; i *= 2)
    {
        p ++;
    }
    for (i = 0; i < n; i ++)
    {
        a = i;
        b = 0;
        for (j = 0; j < p; j ++)
        {
            b = (b << 1) + (a & 1);    // b = b * 2 + a % 2;
            a >>= 1;        // a = a / 2;
        }
        if ( b > i)
        {
            swap (xreal [i], xreal [b]);
            swap (ximag [i], ximag [b]);
        }
    }
}

void FFT::on_comboBox_region_currentIndexChangedSlot(int _regionIndex)
{
    regionIndex = _regionIndex;
    qDebug()<<"regionIndex = "<<regionIndex<<endl;
}
