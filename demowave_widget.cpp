#include "demowave_widget.h"
#include "ui_demowave_widget.h"

demowave_widget::demowave_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::demowave_widget)
{
    ui->setupUi(this);

    initWidget();


}

demowave_widget::~demowave_widget()
{
    delete ui;
}

void demowave_widget::initWidget()
{
    // 创建横纵坐标轴并设置显示范围
    m_axisX = new QValueAxis();
    m_axisY = new QValueAxis();
    m_axisX->setTitleText("Time Series");
    m_axisY->setTitleText("Phase (rad)");
    m_axisX->setMin(0);
    m_axisY->setMin(-AXIS_MAX_Y);
    m_axisX->setMax(AXIS_MAX_X);
    m_axisY->setMax(AXIS_MAX_Y);
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

//HEX发送
void demowave_widget::FlashWave(shared_ptr<CirQueue<float>> DEMOdata)
{
    qDebug() <<"Flash Demodulation Wave Slot responsed !"<<endl;

    m_lineSeries->clear();

    int sizeoDemoData = READ_DEMO_LENGTH;

    //DEMOdata[] split into 4 channels
    for(int k = 0; k<sizeoDemoData; k+=4){
        int p = k/4;
        Demodata_1[p] = DEMOdata->pop();
        Demodata_2[p] = DEMOdata->pop();
        Demodata_3[p] = DEMOdata->pop();
        Demodata_4[p] = DEMOdata->pop();
    }

    //    Channel select
    ChannelIndex = ui->comboBox_Channel->currentIndex();

    switch (ChannelIndex) {
    case 0:{
        for(int i = 0;i<DISPLAY_LENGTH_DEMO; i++)
            m_lineSeries->append(QPointF(i,Demodata_1[i]));
        break;
    }

    case 1:{
        for(int i = 0;i<DISPLAY_LENGTH_DEMO; i++)
            m_lineSeries->append(QPointF(i,Demodata_2[i]));
        break;
    }

    case 2:{
        for(int i = 0;i<DISPLAY_LENGTH_DEMO; i++)
            m_lineSeries->append(QPointF(i,Demodata_3[i]));
        break;
    }

    case 3:{
        for(int i = 0;i<DISPLAY_LENGTH_DEMO; i++)
            m_lineSeries->append(QPointF(i,Demodata_4[i]));
        break;
    }

    default:
        break;
    }

}

void demowave_widget::on_pushButton_reset_clicked()
{
    m_axisX->setMin(0);
    m_axisY->setMin(-AXIS_MAX_Y);
    m_axisX->setMax(AXIS_MAX_X);
    m_axisY->setMax(AXIS_MAX_Y);
}

