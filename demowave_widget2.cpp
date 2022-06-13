#include "demowave_widget2.h"
#include "ui_demowave_widget2.h"

demowave_widget2::demowave_widget2(Demodulation *demodulation):
    ui(new Ui::demowave_widget2)
{
    ui->setupUi(this);
    demodu = demodulation;

    initWidget();

    readConfigFile();

    initComboBox_Region();

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

demowave_widget2::~demowave_widget2()
{
    delete ui;
}

void demowave_widget2::initWidget()
{
    setWindowTitle(QString("Demodulation Wave Display"));

    m_customPlot = ui->customPlot;

    //每条曲线都会独占一个graph()
    m_customPlot->addGraph();
    m_customPlot->graph(0)->setPen(QPen(Qt::blue)); // 曲线的颜色
    m_customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // 曲线与X轴包围区的颜色

    // 边框右侧和上侧均显示刻度线，但不显示刻度值:
    // (参见 QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    m_customPlot->xAxis2->setVisible(true);
    m_customPlot->xAxis2->setTickLabels(false);
    m_customPlot->yAxis2->setVisible(true);
    m_customPlot->yAxis2->setTickLabels(false);
    // 使上下两个X轴的范围总是相等，使左右两个Y轴的范围总是相等
    //    connect(m_customPlot->xAxis, &QCPAxis::rangeChanged(QCPRange), m_customPlot->xAxis2, &QCPAxis::setRange(QCPRange));
    //    connect(m_customPlot->yAxis, &QCPAxis::rangeChanged(QCPRange), m_customPlot->yAxis2, &QCPAxis::setRange(QCPRange));

//    //自动调整XY轴的范围，以便显示出graph(0)中所有的点（下面会单独讲到这个函数）
//    m_customPlot->graph(0)->rescaleAxes(true);

    // 支持鼠标拖拽轴的范围、滚动缩放轴的范围，左键点选图层（每条曲线独占一个图层）
    m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

}

void demowave_widget2::readConfigFile()
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

void demowave_widget2::initComboBox_Region()
{
    ui->comboBox_Region->clear();

    for(int i=1; i<= peakNum; i++ )
        ui->comboBox_Region->addItem(QString::asprintf("Region %d",i));
}

//刷新波形显示
void demowave_widget2::FlashWave()
{
    qDebug() <<"Flash Demodulation Wave Slot responsed !"<<endl;

    //clear DEMOdata_flash first, then waiting. （解决实时性）
    demodu->DEMOdata_flash->clear();
    QThread::msleep(50);

    //clear plot data
    m_customPlot->graph(0)->data()->clear();

    int regionNum = peakNum;

    int sizeoDemoData = demodu->DEMOdata_flash->size();

    //重设sizeoDemoData的长度，使其为regionNum的倍数
    int N1 = sizeoDemoData/regionNum;
    sizeoDemoData = N1*peakNum;

    //DEMOdata[] split regions
    for(int k = 0; k<sizeoDemoData; k+=regionNum){
        int p = k/regionNum;
        for(int q=0; q<regionNum;q++){
//            if(demodu->DEMOdata_flash->isEmpty()) QThread::msleep(50);
            DemodataArray[q][p] = demodu->DEMOdata_flash->pop();
        }
    }

    //region select
    RegionIndex = ui->comboBox_Region->currentIndex();

    //dispaly wave
    for(int i = 0;i<DISPLAY_LENGTH_DEMO; i++){
        QVector<double> x(1),y(1);
        x[0] = i;
        y[0]= DemodataArray[RegionIndex][i];
        m_customPlot->graph(0)->addData(x, y);
    }

    m_customPlot->graph(0)->rescaleAxes(true);

    ui->customPlot->replot();
}

void demowave_widget2::on_pushButton_reset_clicked()
{
    m_customPlot->graph(0)->rescaleAxes(true);
    ui->customPlot->replot();
}

