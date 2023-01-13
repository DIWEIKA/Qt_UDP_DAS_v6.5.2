#include "pulsewave_widget2.h"
#include "ui_pulsewave_widget2.h"

pulsewave_widget2::pulsewave_widget2(UDP_Recv *udp_Recv):
    ui( new Ui::pulsewave_widget2),
    udp_recv(udp_Recv)
{
    this->setAttribute(Qt::WA_DeleteOnClose);

    ui->setupUi(this);

    PulsedataHEX = new char[READ_PULSE_LENGTH*2];

    setHtmlPages();

    connect(webobj2,&WebClass::send_pulsewave_widget_btn_pulsewave_pause,this,&pulsewave_widget2::PulseWave_pause_slot);
    connect(webobj2,&WebClass::send_pulsewave_widget_btn_pulsewave_restart,this,&pulsewave_widget2::PulseWave_restart_slot);
}

pulsewave_widget2::~pulsewave_widget2()
{
    delete ui;
    FreeMemory();
}

void pulsewave_widget2::setHtmlPages()
{
    setWindowTitle(QString("Pulse Wave Display"));

    m_pulsewave_widget = ui->pulsewave_widget;
    m_pulsewave_widget->setContextMenuPolicy(Qt::NoContextMenu);
    m_pulsewave_widget->load(QUrl::fromLocalFile(QString("C:/Qt_UDP_DAS/PAGE/tpl03/PulseWaveDisplay.html")));

    webChannel2 = new QWebChannel;

    webobj2 = new WebClass();

    webChannel2->registerObject("webobj2", webobj2);

    m_pulsewave_widget->page()->setWebChannel(webChannel2);
}

void pulsewave_widget2::FlashWave()
{
    qDebug() <<"Flash Pulse Wave Slot responsed !"<<endl;

    sizeoPulsedata = READ_PULSE_LENGTH*2;

    //1. pack_HEX_Display >> PulsedataHEX[]
    memcpy(PulsedataHEX,udp_recv->pack_HEX_Display,sizeof(char)*sizeoPulsedata);

    //2. PulsedataHEX[] >> Pulsedata_DEC_all[]
    for(int i = 0; i<sizeoPulsedata; i+=4){
        bool ok;
        int number_DEC = QString(PulsedataHEX[i]).toInt(&ok,16)*0 + QString(PulsedataHEX[i+1]).toInt(&ok,16)*256 + QString(PulsedataHEX[i+2]).toInt(&ok,16)*16 +QString(PulsedataHEX[i+3]).toInt(&ok,16)*1;
        if(number_DEC>2047)
            number_DEC = number_DEC-4096;
        int j = i/4;
        Pulsedata_DEC_all_HEX[j] = number_DEC;
    }

    sizeoPulsedataDec = sizeoPulsedata/4;

    //3. Pulsedata_DEC_all[] split into 4 channels
    for(int k = 0; k<sizeoPulsedataDec; k+=4){
        int p = k/4;
        Pulsedata_DEC_1_HEX[p] = Pulsedata_DEC_all_HEX[k];
        Pulsedata_DEC_2_HEX[p] = Pulsedata_DEC_all_HEX[k+1];
        Pulsedata_DEC_3_HEX[p] = Pulsedata_DEC_all_HEX[k+2];
        Pulsedata_DEC_4_HEX[p] = Pulsedata_DEC_all_HEX[k+3];
    }

    sizeoDisplaydata = sizeoPulsedataDec/4;

    //5.Wave Display
    QJsonObject pulse_wave_obj1,pulse_wave_obj2,pulse_wave_obj3,pulse_wave_obj4;
    QJsonArray pulse_wave_json1,pulse_wave_json2,pulse_wave_json3,pulse_wave_json4;

    for(int i=0; i<sizeoDisplaydata-1; ++i) {
        pulse_wave_json1.push_back(Pulsedata_DEC_1_HEX[i]);
        pulse_wave_json2.push_back(Pulsedata_DEC_2_HEX[i]);
        pulse_wave_json3.push_back(Pulsedata_DEC_3_HEX[i]);
        pulse_wave_json4.push_back(Pulsedata_DEC_4_HEX[i]);
    }
    pulse_wave_obj1.insert("pulse_wave_1", pulse_wave_json1);
    pulse_wave_obj2.insert("pulse_wave_2", pulse_wave_json2);
    pulse_wave_obj3.insert("pulse_wave_3", pulse_wave_json3);
    pulse_wave_obj4.insert("pulse_wave_4", pulse_wave_json4);

    QString pulse_wave_str1 = QJsonDocument(pulse_wave_obj1).toJson();
    QString pulse_wave_str2 = QJsonDocument(pulse_wave_obj2).toJson();
    QString pulse_wave_str3 = QJsonDocument(pulse_wave_obj3).toJson();
    QString pulse_wave_str4 = QJsonDocument(pulse_wave_obj4).toJson();

    QString pulse_wave_js1 = QString("pulsewave_flash1(%1)").arg(pulse_wave_str1);
    QString pulse_wave_js2 = QString("pulsewave_flash2(%1)").arg(pulse_wave_str2);
    QString pulse_wave_js3 = QString("pulsewave_flash3(%1)").arg(pulse_wave_str3);
    QString pulse_wave_js4 = QString("pulsewave_flash4(%1)").arg(pulse_wave_str4);

    m_pulsewave_widget->page()->runJavaScript(pulse_wave_js1);
    m_pulsewave_widget->page()->runJavaScript(pulse_wave_js2);
    m_pulsewave_widget->page()->runJavaScript(pulse_wave_js3);
    m_pulsewave_widget->page()->runJavaScript(pulse_wave_js4);


    //5. Wave Display /* (从8开始 因为起始帧开始部分包含了上一帧的8个点)*/
//    for(int i = 0;i<sizeoDisplaydata-1;i++){
//        QVector<double> x(1),y(1);
//        x[0] = i/*-8*/;
//        y[0]= Pulsedata_DEC_disp[i];
//        if(y[0]<-10) y[0]=0; //去掉下方的掉点问题
//        if(Pulsedata_DEC_disp[i]>0 && Pulsedata_DEC_disp[i-1]==0 && Pulsedata_DEC_disp[i+1]==0) y[0]=0; //去掉上方的掉点问题
//        m_customPlot->graph(0)->addData(x, y);
//    }

//    ui->customPlot->replot();
}

void pulsewave_widget2::FreeMemory()
{
    delete[] PulsedataHEX;
}

void pulsewave_widget2::PulseWave_pause_slot()
{
    emit send_mainwindow_btn_pause();
}

void pulsewave_widget2::PulseWave_restart_slot()
{
    emit send_mainwindow_btn_restart();
}






