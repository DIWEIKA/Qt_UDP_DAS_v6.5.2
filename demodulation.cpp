#include "demodulation.h"

//传入udp_recv下的CHdata即可解调
Demodulation::Demodulation(UDP_Recv* udp_Recv, int DemoFlashTime, int DemoFlashFreq, int freq, int peaknum):
    demoFlashTime(DemoFlashTime),
    demoFlashFreq(DemoFlashFreq),
    Freq(freq),
    peakNum(peaknum),
    RealPh(new float[peakNum]),
    PriorPh(new float[peakNum]),
    K(new float[peakNum]),
    PriorK(new float[peakNum]),
    RealPhReg(new float[peakNum][FILTERODR]),
    RealPhOut(new float[peakNum][FILTERODR]),
    HPFilterCoeff(new float[54]),
    cnt(new unsigned long[peakNum]),
    FirstRealPh(new float[peakNum]),
    FirstIn_n(new int[peakNum])
{
    udp_recv = udp_Recv;

    DEMOdata_flash = make_shared<CirQueue<float>>(peakNum*Freq/demoFlashFreq); //量化存储容器的大小
    DEMOdata_save = make_shared<CirQueue<float>>(peakNum*Freq*60); //量化存储容器的大小

    //    demo_CHdata = new unsigned char[READ_LENGTH](); //动态数组初始化
    //    Vi = new float[CHDATA_LENGTH]();
    //    Vq = new float[CHDATA_LENGTH]();
    //    Ph = new float[CHDATA_LENGTH]();
    //    atanTable = new float[NUMTABLE]();
    //    demo_CHdata_DEC_all = new int[CHDATA_ALL_LENGTH]();
    //    demo_CHdata_DEC_1 = new int[CHDATA_LENGTH]();
    //    demo_CHdata_DEC_2 = new int[CHDATA_LENGTH]();
    //    demo_CHdata_DEC_3 = new int[CHDATA_LENGTH]();
    //    demo_CHdata_DEC_4 = new int[CHDATA_LENGTH]();

    //    RealPh = new float[peakNum]();
    //    PriorPh = new float[peakNum]();
    //    K=new float[peakNum]();
    //    PriorK=new float[peakNum]();

    readAtanTable(atanTable);

    //    RealPhReg = new float[peakNum][FILTERODR]();
    //    RealPhOut = new float[peakNum][FILTERODR]();

    //    HPFilterCoeff = new float[54]();
    ReadFilterCoeff(HPFilterCoeff);

    //    cnt=new unsigned long[peakNum]();
    //    FirstRealPh=new float[peakNum]();
    //    FirstIn_n=new int[peakNum]();
}

Demodulation::~Demodulation()
{
    FreeMemory();
}


void Demodulation::run()
{
    while(1){

        /*------------遍历CHdataArray[0]即可---------------*/

        if(udp_recv->isStart){

            //1. CHdataArray[0] >> demo_CHdata
            bool isHeadFream = 0;

            //判断前16位是否是6666666666666666，若不是则继续找;
            //若是则从当前位置开始存入一个6666666666666666到6666666666666666之间的长度，即一个峰值点的数据到demo_CHdata中
            do{
//                   if(udp_recv->CHdata1->isEmpty())  msleep(100);
                if(udp_recv->CHdata1->pop() == '6' ){
//                    if(udp_recv->CHdata1->isEmpty())  msleep(10);
                    if(udp_recv->CHdata1->pop() == '6' ){
//                       if(udp_recv->CHdata1->isEmpty())  msleep(10);
                        if(udp_recv->CHdata1->pop() == '6' ){
//                             if(udp_recv->CHdata1->isEmpty())  msleep(6);
                            if(udp_recv->CHdata1->pop() == '6' ){
//                                if(udp_recv->CHdata1->pop() == '6' ){
////                                     if(udp_recv->CHdata1->isEmpty())  msleep(10);
//                                    if(udp_recv->CHdata1->pop() == '6' ){
////                                         if(udp_recv->CHdata1->isEmpty())  msleep(10);
//                                        if(udp_recv->CHdata1->pop() == '6' ){
////                                             if(udp_recv->CHdata1->isEmpty())  msleep(10);
//                                            if(udp_recv->CHdata1->pop() == '6' ){
//                                                if(udp_recv->CHdata1->pop() == '6' ){
////                                                if(udp_recv->CHdata1->isEmpty())  msleep(10);
//                                                    if(udp_recv->CHdata1->pop() == '6' ){
////                                                         if(udp_recv->CHdata1->isEmpty())  msleep(10);
//                                                        if(udp_recv->CHdata1->pop() == '6' ){
////                                                             if(udp_recv->CHdata1->isEmpty())  msleep(10);
//                                                            if(udp_recv->CHdata1->pop() == '6' ){
//                                                                if(udp_recv->CHdata1->pop() == '6' ){
////                                                                     if(udp_recv->CHdata1->isEmpty())  msleep(10);
//                                                                    if(udp_recv->CHdata1->pop() == '6' ){
////                                                                        if(udp_recv->CHdata1->isEmpty())  msleep(10);
//                                                                        if(udp_recv->CHdata1->pop() == '6' ){
////                                                                             if(udp_recv->CHdata1->isEmpty())  msleep(10);
//                                                                            if(udp_recv->CHdata1->pop() == '6' ){

                                                                                sizeoCHdata = peakNum*16; //两个6666666666666666之间的长度

                                                                                demo_CHdata[0] = '6';
                                                                                demo_CHdata[1] = '6';
                                                                                demo_CHdata[2] = '6';
                                                                                demo_CHdata[3] = '6';
//                                                                                demo_CHdata[4] = '6';
//                                                                                demo_CHdata[5] = '6';
//                                                                                demo_CHdata[6] = '6';
//                                                                                demo_CHdata[7] = '6';
//                                                                                demo_CHdata[8] = '6';
//                                                                                demo_CHdata[9] = '6';
//                                                                                demo_CHdata[10] = '6';
//                                                                                demo_CHdata[11] = '6';
//                                                                                demo_CHdata[12] = '6';
//                                                                                demo_CHdata[13] = '6';
//                                                                                demo_CHdata[14] = '6';
//                                                                                demo_CHdata[15] = '6';

                                                                                //从16开始存读sizeoCHdata长度
                                                                                for( int j=4; j<sizeoCHdata; ++j){
                                                                                         if(udp_recv->CHdata1->isEmpty())  msleep(10);
//                                                                                    unsigned char usCHdata = udp_recv->CHdata1->pop();
                                                                                    demo_CHdata[j] = udp_recv->CHdata1->pop();
                                                                                }

                                                                                isHeadFream = 1;

                                                                                qDebug()<<"Found 6666666666666666!!"<<endl;
//                                                                            }
//                                                                        }
//                                                                    }
//                                                                }
//                                                            }
//                                                        }
//                                                    }
//                                                }
//                                            }
//                                        }
//                                    }
//                                }
                            }
                        }
                    }
                }


            }while (isHeadFream==0) ;//isHeadFream == 0时循环，直到不等于0跳出循环

//            //1.CHdatax >> demo_CHdatax[]

//            memcpy(demo_CHdatax,udp_recv->CHdatax,sizeof(char)*2048);

            //2. demo_CHdata[] >> demo_CHdata_DEC_all[]
            int sizeoDemodata = sizeoCHdata;

            for(int m = 0; m<sizeoDemodata; m+=4){
                bool ok;
                int number_DEC = QString(demo_CHdata[m]).toInt(&ok,16)*0
                        + QString(demo_CHdata[m+1]).toInt(&ok,16)*256
                        + QString(demo_CHdata[m+2]).toInt(&ok,16)*16
                        +QString(demo_CHdata[m+3]).toInt(&ok,16)*1;
                if(number_DEC>2047)
                    number_DEC = number_DEC-4096;
                int n = m/4/*-4*/;
                demo_CHdata_DEC_all[n] = number_DEC;
            }

//             memset(demo_CHdatax,'\0',sizeof(char)); //清空数组

            //3. demo_CHdata_DEC_all[] split into 4 channels
            for(int k = 0; k<(sizeoDemodata/*-16*/)/4; k+=4){
                int p = k/4;
                demo_CHdata_DEC_1[p] = demo_CHdata_DEC_all[k];
                demo_CHdata_DEC_2[p] = demo_CHdata_DEC_all[k+1];
                demo_CHdata_DEC_3[p] = demo_CHdata_DEC_all[k+2];
                demo_CHdata_DEC_4[p] = demo_CHdata_DEC_all[k+3];
            }

            //4. get Vi Vq
            for(int t = 0; t<(sizeoDemodata/*-16*/)/16; t++){
                Vi[t] = (float)(demo_CHdata_DEC_1[t] + demo_CHdata_DEC_2[t] - 2 * demo_CHdata_DEC_3[t]);
                Vq[t] = (float)(-sqrt(3) * (demo_CHdata_DEC_1[t] - demo_CHdata_DEC_2[t]));

                /*------------5. Demodulate Phase--------------*/
                Ph[t]=demoduPh(Vi[t],Vq[t]);


                /*---------------Unwrap Phase & HpFilte Phase---------------*/
                RealPh[t] = Unwrap(Ph[t], t);


                //6.Ph[] >> DEMOdata_flash ; Ph[] >> DEMOdata_save
                DEMOdata_flash->push(RealPh[t]);
                DEMOdata_save->push(RealPh[t]);
            }

            qDebug()<<"aa"<<endl;

        } // end if



    }//end while

}

//读取反正切值查表文件
void Demodulation::readAtanTable(float *roundNum){
    QString tableFileName;
    tableFileName = QString("C:/Qt_UDP_DAS/atanTable.bin");
    QString path= tableFileName;
    qDebug()<<"atan table file path:"<<path.toStdString().c_str();
    FILE *tableFile=fopen(path.toStdString().c_str(),"rb");
    if(tableFile == NULL)
    {
        char logStr2[64];
        sprintf(logStr2,"Open %s Failed!\n",path.toStdString().c_str());

    }
    fread(roundNum,sizeof(float),201,tableFile);
    fclose(tableFile);
}

//查表法反正切相位解调
float Demodulation::demoduPh(float vi,float vq){
    float absVi=abs(vi);
    float absVq=abs(vq);
    float z=0,z0=0,dz=0,ph0=0,ph=0;
    int numZ0=0;

    if(absVi>=absVq){
        if(vi>0){//111 110
            z=-vq/vi;
            z0=(float) (round(z*100.0)/100.0);//0.01步进的反正切值
            numZ0=(int) (100+z0/0.01);//z0=-1:0.01:1,将其编号为1：1：201
            dz=(z-z0)/(1+(z*z0));
            ph0=dz+atanTable[numZ0];//查表法
            ph=ph0;
        }
        else if(vi==0){
            ph=0;
        }
        else {//vi<0  101 100
            z=-vq/vi;
            z0=(float) (round(z*100.0)/100.0);//0.01步进的反正切值
            numZ0=(int) (100+z0/0.01);//z0=-1:0.01:1,将其编号为1：1：201
            dz=(z-z0)/(1+(z*z0));
            ph0=dz+atanTable[numZ0];//查表法
            ph= ( ((-vq)>=0) ? 1: -1 ) *M_PI+ph0;
        }
    }
    else {//absVi<absVq
        if(vq<0){//-vq>0
            z=-vi/vq;
            z0=(float) (round(z*100.0)/100.0);//0.01步进的反正切值
            numZ0=(int) (100+z0/0.01);//z0=-1:0.01:1,将其编号为1：1：201
            dz=(z-z0)/(1+(z*z0));
            ph0=dz+atanTable[numZ0];//查表法
            ph=0.5*M_PI-ph0;
        }
        else {//-vq<0
            z=-vi/vq;
            z0=(float) (round(z*100.0)/100.0);//0.01步进的反正切值
            numZ0=(int) (100+z0/0.01);//z0=-1:0.01:1,将其编号为1：1：201
            dz=(z-z0)/(1+(z*z0));
            ph0=dz+atanTable[numZ0];//查表法
            ph=-0.5*M_PI-ph0;
        }
    }
    return ph;
}

//相位解缠绕
float Demodulation::Unwrap(float ph, int i)
{
    if((ph - PriorPh[i]) > M_PI)//PriorPh[i]时间轴上上一个数据
        K[i] = PriorK[i] - 1;//PriorK是K时间轴上上一个数据
    else if((ph - PriorPh[i]) < -M_PI)
        K[i] = PriorK[i] + 1;
    else
        K[i] = PriorK[i];

    RealPh[i] = (float)(ph + 2*K[i]*M_PI);
    PriorPh[i] = ph;
    PriorK[i] = K[i];

    if(FirstIn_n[i] == 0)
    {
        FirstRealPh[i] = RealPh[i];
        FirstIn_n[i] = 1;
    }

    RealPh[i] -= FirstRealPh[i];

    //调用高通滤波函数
    Hpfilter(i);

    float HPRealPh = RealPhOut[i][2];

    return HPRealPh; //返回滤波后数据

//    return RealPh[i]; //返回滤波前数据
}

void Demodulation::FreeMemory()
{
    delete[] RealPh;
    delete[] PriorPh;
    delete[] K;
    delete[] PriorK;
    delete[] HPFilterCoeff;
    //    delete[] LPFilterCoeff;
    delete[] FirstRealPh;
    delete[] FirstIn_n;
    delete[] RealPhReg;
    delete[] RealPhOut;
    //    delete[] FilterReg;
    delete[] cnt;
    delete[] demo_CHdatax;
}

//读取本地buttorworth高通滤波器至*HPFcoeff
void Demodulation::ReadFilterCoeff(float *HPFcoeff/*, float *LPFcoeff*/)
{
    //    QString fileName = QString::fromLocal8Bit(hpcutoff.data());
    //    QString fileName2 = QString::fromLocal8Bit(lpcutoff.data());

    //fileName = QString("ButtorWorthFilterCoefficient_")+QString::number((int)(frequency/1000))+QString("KHz_50Hz.bin");
    //fileName = QString("ChebysheyIIFilterCoefficient_Order8_4Section_")+QString::number((int)(frequency/1000))+QString("KHz_1Hz.bin");//1Hz的高通滤波器文件名为ButtorWorthFilterCoefficient_Order8_1KHz_1Hz
    //fileName2 = QString("LPFilterCoefficient_")+QString::number((int)(frequency/1000))+QString("KHz_400Hz.bin");// 400Hz低通滤波器文件名LPFilterCoefficient_1KHz_400Hz.bin

    QString pat = QString("C:/Qt_UDP_DAS/ButtorWorthFilterCoefficient_10KHz_5Hz.bin");
    //    QString pat2 = QString("C:/DAS/ButtorWorthFilterCoefficient/") + fileName2;

    //    qDebug()<<"Filter Coefficient path:"<<pat.toStdString().c_str()<<"  "<<pat2.toStdString().c_str();

    QFile pFile(pat);
    //    QFile pFile2(pat2);
    if(!pFile.exists())
    {
        char logStr[64];
        sprintf(logStr,"Open %s Failed!.",pat.toStdString().c_str());

        //        isWaveFiletr = false;
    }
    else
    {
        //        isWaveFiletr = true;
        ifstream inFile(pat.toStdString().data(), ifstream::binary);
        for(int i = 0 ; i < FILTERODR; i++)
        {
            inFile.read((char*)(HPFcoeff + i), sizeof(float));
            qDebug() << "coeff[" << i << "] = " << HPFcoeff[i] << endl;
        }
        inFile.close();
    }

    //    if(!pFile2.exists())
    //    {
    //        char logStr[64];
    //        sprintf(logStr,"Open %s Failed!.",pat2.toStdString().c_str());

    ////        isWaveLpFilter = false;
    //    }
    //    else
    //    {
    ////        isWaveLpFilter = true;
    //        ifstream inFile2(pat2.toStdString().data(), ifstream::binary);
    //        for(int i = 0 ; i < LPFILTERODR; i++)
    //        {
    //            inFile2.read((char*)(LPFcoeff + i), sizeof(float));
    //            qDebug() << "LPFcoeff[" << i << "] = " << LPFcoeff[i] << endl;
    //        }
    //        inFile2.close();
    //    }

}

//RealPhOut存放滤波后数据
void Demodulation::Hpfilter(int i)
{
    RealPhReg[i][0]=RealPhReg[i][1];
    RealPhReg[i][1]=RealPhReg[i][2];
    RealPhReg[i][2] = RealPh[i]-FirstRealPh[i];

    cnt[i] ++;//滤波执行计数
    if(cnt[i]>2){
        //二阶巴特沃斯滤波，1 * outdata(i)=FilterCoeff(0) * data(i) + FilterCoeff(1) * data(i - 1) + FilterCoeff(2) * data(i-2) - FilterCoeff*outdata(i-1)-b2*outdata(i-2);
        RealPhOut[i][0]=RealPhOut[i][1];
        RealPhOut[i][1]=RealPhOut[i][2];
        //此处的程序已经改成和上面滤波的符号相同，因此以后生成的滤波器系数文件 只需要直接粘贴matlab里fdatools生成的。
        RealPhOut[i][2] = HPFilterCoeff[0] * RealPhReg[i][2] + HPFilterCoeff[1] * RealPhReg[i][1] +
                HPFilterCoeff[2] * RealPhReg[i][0] - HPFilterCoeff[3] * RealPhOut[i][1] - HPFilterCoeff[4] * RealPhOut[i][0];
        cnt[i] = 3;
    }

}
