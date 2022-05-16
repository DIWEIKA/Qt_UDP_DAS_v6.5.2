#include "demodulation.h"

//传入udp_recv下的CHdata即可解调
Demodulation::Demodulation(UDP_Recv* udp_Recv)
{
    //init
    udp_recv = udp_Recv;

    DEMOdata = make_shared<CirQueue<float>>(LenoDemo);

    readAtanTable(atanTable);
}

void Demodulation::run()
{
 /*------------遍历CHdataArray里的所有容器---------------*/
    for(int i = 0; i< SaveNumber; i++){

        if(udp_recv->CHdataArray[i]->isEmpty())
            continue;
        else
        {
            //1. 一个容器的CHdata >> demo_CHdata
            demo_CHdata[READ_LENGTH] = {'\0'};

            unsigned int sizeoCHdata = udp_recv->CHdataArray[i]->size();

            for(unsigned int j=0; j<sizeoCHdata; ++j){
                unsigned char usCHdata = udp_recv->CHdataArray[i]->pop();
                demo_CHdata[j] = usCHdata;
            }

            udp_recv->CHdataArray[i]->clear();

            //2. demo_CHdata[] >> demo_CHdata_DEC_all[]
            for(int m = 0; m<READ_LENGTH; m+=4){
                bool ok;
                int number_DEC = QString(demo_CHdata[m]).toInt(&ok,16)*0 + QString(demo_CHdata[m+1]).toInt(&ok,16)*256 + QString(demo_CHdata[m+2]).toInt(&ok,16)*16 +QString(demo_CHdata[m+3]).toInt(&ok,16)*1;
                if(number_DEC>2047)
                    number_DEC = number_DEC-4096;
                int n = m/4;
                demo_CHdata_DEC_all[n] = number_DEC;
            }

            //3. demo_CHdata_DEC_all[] split into 4 channels
            for(int k = 0; k<CHDATA_ALL_LENGTH; k+=4){
                int p = k/4;
                demo_CHdata_DEC_1[p] = demo_CHdata_DEC_all[k];
                demo_CHdata_DEC_2[p] = demo_CHdata_DEC_all[k+1];
                demo_CHdata_DEC_3[p] = demo_CHdata_DEC_all[k+2];
                demo_CHdata_DEC_4[p] = demo_CHdata_DEC_all[k+3];
            }

            //4. get Vi Vq
            for(int t = 0; t<CHDATA_LENGTH; t++){
                Vi[t] = (float)(demo_CHdata_DEC_1[t] + demo_CHdata_DEC_2[t] - 2 * demo_CHdata_DEC_3[t]);
                Vq[t] = (float)(-sqrt(3) * (demo_CHdata_DEC_1[t] - demo_CHdata_DEC_2[t]));

                //5. 相位解调
                Ph[t]=demoduPh(Vi[t],Vq[t]);

                //6.Ph[] >> DEMOdata
                DEMOdata->push(Ph[t]);
            }

            //7. send to demowave_widget
            emit sendToDemoWave_widget(DEMOdata);

             udp_recv->CHdataArray[i]->clear();
        }
    }

/*------------存储解调数据DEMOdata到本地---------------*/
    dateTime = QDateTime::currentDateTime();

    saveFileDemo = QString("F:/Desktop/UDPConnect/data/")+QString("[Demo]")+dateTime.toString("yyyyMMddhhmmss")+ QString(".bin");

    outfileDemo.open(saveFileDemo.toStdString().data(), ofstream::binary);

    if (!outfileDemo.is_open()) return;

    int sizeofDEMOdata = DEMOdata->size();

    for(int i = 0; i<sizeofDEMOdata; i++){
        outfileDemo.write((const char*)DEMOdata->begin(),sizeof(float));
        DEMOdata->pop();
    }

    outfileDemo.close();

    //clear DEMOdata
    DEMOdata->clear();
}

//读取反正切值查表文件
void Demodulation::readAtanTable(float *roundNum){
    QString tableFileName;
    tableFileName = QString("atanTable.bin");
    QString path=QString("F:/Desktop/UDPConnect/")+tableFileName;//文件地址当在仪表时需要重新设置。
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
