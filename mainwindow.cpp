#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,isDemo(false)
    ,isStart(false)
    ,isHEX(false)
    ,AcqMode(1)
    ,Freq(10*1000) //采样率
    ,demoFlashTime(50)//解调信号 flash一次的时间
    ,pulseFlashTime(5)//脉冲信号 flash一次的时间
    ,demoFlashFreq(1000/demoFlashTime)  //即flash的频率
    ,pulseFlashFreq(1000/pulseFlashTime) //即flash的频率
    //对象的初始化不要用构造函数初始化列表
//    ,udp_recv(new UDP_Recv(this))
//    ,SaveTimer(new QTimer()) // writetofiles Timer
//    ,FlashTimer_Pulse(new QTimer())  //Flash pulsewave_widget2 Timer
//    ,DemoTimer(new QTimer()) //demodualtion Timer
//    ,FlashTimer(new QTimer()) //Flash demowave_widget2 Timer
//    ,writeToFiles(new WriteToFiles(udp_recv))
//    ,pulsewave_Widget2(new pulsewave_widget2(udp_recv))
//    ,demodu(new Demodulation(udp_recv,demoFlashTime,demoFlashFreq))
//    ,demowave_Widget2(new demowave_widget2(demodu))
//    ,com_send(new COM_Send(this))
//    ,demodata_save(new DemoData_Save(demodu))
{
    ui->setupUi(this);

    setWindowIcon(QIcon("C:/Qt_UDP_DAS/main.png"));

    setWindowTitle(QString("Qt_UDP_DAS"));

    //set Style Sheet
    setLocalStyleSheet();

    //set Local Message
    setLocalMsg();

    //read configuration file
    readConfigFile();

    udp_recv = new UDP_Recv(this);
    udp_recv->start();
    SaveTimer = new QTimer();
    FlashTimer_Pulse = new QTimer();
    DemoTimer = new QTimer();
    FlashTimer = new QTimer();
    writeToFiles = new WriteToFiles(udp_recv, peakNum);
    pulsewave_Widget2 = new pulsewave_widget2(udp_recv);
    demodu = new Demodulation(udp_recv,demoFlashTime,demoFlashFreq,Freq,peakNum);
    demowave_Widget2 = new demowave_widget2(demodu);
    com_send = new COM_Send(this);
    demodata_save = new DemoData_Save(demodu);

    SaveTimer->setTimerType(Qt::PreciseTimer);
    FlashTimer_Pulse->setTimerType(Qt::PreciseTimer);
    DemoTimer->setTimerType(Qt::PreciseTimer);
    FlashTimer->setTimerType(Qt::PreciseTimer);

    //clear window
    if(ui->textEdit_Msg->isFullScreen())
        ui->textEdit_Msg->clear();

    connect(ui->comboBox_Mode, QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::on_comboBox_Mode_currentIndexChangedSlot);
    connect(udp_recv,&QThread::finished,this,&MainWindow::FinishUDP_RecvThread);
    connect(SaveTimer,&QTimer::timeout,this,&MainWindow::OpenSaveThread);
    connect(DemoTimer,&QTimer::timeout,this,&MainWindow::OpenDemoSaveThread);
    connect(FlashTimer_Pulse,&QTimer::timeout,pulsewave_Widget2,&pulsewave_widget2::FlashWave);
    connect(FlashTimer,&QTimer::timeout,demowave_Widget2,&demowave_widget2::FlashWave);
    connect(writeToFiles,&QThread::finished,this,&MainWindow::FinishWriteToFilesThread);
    connect(demodu,&QThread::finished,this,&MainWindow::FinishDemodulationThread);
    connect(demodata_save,&QThread::finished,this,&MainWindow::FinishDemoData_saveThread);
    connect(pulsewave_Widget2,&pulsewave_widget2::PauseWave,this,&MainWindow::PulseWave_pause_slot);
    connect(pulsewave_Widget2,&pulsewave_widget2::RestartWave,this,&MainWindow::PulseWave_restart_slot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLocalStyleSheet()
{

    QFile file("C:/Qt_UDP_DAS/qssStyls/Aqua.qss");//set Style Sheet Directory

    file.open(QIODevice::ReadOnly);

    QString styleSheet = QLatin1String(file.readAll());

    qApp->setStyleSheet(styleSheet);

}

void MainWindow::setLocalMsg()
{
    //获取本机的计算机名
    QString localHostName = QHostInfo:: localHostName();
    qDebug() <<"LocalHostName: "<<localHostName<<endl;

    ui->textEdit_Msg->insertPlainText("LocalHostName: "+localHostName+"\n");

    //获取本机IP
    QHostInfo info = QHostInfo::fromName(localHostName);
    QList<QHostAddress> strIpAddress  = info.addresses();
    QHostAddress IpAddress =  strIpAddress.back();
    qDebug() << "IpAddress: " << IpAddress<<endl;
    qDebug()<<"--------------------------"<<endl;

    ui->textEdit_Msg->insertPlainText("IpAddress: "+IpAddress.toString()+" Port: 7000 \n");

    //设置窗口的标题
    QString title = QString("Qt_UDP_DAS");
//    setWindowTitle(title);

    ui->textEdit_Msg->insertPlainText("Setting Acquisition Card Mode I ! \n");
}

void MainWindow::FinishUDP_RecvThread()
{
    udp_recv->quit();
    udp_recv->wait();
}

void MainWindow::OpenSaveThread()
{
    isSave = ui->checkBox_Save->isChecked();

    if(isSave && isStart)
        writeToFiles->start();
}

void MainWindow::OpenDemoSaveThread()
{
    isDemo = ui->checkBox_Demo->isChecked();

    if(isDemo && isStart)
        demodata_save->start(); //开始解调存储线程
}

void MainWindow::readConfigFile()
{
    QString filePath = QString("C:/Qt_UDP_DAS/peak.txt"); //build所在目录下
    QFile file(filePath);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug()<<"Can't open the Configration file!"<<endl;
    }
    QByteArray configData = file.readAll(); //读取所有数据
    char peakNumChar_3 = configData[3]; //peakNum的百位存放在第四个位置
    char peakNumChar_4 = configData[4]; //peakNum的十位存放在第五个位置
    char peakNumChar_5 = configData[5]; //peakNum的个位存放在第六个位置
    char peakNumChar_6 = configData[6]; //换行符


    //peakNum是个位数
    if(peakNumChar_4 == '\n'){
        bool ok;
        peakNum = QString(peakNumChar_3).toInt(&ok,16)*1;
    }
    //peakNum是十位数
    else if(peakNumChar_5 == '\n'){
        bool ok;
        peakNum = QString(peakNumChar_3).toInt(&ok,16)*10 + QString(peakNumChar_4).toInt(&ok,16)*1;
    }
    //peakNum是百位数
    else if(peakNumChar_6 == '\n'){
        bool ok;
        peakNum = QString(peakNumChar_3).toInt(&ok,16)*100 + QString(peakNumChar_4).toInt(&ok,16)*10 + QString(peakNumChar_5).toInt(&ok,16)*1;
    }
}

void MainWindow::FinishWriteToFilesThread()
{
    writeToFiles->quit();
    writeToFiles->wait();

    ui->textEdit_Msg->insertPlainText(" Save Files have been saved in " + writeToFiles->saveFilenameAll+"\n");
}

void MainWindow::FinishDemodulationThread()
{
    demodu->quit();
    demodu->wait();
}

void MainWindow::FinishDemoData_saveThread()
{
    demodata_save->quit();
    demodata_save->wait();

    ui->textEdit_Msg->insertPlainText("Demodulation have been saved in " + demodata_save->saveFileDemo+ "\n");
}

void MainWindow::on_pushButton_Start_clicked()
{
    ui->textEdit_Msg->insertPlainText("Started ! \n");

    if(!udp_recv->isRunning())
        udp_recv->start();

    isStart = true;

    if(isSave) ui->checkBox_Demo->setDisabled(true);
    if(isDemo) ui->checkBox_Save->setDisabled(true);

    if(AcqMode == 1){
        ui->checkBox_Save->setDisabled(true);

        ui->checkBox_Demo->setDisabled(true);
    }

    if(AcqMode == 2){
        ui->pushButton_Display_pulse->setDisabled(true);

        ui->pushButton_Send->setDisabled(true);
    }

}

void MainWindow::on_pushButton_Stop_clicked()
{
    isStart = false;
    isSave = false;
    isHEX = false;
    isDemo = false;

    ui->checkBox_Demo->setEnabled(true);
    ui->checkBox_Hex->setEnabled(true);
    ui->checkBox_Save->setEnabled(true);
    ui->pushButton_Display_pulse->setEnabled(true);
    ui->pushButton_Send->setEnabled(true);

    ui->checkBox_Hex->setChecked(isStart);
    ui->checkBox_Save->setChecked(isSave);
    ui->checkBox_Demo->setChecked(isDemo);

    //clear CHdata
    udp_recv->clearCHdata();
    udp_recv->quit();

    //clear DEMOdata
    demodu->DEMOdata_flash->clear();
    demodu->DEMOdata_save->clear();

    if(SaveTimer->isActive()) SaveTimer->stop();
    if(DemoTimer->isActive()) DemoTimer->stop();
    if(FlashTimer_Pulse->isActive()) FlashTimer_Pulse->stop();
    if(FlashTimer->isActive()) FlashTimer->stop();

    ui->textEdit_Msg->insertPlainText("Stopped ! \n");
}

void MainWindow::on_pushButton_Clear_clicked()
{
    ui->textEdit_Msg->clear();
}

void MainWindow::on_checkBox_Save_clicked()
{
    isSave = true;

    if(!SaveTimer->isActive()) SaveTimer->start(60000); //存60s的数据
}

void MainWindow::on_checkBox_Hex_clicked()
{
    isHEX = true;
}

void MainWindow::on_checkBox_Demo_clicked()
{
    isDemo = true;

    if(!DemoTimer->isActive()) DemoTimer->start(60000); //解调存储计时

    demodu->start(); //开始解调线程
}

void MainWindow::on_comboBox_Mode_currentIndexChangedSlot()
{
    //采集卡模式选择
    if(ui->comboBox_Mode->currentIndex() == 0){
        ui->textEdit_Msg->insertPlainText("Setting Acquisition Card Mode I ! \n");

        AcqMode = 1;
    }

    if(ui->comboBox_Mode->currentIndex() == 1){
        ui->textEdit_Msg->insertPlainText("Setting Acquisition Card Mode II ! \n");

        AcqMode = 2;
    }
}

void MainWindow::on_pushButton_Display_pulse_clicked()
{


    if(!FlashTimer_Pulse->isActive()) FlashTimer_Pulse->start(pulseFlashTime);

    pulsewave_Widget2->show();
}

void MainWindow::on_pushButton_Send_clicked()
{
    com_send->start();

    ui->textEdit_Msg->insertPlainText("Sendding peak.txt ! \n");
}

void MainWindow::on_pushButton_Display_demo_clicked()
{

    if(!FlashTimer->isActive()) FlashTimer->start(demoFlashTime);

    demowave_Widget2->show();
}

void MainWindow::PulseWave_pause_slot()
{
    if(FlashTimer_Pulse->isActive()) FlashTimer_Pulse->stop();
}

void MainWindow::PulseWave_restart_slot()
{
    if(!FlashTimer->isActive()) FlashTimer_Pulse->start(pulseFlashTime);
}

