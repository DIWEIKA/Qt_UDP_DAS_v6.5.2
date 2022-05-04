#include "wave_widget.h"
#include "ui_wave_widget.h"

wave_widget::wave_widget(shared_ptr<CirQueue<unsigned char>> CHdataX)
{
    ui = new Ui::wave_widget;
    ui->setupUi(this);

    CHdataQueue = make_shared<CirQueue<unsigned char>>(LenoUDP);

    CHdataQueue = CHdataX;

    //初始化widget
    initWidget();

}

wave_widget::~wave_widget()
{
    delete ui;
}

void wave_widget::initWidget()
{
    // 创建横纵坐标轴并设置显示范围
    m_axisX = new QValueAxis();
    m_axisY = new QValueAxis();
    m_axisX->setTitleText("X-label");
    m_axisY->setTitleText("Y-label");
    m_axisX->setMin(0);
    m_axisY->setMin(-AXIS_MAX_Y);
    m_axisX->setMax(AXIS_MAX_X);
    m_axisY->setMax(AXIS_MAX_Y);

    m_lineSeries = new QSplineSeries();                             // 创建曲线绘制对象
    m_lineSeries->setPointsVisible(true);                         // 设置数据点可见
    m_lineSeries->setName("Wave Plot");                            // 图例名称
    m_lineSeries->setPen(QPen(Qt::blue,2,Qt::SolidLine));
    m_lineSeries->setUseOpenGL(true);                              //openGL加速
    m_lineSeries->clear();

    m_chart = new QChart();                                        // 创建图表对象
    m_chart->addAxis(m_axisY, Qt::AlignLeft);                      // 将X轴添加到图表上
    m_chart->addAxis(m_axisX, Qt::AlignBottom);                    // 将Y轴添加到图表上
    m_chart->addSeries(m_lineSeries);                              // 将曲线对象添加到图表上
    m_chart->setAnimationOptions(QChart::SeriesAnimations);        // 动画：能使曲线绘制显示的更平滑，过渡效果更好看

    m_lineSeries->attachAxis(m_axisX);                             // 曲线对象关联上X轴，此步骤必须在m_chart->addSeries之后
    m_lineSeries->attachAxis(m_axisY);                             // 曲线对象关联上Y轴，此步骤必须在m_chart->addSeries之后

    ui->graphicsView->setChart(m_chart);                           // 将图表对象设置到graphicsView上进行显示
//    ui->graphicsView->setRenderHint(QPainter::Antialiasing);       // 设置渲染：抗锯齿，如果不设置那么曲线就显得不平滑
    ui->graphicsView->setRubberBand(QChartView::RectangleRubberBand);   //XY方向同时放大到鼠标画出的矩形大小
}

//读取本地波形文件
void wave_widget::ReadFromFiles()
{
    //1. 读取波形文件
    saveFolder =  QString("F:/Desktop/UDPConnect/data/");

    saveFilenameAll = saveFolder+QString("[All][31]")+QString("20220502140910")+ QString(".bin");

    infileAll.open(saveFilenameAll.toStdString().data(), ifstream::binary);

    if(!infileAll.is_open()) return;

    infileAll.read(CHdata,READ_LENGTH);

    //2. HEX to DEC >> CHdata_DEC_all[256]

    for(int i = 0; i<READ_LENGTH; i+=4){
        bool ok;
        int number_DEC = QString(CHdata[i]).toInt(&ok,16)*0 + QString(CHdata[i+1]).toInt(&ok,16)*256 + QString(CHdata[i+2]).toInt(&ok,16)*16 +QString(CHdata[i+3]).toInt(&ok,16)*1;
        if(number_DEC>2047)
            number_DEC = number_DEC-4096;
        int j = i/4;
        CHdata_DEC_all[j] = number_DEC;
    }

    //3. CHdata_DEC_all[256] split into 4 channels
    for(int k = 0; k<CHDATA_ALL_LENGTH; k+=4){
        int p = k/4;
        CHdata_DEC_1[p] = CHdata_DEC_all[k];
        CHdata_DEC_2[p] = CHdata_DEC_all[k+1];
        CHdata_DEC_3[p] = CHdata_DEC_all[k+2];
        CHdata_DEC_4[p] = CHdata_DEC_all[k+3];
    }
}

//读取CHdataQueue
void wave_widget::ReadFromQueue()
{
    //1. CHdataQueue >> CHdata
    sizeoCHdata = CHdataQueue->size();

    for( int j=0; j<sizeoCHdata; ++j){
        unsigned char usCHdata = *CHdataQueue->begin();
        CHdataQueue->pop();
        CHdata[j] = (char)usCHdata;
    }

    //2. CHdata >> CHdata_DEC_all[]
    for(int i = 0; i<sizeoCHdata; i+=4){
        bool ok;
        int number_DEC = QString(CHdata[i]).toInt(&ok,16)*0 + QString(CHdata[i+1]).toInt(&ok,16)*256 + QString(CHdata[i+2]).toInt(&ok,16)*16 +QString(CHdata[i+3]).toInt(&ok,16)*1;
        if(number_DEC>2047)
            number_DEC = number_DEC-4096;
        int j = i/4;
        CHdata_DEC_all[j] = number_DEC;
    }

    sizeoCHdataDec = sizeoCHdata/4;

    //3. CHdata_DEC_all[256] split into 4 channels
    for(int k = 0; k<sizeoCHdataDec; k+=4){
        int p = k/4;
        CHdata_DEC_1[p] = CHdata_DEC_all[k];
        CHdata_DEC_2[p] = CHdata_DEC_all[k+1];
        CHdata_DEC_3[p] = CHdata_DEC_all[k+2];
        CHdata_DEC_4[p] = CHdata_DEC_all[k+3];
    }
}

//ASCII发送
void wave_widget::FlashWave(char datagram[])
{
    qDebug() <<"Slot responsed !"<<endl;

    m_lineSeries->clear();

    //1. datagram[] >> CHdata[]
    memcpy(CHdata,datagram,4096);

    sizeoCHdata = 4096;

    //2. CHdata >> CHdata_DEC_all[]
    for(int i = 0; i<sizeoCHdata; i+=4){
        bool ok;
        int number_DEC = QString(CHdata[i]).toInt(&ok,16)*0 + QString(CHdata[i+1]).toInt(&ok,16)*256 + QString(CHdata[i+2]).toInt(&ok,16)*16 +QString(CHdata[i+3]).toInt(&ok,16)*1;
        if(number_DEC>2047)
            number_DEC = number_DEC-4096;
        int j = i/4;
        CHdata_DEC_all[j] = number_DEC;
    }

    sizeoCHdataDec = sizeoCHdata/4;

    //3. CHdata_DEC_all[256] split into 4 channels
    for(int k = 0; k<sizeoCHdataDec; k+=4){
        int p = k/4;
        CHdata_DEC_1[p] = CHdata_DEC_all[k];
        CHdata_DEC_2[p] = CHdata_DEC_all[k+1];
        CHdata_DEC_3[p] = CHdata_DEC_all[k+2];
        CHdata_DEC_4[p] = CHdata_DEC_all[k+3];
    }

    //4. 显示波形
    for(int i = 0;i<DISPLAY_LENGTH;i++)
        m_lineSeries->append(QPointF(i,CHdata_DEC_1[i+index]));
}

//HEX发送
void wave_widget::FlashWave2(char datagramHEX[])
{
    qDebug() <<"Slot responsed !"<<endl;

    m_lineSeries->clear();

    sizeoCHdata = 2048*32;

    //1. datagramHEX[] >> CHdataHEX[]
    memcpy(CHdataHEX,datagramHEX,sizeoCHdata);

    //2. CHdataHEX[] >> CHdata_DEC_all[]
    for(int i = 0; i<sizeoCHdata; i+=4){
        bool ok;
        int number_DEC = QString(CHdataHEX[i]).toInt(&ok,16)*0 + QString(CHdataHEX[i+1]).toInt(&ok,16)*256 + QString(CHdataHEX[i+2]).toInt(&ok,16)*16 +QString(CHdataHEX[i+3]).toInt(&ok,16)*1;
        if(number_DEC>2047)
            number_DEC = number_DEC-4096;
        int j = i/4;
        CHdata_DEC_all[j] = number_DEC;
    }

    sizeoCHdataDec = sizeoCHdata/4;

    //3. CHdata_DEC_all[256] split into 4 channels
    for(int k = 0; k<sizeoCHdataDec; k+=4){
        int p = k/4;
        CHdata_DEC_1[p] = CHdata_DEC_all[k];
        CHdata_DEC_2[p] = CHdata_DEC_all[k+1];
        CHdata_DEC_3[p] = CHdata_DEC_all[k+2];
        CHdata_DEC_4[p] = CHdata_DEC_all[k+3];
    }

    //4. 显示波形
    for(int i = 0;i<DISPLAY_LENGTH;i++)
        m_lineSeries->append(QPointF(i,CHdata_DEC_1[i+index]));
}


void wave_widget::on_btnReset_clicked()
{
    m_axisX->setMin(0);
    m_axisY->setMin(-AXIS_MAX_Y);
    m_axisX->setMax(AXIS_MAX_X);
    m_axisY->setMax(AXIS_MAX_Y);
}
