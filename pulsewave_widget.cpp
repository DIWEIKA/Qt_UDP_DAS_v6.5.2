#include "pulsewave_widget.h"
#include "ui_pulsewave_widget.h"

pulsewave_widget::pulsewave_widget()
{
    ui = new Ui::pulsewave_widget;
    ui->setupUi(this);

    //初始化widget
    initWidget();

    ChannelIndex = 0;
}

pulsewave_widget::~pulsewave_widget()
{
    delete ui;
}

void pulsewave_widget::initWidget()
{
    setWindowTitle(QString("Pulse Wave Display"));

    // 创建横纵坐标轴并设置显示范围
    m_axisX = new QValueAxis();
    m_axisY = new QValueAxis();
    m_axisX->setTitleText("Time Series");
    m_axisY->setTitleText("Amplitude");
    m_axisX->setMin(0);
    m_axisY->setMin(-200);
    m_axisX->setMax(AXIS_MAX_X);
    m_axisY->setMax(AXIS_MAX_Y);
    m_axisY->setTickCount(15);
    m_axisX->setTickCount(10);

    m_lineSeries = new QSplineSeries();                             // 创建曲线绘制对象
    m_lineSeries->setPointsVisible(true);                         // 设置数据点可见
    m_lineSeries->setName("Pulse Wave Plot");                            // 图例名称
    m_lineSeries->setPen(QPen(Qt::blue,2,Qt::SolidLine));
    m_lineSeries->setUseOpenGL(true);                              //openGL加速
    m_lineSeries->clear();

    m_chart = new QChart();                                        // 创建图表对象
    m_chart->addAxis(m_axisY, Qt::AlignLeft);                      // 将X轴添加到图表上
    m_chart->addAxis(m_axisX, Qt::AlignBottom);                    // 将Y轴添加到图表上
    m_chart->addSeries(m_lineSeries);                              // 将曲线对象添加到图表上
    m_chart->setAnimationOptions(QChart::NoAnimation);        // 关掉动画：能使曲线绘制显示的更平滑，过渡效果更好看

    m_lineSeries->attachAxis(m_axisX);                             // 曲线对象关联上X轴，此步骤必须在m_chart->addSeries之后
    m_lineSeries->attachAxis(m_axisY);                             // 曲线对象关联上Y轴，此步骤必须在m_chart->addSeries之后

    ui->graphicsView->setChart(m_chart);                           // 将图表对象设置到graphicsView上进行显示
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);       // 设置渲染：抗锯齿，如果不设置那么曲线就显得不平滑
    ui->graphicsView->setRubberBand(QChartView::RectangleRubberBand);   //XY方向同时放大到鼠标画出的矩形大小

}

//HEX发送
void pulsewave_widget::FlashWave3(char datagramHEX[])
{
    qDebug() <<"Flash Pulse Wave Slot responsed !"<<endl;

    m_lineSeries->clear();

    sizeoPulsedata = READ_PULSE_LENGTH;

    //1. datagramHEX >> PulsedataHEX[]
    memcpy(PulsedataHEX,datagramHEX,sizeoPulsedata);

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

//    4. Channel select
    ChannelIndex = ui->comboBox_Channel->currentIndex();
    switch (ChannelIndex) {
    case 0:
        memcpy(Pulsedata_DEC_disp,Pulsedata_DEC_1_HEX,PULSEDATA_LENGTH*2);
        break;
    case 1:
        memcpy(Pulsedata_DEC_disp,Pulsedata_DEC_2_HEX,PULSEDATA_LENGTH*2);
        break;
    case 2:
        memcpy(Pulsedata_DEC_disp,Pulsedata_DEC_3_HEX,PULSEDATA_LENGTH*2);
        break;
    case 3:
        memcpy(Pulsedata_DEC_disp,Pulsedata_DEC_4_HEX,PULSEDATA_LENGTH*2);
        break;
    default:
        break;
    }

    //5. Wave Display (从8开始 因为起始帧开始部分包含了上一帧的8个点)
    for(int i = 8;i<DISPLAY_LENGTH_PULSE;i++)
        m_lineSeries->append(QPointF(i-8,Pulsedata_DEC_disp[i]));
}

void pulsewave_widget::on_btnReset_clicked()
{
    m_axisX->setMin(0);
    m_axisY->setMin(-200);
    m_axisX->setMax(AXIS_MAX_X);
    m_axisY->setMax(AXIS_MAX_Y);
}

////ASCII发送
//void wave_widget::FlashWave(char datagram[])
//{
//    qDebug() <<"Slot responsed !"<<endl;

//    m_lineSeries->clear();

//    //1. datagram[] >> CHdata[]
//    memcpy(CHdata,datagram,4096);

//    sizeoCHdata = 4096;

//    //2. CHdata >> CHdata_DEC_all[]
//    for(int i = 0; i<sizeoCHdata; i+=4){
//        bool ok;
//        int number_DEC = QString(CHdata[i]).toInt(&ok,16)*0 + QString(CHdata[i+1]).toInt(&ok,16)*256 + QString(CHdata[i+2]).toInt(&ok,16)*16 +QString(CHdata[i+3]).toInt(&ok,16)*1;
//        if(number_DEC>2047)
//            number_DEC = number_DEC-4096;
//        int j = i/4;
//        CHdata_DEC_all[j] = number_DEC;
//    }

//    sizeoCHdataDec = sizeoCHdata/4;

//    //3. CHdata_DEC_all[256] split into 4 channels
//    for(int k = 0; k<sizeoCHdataDec; k+=4){
//        int p = k/4;
//        CHdata_DEC_1[p] = CHdata_DEC_all[k];
//        CHdata_DEC_2[p] = CHdata_DEC_all[k+1];
//        CHdata_DEC_3[p] = CHdata_DEC_all[k+2];
//        CHdata_DEC_4[p] = CHdata_DEC_all[k+3];
//    }

//    //4. 显示波形
//    for(int i = 0;i<DISPLAY_LENGTH;i++)
//        m_lineSeries->append(QPointF(i,CHdata_DEC_1[i]));
//}

