#include "demowave_widget.h"
#include "ui_demowave_widget.h"

demowave_widget::demowave_widget(Demodulation *demodulation) :
    ui(new Ui::demowave_widget)
{
    ui->setupUi(this);
    demodu = demodulation;

    initWidget();

    readConfigFile();

    initComboBox_Region();

//    Demodata_1 = new float[REGION_DATA_LENGTH]();
//    Demodata_2 = new float[REGION_DATA_LENGTH]();
//    Demodata_3 = new float[REGION_DATA_LENGTH]();
//    Demodata_4 = new float[REGION_DATA_LENGTH]();
//    Demodata_5 = new float[REGION_DATA_LENGTH]();
//    Demodata_6 = new float[REGION_DATA_LENGTH]();
//    Demodata_7 = new float[REGION_DATA_LENGTH]();
//    Demodata_8 = new float[REGION_DATA_LENGTH]();
//    Demodata_9 = new float[REGION_DATA_LENGTH]();

    DemodataArray = new float*[peakNum]; //动态创建二维数组
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
}

demowave_widget::~demowave_widget()
{
    delete ui;
}

void demowave_widget::initWidget()
{
    setWindowTitle(QString("Demodulation Wave Display"));

    // 创建横纵坐标轴并设置显示范围
    m_axisX = new QValueAxis();
    m_axisY = new QValueAxis();
    m_axisX->setTitleText("Time Series");
    m_axisY->setTitleText("Phase (rad)");
    m_axisX->setMin(0);
//    m_axisY->setMin(-AXIS_MAX_Y);
    m_axisX->setMax(AXIS_MAX_X);
//    m_axisY->setMax(AXIS_MAX_Y);
    m_axisY->setTickCount(10);
    m_axisX->setTickCount(10);

    m_lineSeries = new QSplineSeries();                             // 创建曲线绘制对象
    m_lineSeries->setPointsVisible(true);                         // 设置数据点可见
    m_lineSeries->setName("Demodulation Wave Plot");                            // 图例名称
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

void demowave_widget::readConfigFile()
{
    QString filePath = QString("C:/Qt_UDP_DAS/peak.txt");
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the Configration file!"<<endl;
    }
   QByteArray configData = file.readAll(); //读取所有数据
   char peakNumChar = configData[3]; //peakNum存放在第四个位置
   bool ok;
   peakNum =  QString(peakNumChar).toInt(&ok,16);
}

void demowave_widget::initComboBox_Region()
{
    ui->comboBox_Region->clear();

    for(int i=1; i<= peakNum; i++ )
        ui->comboBox_Region->addItem(QString::asprintf("Region %d",i));
}

//HEX发送时刷新波形显示
void demowave_widget::FlashWave()
{
    qDebug() <<"Flash Demodulation Wave Slot responsed !"<<endl;

    m_lineSeries->clear();

    int regionNum = peakNum;

    int sizeoDemoData = demodu->DEMOdata_flash->size();

    //重设sizeoDemoData的长度，使其为regionNum的倍数
    int N1 = sizeoDemoData/regionNum;
    sizeoDemoData = N1*peakNum;

    //DEMOdata[] split regions
    for(int k = 0; k<sizeoDemoData; k+=regionNum){
        int p = k/regionNum;
        for(int q=0; q<regionNum;q++){
            if(demodu->DEMOdata_flash->isEmpty()) QThread::msleep(50);
            DemodataArray[q][p] = demodu->DEMOdata_flash->pop();
        }
    }

    //region select
    RegionIndex = ui->comboBox_Region->currentIndex();

    //dispaly wave
    for(int i = 0;i<DISPLAY_LENGTH_DEMO; i++){
        m_lineSeries->append(QPointF(i,DemodataArray[RegionIndex][i]));
        m_axisY->setRange(DemodataArray[RegionIndex][i]-15,DemodataArray[RegionIndex][i]+15);
    }

}

void demowave_widget::on_pushButton_reset_clicked()
{
    m_axisX->setMin(0);
    m_axisY->setMin(-AXIS_MAX_Y);
    m_axisX->setMax(AXIS_MAX_X);
    m_axisY->setMax(AXIS_MAX_Y);

}

