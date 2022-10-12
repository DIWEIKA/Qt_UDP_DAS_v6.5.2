#include "pulsewave_widget2.h"
#include "ui_pulsewave_widget2.h"

pulsewave_widget2::pulsewave_widget2(UDP_Recv *udp_Recv):
    ui( new Ui::pulsewave_widget2),
    udp_recv(udp_Recv)
{
    ui->setupUi(this);

    PulsedataHEX = new char[READ_PULSE_LENGTH*2];

    initWidget();
}

pulsewave_widget2::~pulsewave_widget2()
{
    FreeMemory();
}

void pulsewave_widget2::initWidget()
{
    setWindowTitle(QString("Pulse Wave Display"));

    m_customPlot = ui->customPlot;

    //每条曲线都会独占一个graph()
    m_customPlot->addGraph();

    //设置画笔QPen
    QPen pen;
    pen.setWidth(4);//线宽
    pen.setStyle(Qt::PenStyle::SolidLine);//实线
    pen.setColor(Qt::blue); //颜色

    //给图层添加画笔
    m_customPlot->graph(0)->setPen(pen);
    m_customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色

    m_customPlot->xAxis->setRangeLower(0);
    m_customPlot->xAxis->setRangeUpper(2000);
    m_customPlot->yAxis->setRangeLower(-200);
    m_customPlot->yAxis->setRangeUpper(2048);

    // 边框右侧和上侧均显示刻度线，但不显示刻度值:
    // (参见 QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    m_customPlot->xAxis2->setVisible(true);
    m_customPlot->xAxis2->setTickLabels(false);
    m_customPlot->yAxis2->setVisible(true);
    m_customPlot->yAxis2->setTickLabels(false);
    // 使上下两个X轴的范围总是相等，使左右两个Y轴的范围总是相等
    //    connect(m_customPlot->xAxis, &QCPAxis::rangeChanged(QCPRange), m_customPlot->xAxis2, &QCPAxis::setRange(QCPRange));
    //    connect(m_customPlot->yAxis, &QCPAxis::rangeChanged(QCPRange), m_customPlot->yAxis2, &QCPAxis::setRange(QCPRange));


    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    //框选放大
    m_customPlot->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    m_customPlot->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    m_customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);

    //确定鼠标点击的精度
    ui->customPlot->setSelectionTolerance(1);

    //标记点信号槽
    connect(ui->customPlot,&QCustomPlot::mouseRelease, this, &pulsewave_widget2::slot_MouseRelease);

}

void pulsewave_widget2::FlashWave()
{
    qDebug() <<"Flash Pulse Wave Slot responsed !"<<endl;

    //clear history data
    m_customPlot->graph(0)->data()->clear();

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

    //4. Channel select
    ChannelIndex = ui->comboBox_Channel->currentIndex();
    switch (ChannelIndex) {
    case 0:
//        copy(begin(Pulsedata_DEC_1_HEX),end(Pulsedata_DEC_1_HEX),begin(Pulsedata_DEC_disp));
        memcpy(Pulsedata_DEC_disp,Pulsedata_DEC_1_HEX,sizeof(int)*sizeoDisplaydata);
        break;
    case 1:
//        copy(begin(Pulsedata_DEC_2_HEX),end(Pulsedata_DEC_2_HEX),begin(Pulsedata_DEC_disp));
        memcpy(Pulsedata_DEC_disp,Pulsedata_DEC_2_HEX,sizeof(int)*sizeoDisplaydata);
        break;
    case 2:
//        copy(begin(Pulsedata_DEC_3_HEX),end(Pulsedata_DEC_3_HEX),begin(Pulsedata_DEC_disp));
        memcpy(Pulsedata_DEC_disp,Pulsedata_DEC_3_HEX,sizeof(int)*sizeoDisplaydata);
        break;
    case 3:
//        copy(begin(Pulsedata_DEC_4_HEX),end(Pulsedata_DEC_4_HEX),begin(Pulsedata_DEC_disp));
        memcpy(Pulsedata_DEC_disp,Pulsedata_DEC_4_HEX,sizeof(int)*sizeoDisplaydata);
        break;
    default:
        break;
    }

    //5. Wave Display /* (从8开始 因为起始帧开始部分包含了上一帧的8个点)*/
    for(int i = 0;i<sizeoDisplaydata-1;i++){
        QVector<double> x(1),y(1);
        x[0] = i/*-8*/;
        y[0]= Pulsedata_DEC_disp[i];
        if(y[0]<-10) y[0]=0; //去掉下方的掉点问题
        if(Pulsedata_DEC_disp[i]>0 && Pulsedata_DEC_disp[i-1]==0 && Pulsedata_DEC_disp[i+1]==0) y[0]=0; //去掉上方的掉点问题
        m_customPlot->graph(0)->addData(x, y);
    }

    ui->customPlot->replot();
}

void pulsewave_widget2::FreeMemory()
{
    delete[] PulsedataHEX;
}

void pulsewave_widget2::on_btnReset_clicked()
{
    //自动调整XY轴的范围，以便显示出graph(0)中所有的点
    m_customPlot->graph(0)->rescaleAxes(true);

//    m_customPlot->xAxis->setRangeLower(0);
//    m_customPlot->xAxis->setRangeUpper(2000);
    m_customPlot->yAxis->setRangeLower(-10);
    m_customPlot->yAxis->setRangeUpper(2048);

    // 立即刷新图像
    ui->customPlot->replot();
}

void pulsewave_widget2::on_pushButton_pause_clicked()
{
    emit PauseWave();
}

void pulsewave_widget2::on_pushButton_restart_clicked()
{
    emit RestartWave();
}

//获取鼠标选中点的数值
void pulsewave_widget2::slot_MouseRelease(QMouseEvent *e)
{
    //排除非左鼠标键
        if (e->button() != Qt::LeftButton){ return; }

    //获取点击的点坐标
        QPointF ChickedPoint = e->pos();
    //排除区间外鼠标点
        if(!ui->customPlot->viewport().contains(e->pos())){return;}
    //将像素坐标转换为轴值
         double currentx = ui->customPlot->xAxis->pixelToCoord(ChickedPoint.x());
         double currenty = ui->customPlot->yAxis->pixelToCoord(ChickedPoint.y());
    //使用QToolTip输出值，
        QToolTip::showText(mapToGlobal(e->pos()),QString("x:%1, y:%2").arg(currentx).arg(currenty),this);


}

