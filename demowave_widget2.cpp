#include "demowave_widget2.h"
#include "ui_demowave_widget2.h"

demowave_widget2::demowave_widget2(Demodulation *demodulation, FFT *_fft):
    ui(new Ui::demowave_widget2),
    demodu(demodulation),
    RegionIndex(0),
    peakNum(demodu->peakNum),
    m_fft(_fft)
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);

    setHtmlPages();

    initComboBox_Region();

    memset(Demodata_1, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_2, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_3, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_4, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_5, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_6, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_7, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_8, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_9, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_10, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_11, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_12, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_13, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_14, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_15, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_16, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_17, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_18, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_19, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_20, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_21, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_22, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_23, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_24, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_25, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_26, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_27, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_28, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_29, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_30, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_31, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_32, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_33, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_34, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_35, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_36, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_37, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_38, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_39, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_40, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_41, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_42, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_43, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_44, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_45, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_46, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_47, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_48, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_49, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_50, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_51, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_52, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_53, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_54, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_55, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_56, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_57, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_58, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_59, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_60, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_61, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_62, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_63, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_64, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_65, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_66, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_67, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_68, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_69, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_70, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_71, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_72, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_73, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_74, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_75, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_76, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_77, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_78, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_79, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_80, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_81, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_82, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_83, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_84, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_85, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_86, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_87, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_88, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_89, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_90, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_91, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_92, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_93, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_94, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_95, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_96, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_97, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_98, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_99, 0, sizeof(float)*REGION_DATA_LENGTH);
    memset(Demodata_100, 0, sizeof(float)*REGION_DATA_LENGTH);


    DemodataArray[0]=Demodata_1;
    DemodataArray[1]=Demodata_2;
    DemodataArray[2]=Demodata_3;
    DemodataArray[3]=Demodata_4;
    DemodataArray[4]=Demodata_5;
    DemodataArray[5]=Demodata_6;
    DemodataArray[6]=Demodata_7;
    DemodataArray[7]=Demodata_8;
    DemodataArray[8]=Demodata_9;
    DemodataArray[9]=Demodata_10;
    DemodataArray[10]=Demodata_11;//region11
    DemodataArray[11]=Demodata_12;
    DemodataArray[12]=Demodata_13;
    DemodataArray[13]=Demodata_14;
    DemodataArray[14]=Demodata_15;
    DemodataArray[15]=Demodata_16;
    DemodataArray[16]=Demodata_17;
    DemodataArray[17]=Demodata_18;
    DemodataArray[18]=Demodata_19;
    DemodataArray[19]=Demodata_20;
    DemodataArray[20]=Demodata_21;//region21
    DemodataArray[21]=Demodata_22;
    DemodataArray[22]=Demodata_23;
    DemodataArray[23]=Demodata_24;
    DemodataArray[24]=Demodata_25;
    DemodataArray[25]=Demodata_26;
    DemodataArray[26]=Demodata_27;
    DemodataArray[27]=Demodata_28;
    DemodataArray[28]=Demodata_29;
    DemodataArray[29]=Demodata_30;
    DemodataArray[30]=Demodata_31;//region31
    DemodataArray[31]=Demodata_32;
    DemodataArray[32]=Demodata_33;
    DemodataArray[33]=Demodata_34;
    DemodataArray[34]=Demodata_35;
    DemodataArray[35]=Demodata_36;
    DemodataArray[36]=Demodata_37;
    DemodataArray[37]=Demodata_38;
    DemodataArray[38]=Demodata_39;
    DemodataArray[39]=Demodata_40;
    DemodataArray[40]=Demodata_41;//region41
    DemodataArray[41]=Demodata_42;
    DemodataArray[42]=Demodata_43;
    DemodataArray[43]=Demodata_44;
    DemodataArray[44]=Demodata_45;
    DemodataArray[45]=Demodata_46;
    DemodataArray[46]=Demodata_47;
    DemodataArray[47]=Demodata_48;
    DemodataArray[48]=Demodata_49;
    DemodataArray[49]=Demodata_50;
    DemodataArray[50]=Demodata_51;//region51
    DemodataArray[51]=Demodata_52;
    DemodataArray[52]=Demodata_53;
    DemodataArray[53]=Demodata_54;
    DemodataArray[54]=Demodata_55;
    DemodataArray[55]=Demodata_56;
    DemodataArray[56]=Demodata_57;
    DemodataArray[57]=Demodata_58;
    DemodataArray[58]=Demodata_59;
    DemodataArray[59]=Demodata_60;
    DemodataArray[60]=Demodata_61;//region61
    DemodataArray[61]=Demodata_62;
    DemodataArray[62]=Demodata_63;
    DemodataArray[63]=Demodata_64;
    DemodataArray[64]=Demodata_65;
    DemodataArray[65]=Demodata_66;
    DemodataArray[66]=Demodata_67;
    DemodataArray[67]=Demodata_68;
    DemodataArray[68]=Demodata_69;
    DemodataArray[69]=Demodata_70;
    DemodataArray[70]=Demodata_71;//region71
    DemodataArray[71]=Demodata_72;
    DemodataArray[72]=Demodata_73;
    DemodataArray[73]=Demodata_74;
    DemodataArray[74]=Demodata_75;
    DemodataArray[75]=Demodata_76;
    DemodataArray[76]=Demodata_77;
    DemodataArray[77]=Demodata_78;
    DemodataArray[78]=Demodata_79;
    DemodataArray[79]=Demodata_80;
    DemodataArray[80]=Demodata_81;//region81
    DemodataArray[81]=Demodata_82;
    DemodataArray[82]=Demodata_83;
    DemodataArray[83]=Demodata_84;
    DemodataArray[84]=Demodata_85;
    DemodataArray[85]=Demodata_86;
    DemodataArray[86]=Demodata_87;
    DemodataArray[87]=Demodata_88;
    DemodataArray[88]=Demodata_89;
    DemodataArray[89]=Demodata_90;
    DemodataArray[90]=Demodata_91;//region91
    DemodataArray[91]=Demodata_92;
    DemodataArray[92]=Demodata_93;
    DemodataArray[93]=Demodata_94;
    DemodataArray[94]=Demodata_95;
    DemodataArray[95]=Demodata_96;
    DemodataArray[96]=Demodata_97;
    DemodataArray[97]=Demodata_98;
    DemodataArray[98]=Demodata_99;
    DemodataArray[99]=Demodata_100;//region100
}

demowave_widget2::~demowave_widget2()
{
    delete ui;
    delete[] DemodataArray;
}

void demowave_widget2::setHtmlPages()
{
    setWindowTitle(QString("Demodulation Wave Display"));

    m_demowave_widget = ui->demowave_widget;
    m_demowave_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_demowave_widget->load(QUrl::fromLocalFile(QString("C:/Qt_UDP_DAS/PAGE/tpl03/DemoWaveDisplay.html")));

    webChannel4 = new QWebChannel;

    webobj4 = new WebClass();

    webChannel4->registerObject("webobj4", webobj4);

    m_demowave_widget->page()->setWebChannel(webChannel4);

}

void demowave_widget2::initComboBox_Region()
{
//    peakNum = 4; //test

    QJsonObject region_obj;
    QJsonArray region_json;
    region_json.push_back(peakNum);
    region_obj.insert("region_num",region_json);
    QString region_str = QJsonDocument(region_obj).toJson();
    QString region_js = QString("get_region_num(%1)").arg(region_str);
    m_demowave_widget->page()->runJavaScript(region_js);
}

////返回labels对应的位置
//QVector<double> demowave_widget2::labelPositions(const QVector<QString> &labels, double offset)
//{
//    QVector<double> result(labels.size());
//        for (int i = 0; i < labels.size(); ++i)
//            result[i] = i + offset;
//        return result;
//}

void demowave_widget2::FreeMemory()
{
    delete[] DemodataArray;
}

//刷新波形显示
void demowave_widget2::FlashWave()
{
    qDebug() <<"Flash Demodulation Wave Slot responsed !"<<endl;

    int regionNum = peakNum;

    int sizeoDemoData = demodu->DEMOdata_flash->size();

    //重设sizeoDemoData的长度，使其为regionNum的倍数
//    int sizeoDemoData = regionNum * 1000; //test
//    int NN1 = REGION_DATA_LENGTH;//test
    int NN1 = sizeoDemoData/regionNum;
    sizeoDemoData = NN1*regionNum;


    //DEMOdata[] split regions
    for(int k = 0; k<sizeoDemoData; k+=regionNum){
        int p = k/regionNum;
        for(int q=0; q<regionNum;q++){
//            if(demodu->DEMOdata_flash->isEmpty()) QThread::msleep(100);
            DemodataArray[q][p] = demodu->DEMOdata_flash->pop();
//            DemodataArray[q][p] = 1.0; //ceshi
        }
    }

    //dispaly demo wave
    QJsonObject demo_wave_obj;
    QJsonArray demo_wave_json1,demo_wave_json2;
    for(int i = 0; i<NN1; i++) demo_wave_json1.push_back(DemodataArray[RegionIndex][i]);
    demo_wave_obj.insert("demo_wave",demo_wave_json1);
    demo_wave_json2.push_back(NN1);
    demo_wave_obj.insert("N1",demo_wave_json2);
    QString demo_wave_str = QJsonDocument(demo_wave_obj).toJson();
    QString demo_wave_js = QString("demowave_flash(%1)").arg(demo_wave_str);
    m_demowave_widget->page()->runJavaScript(demo_wave_js);

    //fft display
    QJsonObject fft_obj;
    QJsonArray fft_json1;
    QJsonArray fft_json2;
    QJsonArray fft_json3;
    QJsonArray fft_json4;
    QJsonArray fft_json5;
    QJsonArray fft_json6;
    QJsonArray fft_json7;
    QJsonArray fft_json8;
    QJsonArray fft_json9;
    QJsonArray fft_json10;
    QJsonArray fft_json11;
    QJsonArray fft_json12;
    QJsonArray fft_json13;
    QJsonArray fft_json14;
    QJsonArray fft_json15;
    QJsonArray fft_json16;
    QJsonArray fft_json17;
    QJsonArray fft_json18;
    QJsonArray fft_json19;
    QJsonArray fft_json20;
    QJsonArray fft_json21;
    QJsonArray fft_json22;
    QJsonArray fft_json23;
    QJsonArray fft_json24;
    QJsonArray fft_json25;
    QJsonArray fft_json26;
    QJsonArray fft_json27;
    QJsonArray fft_json28;
    QJsonArray fft_json29;
    QJsonArray fft_json30;
    QJsonArray fft_json31;
    QJsonArray fft_json32;
    QJsonArray fft_json33;
    QJsonArray fft_json34;
    QJsonArray fft_json35;
    QJsonArray fft_json36;
    QJsonArray fft_json37;
    QJsonArray fft_json38;
    QJsonArray fft_json39;
    QJsonArray fft_json40;
    QJsonArray fft_json41;
    QJsonArray fft_json42;
    QJsonArray fft_json43;
    QJsonArray fft_json44;
    QJsonArray fft_json45;
    QJsonArray fft_json46;
    QJsonArray fft_json47;
    QJsonArray fft_json48;
    QJsonArray fft_json49;
    QJsonArray fft_json50;
    QJsonArray fft_json51;
    QJsonArray fft_json52;
    QJsonArray fft_json53;
    QJsonArray fft_json54;
    QJsonArray fft_json55;
    QJsonArray fft_json56;
    QJsonArray fft_json57;
    QJsonArray fft_json58;
    QJsonArray fft_json59;
    QJsonArray fft_json60;
    QJsonArray fft_json61;
    QJsonArray fft_json62;
    QJsonArray fft_json63;
    QJsonArray fft_json64;
    QJsonArray fft_json65;
    QJsonArray fft_json66;
    QJsonArray fft_json67;
    QJsonArray fft_json68;
    QJsonArray fft_json69;
    QJsonArray fft_json70;
    QJsonArray fft_json71;
    QJsonArray fft_json72;
    QJsonArray fft_json73;
    QJsonArray fft_json74;
    QJsonArray fft_json75;
    QJsonArray fft_json76;
    QJsonArray fft_json77;
    QJsonArray fft_json78;
    QJsonArray fft_json79;
    QJsonArray fft_json80;
    QJsonArray fft_json81;
    QJsonArray fft_json82;
    QJsonArray fft_json83;
    QJsonArray fft_json84;
    QJsonArray fft_json85;
    QJsonArray fft_json86;
    QJsonArray fft_json87;
    QJsonArray fft_json88;
    QJsonArray fft_json89;
    QJsonArray fft_json90;
    QJsonArray fft_json91;
    QJsonArray fft_json92;
    QJsonArray fft_json93;
    QJsonArray fft_json94;
    QJsonArray fft_json95;
    QJsonArray fft_json96;
    QJsonArray fft_json97;
    QJsonArray fft_json98;
    QJsonArray fft_json99;
    QJsonArray fft_json100;
    QJsonArray fft_json101;
    QJsonArray fft_json102;
    QJsonArray fft_json103;
    QJsonArray fft_json104;
    QJsonArray fft_json105;
    QJsonArray fft_json106;
    QJsonArray fft_json107;
    QJsonArray fft_json108;
    QJsonArray fft_json109;
    QJsonArray fft_json110;
    QJsonArray fft_json111;
    QJsonArray fft_json112;
    QJsonArray fft_json113;
    QJsonArray fft_json114;
    QJsonArray fft_json115;
    QJsonArray fft_json116;
    QJsonArray fft_json117;
    QJsonArray fft_json118;
    QJsonArray fft_json119;
    QJsonArray fft_json120;
    QJsonArray fft_json121;
    QJsonArray fft_json122;
    QJsonArray fft_json123;
    QJsonArray fft_json124;
    QJsonArray fft_json125;
    QJsonArray fft_json126;
    QJsonArray fft_json127;
    QJsonArray fft_json128;
    QJsonArray fft_json129;
    QJsonArray fft_json130;
    QJsonArray fft_json131;
    QJsonArray fft_json132;
    QJsonArray fft_json133;
    QJsonArray fft_json134;
    QJsonArray fft_json135;
    QJsonArray fft_json136;
    QJsonArray fft_json137;
    QJsonArray fft_json138;
    QJsonArray fft_json139;
    QJsonArray fft_json140;
    QJsonArray fft_json141;
    QJsonArray fft_json142;
    QJsonArray fft_json143;
    QJsonArray fft_json144;
    QJsonArray fft_json145;
    QJsonArray fft_json146;
    QJsonArray fft_json147;
    QJsonArray fft_json148;
    QJsonArray fft_json149;
    QJsonArray fft_json150;

    for(int i = 0; i < N2; i++) fft_json1.push_back(m_fft->FFTData_1[i]);
    for(int i = 0; i < N2; i++) fft_json2.push_back(m_fft->FFTData_2[i]);
    for(int i = 0; i < N2; i++) fft_json3.push_back(m_fft->FFTData_3[i]);
    for(int i = 0; i < N2; i++) fft_json4.push_back(m_fft->FFTData_4[i]);
    for(int i = 0; i < N2; i++) fft_json5.push_back(m_fft->FFTData_5[i]);
    for(int i = 0; i < N2; i++) fft_json6.push_back(m_fft->FFTData_6[i]);
    for(int i = 0; i < N2; i++) fft_json7.push_back(m_fft->FFTData_7[i]);
    for(int i = 0; i < N2; i++) fft_json8.push_back(m_fft->FFTData_8[i]);
    for(int i = 0; i < N2; i++) fft_json9.push_back(m_fft->FFTData_9[i]);
    for(int i = 0; i < N2; i++) fft_json10.push_back(m_fft->FFTData_10[i]);
    for(int i = 0; i < N2; i++) fft_json11.push_back(m_fft->FFTData_11[i]);
    for(int i = 0; i < N2; i++) fft_json12.push_back(m_fft->FFTData_12[i]);
    for(int i = 0; i < N2; i++) fft_json13.push_back(m_fft->FFTData_13[i]);
    for(int i = 0; i < N2; i++) fft_json14.push_back(m_fft->FFTData_14[i]);
    for(int i = 0; i < N2; i++) fft_json15.push_back(m_fft->FFTData_15[i]);
    for(int i = 0; i < N2; i++) fft_json16.push_back(m_fft->FFTData_16[i]);
    for(int i = 0; i < N2; i++) fft_json17.push_back(m_fft->FFTData_17[i]);
    for(int i = 0; i < N2; i++) fft_json18.push_back(m_fft->FFTData_18[i]);
    for(int i = 0; i < N2; i++) fft_json19.push_back(m_fft->FFTData_19[i]);
    for(int i = 0; i < N2; i++) fft_json20.push_back(m_fft->FFTData_20[i]);
    for(int i = 0; i < N2; i++) fft_json21.push_back(m_fft->FFTData_21[i]);
    for(int i = 0; i < N2; i++) fft_json22.push_back(m_fft->FFTData_22[i]);
    for(int i = 0; i < N2; i++) fft_json23.push_back(m_fft->FFTData_23[i]);
    for(int i = 0; i < N2; i++) fft_json24.push_back(m_fft->FFTData_24[i]);
    for(int i = 0; i < N2; i++) fft_json25.push_back(m_fft->FFTData_25[i]);
    for(int i = 0; i < N2; i++) fft_json26.push_back(m_fft->FFTData_26[i]);
    for(int i = 0; i < N2; i++) fft_json27.push_back(m_fft->FFTData_27[i]);
    for(int i = 0; i < N2; i++) fft_json28.push_back(m_fft->FFTData_28[i]);
    for(int i = 0; i < N2; i++) fft_json29.push_back(m_fft->FFTData_29[i]);
    for(int i = 0; i < N2; i++) fft_json30.push_back(m_fft->FFTData_30[i]);
    for(int i = 0; i < N2; i++) fft_json31.push_back(m_fft->FFTData_31[i]);
    for(int i = 0; i < N2; i++) fft_json32.push_back(m_fft->FFTData_32[i]);
    for(int i = 0; i < N2; i++) fft_json33.push_back(m_fft->FFTData_33[i]);
    for(int i = 0; i < N2; i++) fft_json34.push_back(m_fft->FFTData_34[i]);
    for(int i = 0; i < N2; i++) fft_json35.push_back(m_fft->FFTData_35[i]);
    for(int i = 0; i < N2; i++) fft_json36.push_back(m_fft->FFTData_36[i]);
    for(int i = 0; i < N2; i++) fft_json37.push_back(m_fft->FFTData_37[i]);
    for(int i = 0; i < N2; i++) fft_json38.push_back(m_fft->FFTData_38[i]);
    for(int i = 0; i < N2; i++) fft_json39.push_back(m_fft->FFTData_39[i]);
    for(int i = 0; i < N2; i++) fft_json40.push_back(m_fft->FFTData_40[i]);
    for(int i = 0; i < N2; i++) fft_json41.push_back(m_fft->FFTData_41[i]);
    for(int i = 0; i < N2; i++) fft_json42.push_back(m_fft->FFTData_42[i]);
    for(int i = 0; i < N2; i++) fft_json43.push_back(m_fft->FFTData_43[i]);
    for(int i = 0; i < N2; i++) fft_json44.push_back(m_fft->FFTData_44[i]);
    for(int i = 0; i < N2; i++) fft_json45.push_back(m_fft->FFTData_45[i]);
    for(int i = 0; i < N2; i++) fft_json46.push_back(m_fft->FFTData_46[i]);
    for(int i = 0; i < N2; i++) fft_json47.push_back(m_fft->FFTData_47[i]);
    for(int i = 0; i < N2; i++) fft_json48.push_back(m_fft->FFTData_48[i]);
    for(int i = 0; i < N2; i++) fft_json49.push_back(m_fft->FFTData_49[i]);
    for(int i = 0; i < N2; i++) fft_json50.push_back(m_fft->FFTData_50[i]);
    for(int i = 0; i < N2; i++) fft_json51.push_back(m_fft->FFTData_51[i]);
    for(int i = 0; i < N2; i++) fft_json52.push_back(m_fft->FFTData_52[i]);
    for(int i = 0; i < N2; i++) fft_json53.push_back(m_fft->FFTData_53[i]);
    for(int i = 0; i < N2; i++) fft_json54.push_back(m_fft->FFTData_54[i]);
    for(int i = 0; i < N2; i++) fft_json55.push_back(m_fft->FFTData_55[i]);
    for(int i = 0; i < N2; i++) fft_json56.push_back(m_fft->FFTData_56[i]);
    for(int i = 0; i < N2; i++) fft_json57.push_back(m_fft->FFTData_57[i]);
    for(int i = 0; i < N2; i++) fft_json58.push_back(m_fft->FFTData_58[i]);
    for(int i = 0; i < N2; i++) fft_json59.push_back(m_fft->FFTData_59[i]);
    for(int i = 0; i < N2; i++) fft_json60.push_back(m_fft->FFTData_60[i]);
    for(int i = 0; i < N2; i++) fft_json61.push_back(m_fft->FFTData_61[i]);
    for(int i = 0; i < N2; i++) fft_json62.push_back(m_fft->FFTData_62[i]);
    for(int i = 0; i < N2; i++) fft_json63.push_back(m_fft->FFTData_63[i]);
    for(int i = 0; i < N2; i++) fft_json64.push_back(m_fft->FFTData_64[i]);
    for(int i = 0; i < N2; i++) fft_json65.push_back(m_fft->FFTData_65[i]);
    for(int i = 0; i < N2; i++) fft_json66.push_back(m_fft->FFTData_66[i]);
    for(int i = 0; i < N2; i++) fft_json67.push_back(m_fft->FFTData_67[i]);
    for(int i = 0; i < N2; i++) fft_json68.push_back(m_fft->FFTData_68[i]);
    for(int i = 0; i < N2; i++) fft_json69.push_back(m_fft->FFTData_69[i]);
    for(int i = 0; i < N2; i++) fft_json70.push_back(m_fft->FFTData_70[i]);
    for(int i = 0; i < N2; i++) fft_json71.push_back(m_fft->FFTData_71[i]);
    for(int i = 0; i < N2; i++) fft_json72.push_back(m_fft->FFTData_72[i]);
    for(int i = 0; i < N2; i++) fft_json73.push_back(m_fft->FFTData_73[i]);
    for(int i = 0; i < N2; i++) fft_json74.push_back(m_fft->FFTData_74[i]);
    for(int i = 0; i < N2; i++) fft_json75.push_back(m_fft->FFTData_75[i]);
    for(int i = 0; i < N2; i++) fft_json76.push_back(m_fft->FFTData_76[i]);
    for(int i = 0; i < N2; i++) fft_json77.push_back(m_fft->FFTData_77[i]);
    for(int i = 0; i < N2; i++) fft_json78.push_back(m_fft->FFTData_78[i]);
    for(int i = 0; i < N2; i++) fft_json79.push_back(m_fft->FFTData_79[i]);
    for(int i = 0; i < N2; i++) fft_json80.push_back(m_fft->FFTData_80[i]);
    for(int i = 0; i < N2; i++) fft_json81.push_back(m_fft->FFTData_81[i]);
    for(int i = 0; i < N2; i++) fft_json82.push_back(m_fft->FFTData_82[i]);
    for(int i = 0; i < N2; i++) fft_json83.push_back(m_fft->FFTData_83[i]);
    for(int i = 0; i < N2; i++) fft_json84.push_back(m_fft->FFTData_84[i]);
    for(int i = 0; i < N2; i++) fft_json85.push_back(m_fft->FFTData_85[i]);
    for(int i = 0; i < N2; i++) fft_json86.push_back(m_fft->FFTData_86[i]);
    for(int i = 0; i < N2; i++) fft_json87.push_back(m_fft->FFTData_87[i]);
    for(int i = 0; i < N2; i++) fft_json88.push_back(m_fft->FFTData_88[i]);
    for(int i = 0; i < N2; i++) fft_json89.push_back(m_fft->FFTData_89[i]);
    for(int i = 0; i < N2; i++) fft_json90.push_back(m_fft->FFTData_90[i]);
    for(int i = 0; i < N2; i++) fft_json91.push_back(m_fft->FFTData_91[i]);
    for(int i = 0; i < N2; i++) fft_json92.push_back(m_fft->FFTData_92[i]);
    for(int i = 0; i < N2; i++) fft_json93.push_back(m_fft->FFTData_93[i]);
    for(int i = 0; i < N2; i++) fft_json94.push_back(m_fft->FFTData_94[i]);
    for(int i = 0; i < N2; i++) fft_json95.push_back(m_fft->FFTData_95[i]);
    for(int i = 0; i < N2; i++) fft_json96.push_back(m_fft->FFTData_96[i]);
    for(int i = 0; i < N2; i++) fft_json97.push_back(m_fft->FFTData_97[i]);
    for(int i = 0; i < N2; i++) fft_json98.push_back(m_fft->FFTData_98[i]);
    for(int i = 0; i < N2; i++) fft_json99.push_back(m_fft->FFTData_99[i]);
    for(int i = 0; i < N2; i++) fft_json100.push_back(m_fft->FFTData_100[i]);
    for(int i = 0; i < N2; i++) fft_json101.push_back(m_fft->FFTData_101[i]);
    for(int i = 0; i < N2; i++) fft_json102.push_back(m_fft->FFTData_102[i]);
    for(int i = 0; i < N2; i++) fft_json103.push_back(m_fft->FFTData_103[i]);
    for(int i = 0; i < N2; i++) fft_json104.push_back(m_fft->FFTData_104[i]);
    for(int i = 0; i < N2; i++) fft_json105.push_back(m_fft->FFTData_105[i]);
    for(int i = 0; i < N2; i++) fft_json106.push_back(m_fft->FFTData_106[i]);
    for(int i = 0; i < N2; i++) fft_json107.push_back(m_fft->FFTData_107[i]);
    for(int i = 0; i < N2; i++) fft_json108.push_back(m_fft->FFTData_108[i]);
    for(int i = 0; i < N2; i++) fft_json109.push_back(m_fft->FFTData_109[i]);
    for(int i = 0; i < N2; i++) fft_json110.push_back(m_fft->FFTData_110[i]);
    for(int i = 0; i < N2; i++) fft_json111.push_back(m_fft->FFTData_111[i]);
    for(int i = 0; i < N2; i++) fft_json112.push_back(m_fft->FFTData_112[i]);
    for(int i = 0; i < N2; i++) fft_json113.push_back(m_fft->FFTData_113[i]);
    for(int i = 0; i < N2; i++) fft_json114.push_back(m_fft->FFTData_114[i]);
    for(int i = 0; i < N2; i++) fft_json115.push_back(m_fft->FFTData_115[i]);
    for(int i = 0; i < N2; i++) fft_json116.push_back(m_fft->FFTData_116[i]);
    for(int i = 0; i < N2; i++) fft_json117.push_back(m_fft->FFTData_117[i]);
    for(int i = 0; i < N2; i++) fft_json118.push_back(m_fft->FFTData_118[i]);
    for(int i = 0; i < N2; i++) fft_json119.push_back(m_fft->FFTData_119[i]);
    for(int i = 0; i < N2; i++) fft_json120.push_back(m_fft->FFTData_120[i]);
    for(int i = 0; i < N2; i++) fft_json121.push_back(m_fft->FFTData_121[i]);
    for(int i = 0; i < N2; i++) fft_json122.push_back(m_fft->FFTData_122[i]);
    for(int i = 0; i < N2; i++) fft_json123.push_back(m_fft->FFTData_123[i]);
    for(int i = 0; i < N2; i++) fft_json124.push_back(m_fft->FFTData_124[i]);
    for(int i = 0; i < N2; i++) fft_json125.push_back(m_fft->FFTData_125[i]);
    for(int i = 0; i < N2; i++) fft_json126.push_back(m_fft->FFTData_126[i]);
    for(int i = 0; i < N2; i++) fft_json127.push_back(m_fft->FFTData_127[i]);
    for(int i = 0; i < N2; i++) fft_json128.push_back(m_fft->FFTData_128[i]);
    for(int i = 0; i < N2; i++) fft_json129.push_back(m_fft->FFTData_129[i]);
    for(int i = 0; i < N2; i++) fft_json130.push_back(m_fft->FFTData_130[i]);
    for(int i = 0; i < N2; i++) fft_json131.push_back(m_fft->FFTData_131[i]);
    for(int i = 0; i < N2; i++) fft_json132.push_back(m_fft->FFTData_132[i]);
    for(int i = 0; i < N2; i++) fft_json133.push_back(m_fft->FFTData_133[i]);
    for(int i = 0; i < N2; i++) fft_json134.push_back(m_fft->FFTData_134[i]);
    for(int i = 0; i < N2; i++) fft_json135.push_back(m_fft->FFTData_135[i]);
    for(int i = 0; i < N2; i++) fft_json136.push_back(m_fft->FFTData_136[i]);
    for(int i = 0; i < N2; i++) fft_json137.push_back(m_fft->FFTData_137[i]);
    for(int i = 0; i < N2; i++) fft_json138.push_back(m_fft->FFTData_138[i]);
    for(int i = 0; i < N2; i++) fft_json139.push_back(m_fft->FFTData_139[i]);
    for(int i = 0; i < N2; i++) fft_json140.push_back(m_fft->FFTData_140[i]);
    for(int i = 0; i < N2; i++) fft_json141.push_back(m_fft->FFTData_141[i]);
    for(int i = 0; i < N2; i++) fft_json142.push_back(m_fft->FFTData_142[i]);
    for(int i = 0; i < N2; i++) fft_json143.push_back(m_fft->FFTData_143[i]);
    for(int i = 0; i < N2; i++) fft_json144.push_back(m_fft->FFTData_144[i]);
    for(int i = 0; i < N2; i++) fft_json145.push_back(m_fft->FFTData_145[i]);
    for(int i = 0; i < N2; i++) fft_json146.push_back(m_fft->FFTData_146[i]);
    for(int i = 0; i < N2; i++) fft_json147.push_back(m_fft->FFTData_147[i]);
    for(int i = 0; i < N2; i++) fft_json148.push_back(m_fft->FFTData_148[i]);
    for(int i = 0; i < N2; i++) fft_json149.push_back(m_fft->FFTData_149[i]);
    for(int i = 0; i < N2; i++) fft_json150.push_back(m_fft->FFTData_150[i]);

    fft_obj.insert("fft_data_1",fft_json1);
    fft_obj.insert("fft_data_2",fft_json2);
    fft_obj.insert("fft_data_3",fft_json3);
    fft_obj.insert("fft_data_4",fft_json4);
    fft_obj.insert("fft_data_5",fft_json5);
    fft_obj.insert("fft_data_6",fft_json6);
    fft_obj.insert("fft_data_7",fft_json7);
    fft_obj.insert("fft_data_8",fft_json8);
    fft_obj.insert("fft_data_9",fft_json9);
    fft_obj.insert("fft_data_10",fft_json10);
    fft_obj.insert("fft_data_11",fft_json11);
    fft_obj.insert("fft_data_12",fft_json12);
    fft_obj.insert("fft_data_13",fft_json13);
    fft_obj.insert("fft_data_14",fft_json14);
    fft_obj.insert("fft_data_15",fft_json15);
    fft_obj.insert("fft_data_16",fft_json16);
    fft_obj.insert("fft_data_17",fft_json17);
    fft_obj.insert("fft_data_18",fft_json18);
    fft_obj.insert("fft_data_19",fft_json19);
    fft_obj.insert("fft_data_20",fft_json20);
    fft_obj.insert("fft_data_21",fft_json21);
    fft_obj.insert("fft_data_22",fft_json22);
    fft_obj.insert("fft_data_23",fft_json23);
    fft_obj.insert("fft_data_24",fft_json24);
    fft_obj.insert("fft_data_25",fft_json25);
    fft_obj.insert("fft_data_26",fft_json26);
    fft_obj.insert("fft_data_27",fft_json27);
    fft_obj.insert("fft_data_28",fft_json28);
    fft_obj.insert("fft_data_29",fft_json29);
    fft_obj.insert("fft_data_30",fft_json30);
    fft_obj.insert("fft_data_31",fft_json31);
    fft_obj.insert("fft_data_32",fft_json32);
    fft_obj.insert("fft_data_33",fft_json33);
    fft_obj.insert("fft_data_34",fft_json34);
    fft_obj.insert("fft_data_35",fft_json35);
    fft_obj.insert("fft_data_36",fft_json36);
    fft_obj.insert("fft_data_37",fft_json37);
    fft_obj.insert("fft_data_38",fft_json38);
    fft_obj.insert("fft_data_39",fft_json39);
    fft_obj.insert("fft_data_40",fft_json40);
    fft_obj.insert("fft_data_41",fft_json41);
    fft_obj.insert("fft_data_42",fft_json42);
    fft_obj.insert("fft_data_43",fft_json43);
    fft_obj.insert("fft_data_44",fft_json44);
    fft_obj.insert("fft_data_45",fft_json45);
    fft_obj.insert("fft_data_46",fft_json46);
    fft_obj.insert("fft_data_47",fft_json47);
    fft_obj.insert("fft_data_48",fft_json48);
    fft_obj.insert("fft_data_49",fft_json49);
    fft_obj.insert("fft_data_50",fft_json50);
    fft_obj.insert("fft_data_51",fft_json51);
    fft_obj.insert("fft_data_52",fft_json52);
    fft_obj.insert("fft_data_53",fft_json53);
    fft_obj.insert("fft_data_54",fft_json54);
    fft_obj.insert("fft_data_55",fft_json55);
    fft_obj.insert("fft_data_56",fft_json56);
    fft_obj.insert("fft_data_57",fft_json57);
    fft_obj.insert("fft_data_58",fft_json58);
    fft_obj.insert("fft_data_59",fft_json59);
    fft_obj.insert("fft_data_60",fft_json60);
    fft_obj.insert("fft_data_61",fft_json61);
    fft_obj.insert("fft_data_62",fft_json62);
    fft_obj.insert("fft_data_63",fft_json63);
    fft_obj.insert("fft_data_64",fft_json64);
    fft_obj.insert("fft_data_65",fft_json65);
    fft_obj.insert("fft_data_66",fft_json66);
    fft_obj.insert("fft_data_67",fft_json67);
    fft_obj.insert("fft_data_68",fft_json68);
    fft_obj.insert("fft_data_69",fft_json69);
    fft_obj.insert("fft_data_70",fft_json70);
    fft_obj.insert("fft_data_71",fft_json71);
    fft_obj.insert("fft_data_72",fft_json72);
    fft_obj.insert("fft_data_73",fft_json73);
    fft_obj.insert("fft_data_74",fft_json74);
    fft_obj.insert("fft_data_75",fft_json75);
    fft_obj.insert("fft_data_76",fft_json76);
    fft_obj.insert("fft_data_77",fft_json77);
    fft_obj.insert("fft_data_78",fft_json78);
    fft_obj.insert("fft_data_79",fft_json79);
    fft_obj.insert("fft_data_80",fft_json80);
    fft_obj.insert("fft_data_81",fft_json81);
    fft_obj.insert("fft_data_82",fft_json82);
    fft_obj.insert("fft_data_83",fft_json83);
    fft_obj.insert("fft_data_84",fft_json84);
    fft_obj.insert("fft_data_85",fft_json85);
    fft_obj.insert("fft_data_86",fft_json86);
    fft_obj.insert("fft_data_87",fft_json87);
    fft_obj.insert("fft_data_88",fft_json88);
    fft_obj.insert("fft_data_89",fft_json89);
    fft_obj.insert("fft_data_90",fft_json90);
    fft_obj.insert("fft_data_91",fft_json91);
    fft_obj.insert("fft_data_92",fft_json92);
    fft_obj.insert("fft_data_93",fft_json93);
    fft_obj.insert("fft_data_94",fft_json94);
    fft_obj.insert("fft_data_95",fft_json95);
    fft_obj.insert("fft_data_96",fft_json96);
    fft_obj.insert("fft_data_97",fft_json97);
    fft_obj.insert("fft_data_98",fft_json98);
    fft_obj.insert("fft_data_99",fft_json99);
    fft_obj.insert("fft_data_100",fft_json100);
    fft_obj.insert("fft_data_101",fft_json101);
    fft_obj.insert("fft_data_102",fft_json102);
    fft_obj.insert("fft_data_103",fft_json103);
    fft_obj.insert("fft_data_104",fft_json104);
    fft_obj.insert("fft_data_105",fft_json105);
    fft_obj.insert("fft_data_106",fft_json106);
    fft_obj.insert("fft_data_107",fft_json107);
    fft_obj.insert("fft_data_108",fft_json108);
    fft_obj.insert("fft_data_109",fft_json109);
    fft_obj.insert("fft_data_110",fft_json110);
    fft_obj.insert("fft_data_111",fft_json111);
    fft_obj.insert("fft_data_112",fft_json112);
    fft_obj.insert("fft_data_113",fft_json113);
    fft_obj.insert("fft_data_114",fft_json114);
    fft_obj.insert("fft_data_115",fft_json115);
    fft_obj.insert("fft_data_116",fft_json116);
    fft_obj.insert("fft_data_117",fft_json117);
    fft_obj.insert("fft_data_118",fft_json118);
    fft_obj.insert("fft_data_119",fft_json119);
    fft_obj.insert("fft_data_120",fft_json120);
    fft_obj.insert("fft_data_121",fft_json121);
    fft_obj.insert("fft_data_122",fft_json122);
    fft_obj.insert("fft_data_123",fft_json123);
    fft_obj.insert("fft_data_124",fft_json124);
    fft_obj.insert("fft_data_125",fft_json125);
    fft_obj.insert("fft_data_126",fft_json126);
    fft_obj.insert("fft_data_127",fft_json127);
    fft_obj.insert("fft_data_128",fft_json128);
    fft_obj.insert("fft_data_129",fft_json129);
    fft_obj.insert("fft_data_130",fft_json130);
    fft_obj.insert("fft_data_131",fft_json131);
    fft_obj.insert("fft_data_132",fft_json132);
    fft_obj.insert("fft_data_133",fft_json133);
    fft_obj.insert("fft_data_134",fft_json134);
    fft_obj.insert("fft_data_135",fft_json135);
    fft_obj.insert("fft_data_136",fft_json136);
    fft_obj.insert("fft_data_137",fft_json137);
    fft_obj.insert("fft_data_138",fft_json138);
    fft_obj.insert("fft_data_139",fft_json139);
    fft_obj.insert("fft_data_140",fft_json140);
    fft_obj.insert("fft_data_141",fft_json141);
    fft_obj.insert("fft_data_142",fft_json142);
    fft_obj.insert("fft_data_143",fft_json143);
    fft_obj.insert("fft_data_144",fft_json144);
    fft_obj.insert("fft_data_145",fft_json145);
    fft_obj.insert("fft_data_146",fft_json146);
    fft_obj.insert("fft_data_147",fft_json147);
    fft_obj.insert("fft_data_148",fft_json148);
    fft_obj.insert("fft_data_149",fft_json149);
    fft_obj.insert("fft_data_150",fft_json150);

    QString fft_str = QJsonDocument(fft_obj).toJson();
//    QString fft_js = QString("fft_flash(%1)").arg(fft_str);
    QString fft_js = QString("fft_heatmap_flash(%1)").arg(fft_str);
    m_demowave_widget->page()->runJavaScript(fft_js);

}

void demowave_widget2::on_comboBox_region_currentIndexChangedSlot(int _regionIndex)
{
    RegionIndex = _regionIndex;
    qDebug()<<"RegionIndex = "<<RegionIndex<<endl;
}


