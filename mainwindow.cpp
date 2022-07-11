#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isStart = false;
    isHEX = false;
    isSave = false;
    isDemo = false;

    AcqMode = 1;

    //set Style Sheet
//    setLocalStyleSheet();

    //set Local Message
    setLocalMsg();

    udp_recv = new UDP_Recv(this);
    udp_recv->start();

    SaveTimer = new QTimer(); // writetofiles Timer
    SaveTimer->setTimerType(Qt::PreciseTimer);
    FlashTimer_Pulse = new QTimer(); //Flash pulsewave_widget2 Timer
    FlashTimer_Pulse->setTimerType(Qt::PreciseTimer);
    DemoTimer = new QTimer(); //demodualtion Timer
    DemoTimer->setTimerType(Qt::PreciseTimer);
    FlashTimer = new QTimer(); //Flash demowave_widget2 Timer
    DemoTimer->setTimerType(Qt::PreciseTimer);

    writeToFiles = new WriteToFiles(udp_recv);
    pulsewave_Widget = new pulsewave_widget();
    pulsewave_Widget2 = new pulsewave_widget2(udp_recv);
    demodu = new Demodulation(udp_recv); 
    demowave_Widget = new demowave_widget(demodu);
    demowave_Widget2 = new demowave_widget2(demodu);
    com_send = new COM_Send(this);
    demodata_save = new DemoData_Save(demodu);

    //clear window
    if(ui->textEdit_Msg->isFullScreen())
        ui->textEdit_Msg->clear();

    connect(ui->comboBox_Mode, QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::on_comboBox_Mode_currentIndexChangedSlot);
    connect(udp_recv,&QThread::finished,this,&MainWindow::FinishUDP_RecvThread);
    connect(SaveTimer,&QTimer::timeout,this,&MainWindow::OpenSaveThread);
    connect(DemoTimer,&QTimer::timeout,this,&MainWindow::OpenDemoSaveThread);
//    connect(FlashTimer,&QTimer::timeout,demowave_Widget,&demowave_widget::FlashWave);
    connect(FlashTimer_Pulse,&QTimer::timeout,pulsewave_Widget2,&pulsewave_widget2::FlashWave);
    connect(FlashTimer,&QTimer::timeout,demowave_Widget2,&demowave_widget2::FlashWave);
    connect(writeToFiles,&QThread::finished,this,&MainWindow::FinishWriteToFilesThread);
    connect(demodu,&QThread::finished,this,&MainWindow::FinishDemodulationThread);
    connect(demodata_save,&QThread::finished,this,&MainWindow::FinishDemoData_saveThread);
//    connect(udp_recv,&UDP_Recv::SendtoWidget,pulsewave_Widget,&pulsewave_widget::FlashWave3,Qt::BlockingQueuedConnection);
//    connect(udp_recv,&UDP_Recv::SendtoWidget,pulsewave_Widget2,&pulsewave_widget2::FlashWave,Qt::BlockingQueuedConnection);
//    connect(demodu,&Demodulation::sendToDemoWave_widget,demowave_Widget,&demowave_widget::FlashWave,Qt::BlockingQueuedConnection);
    connect(pulsewave_Widget2,&pulsewave_widget2::PauseWave,this,&MainWindow::PulseWave_pause_slot);
    connect(pulsewave_Widget2,&pulsewave_widget2::RestartWave,this,&MainWindow::PulseWave_restart_slot);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLocalStyleSheet()
{
    //set Style Sheet
    QFile file("C:/Qt_UDP_DAS/my.qss");

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
    if(!FlashTimer_Pulse->isActive()) FlashTimer_Pulse->start(10); //10ms 脉冲信号 flash

    pulsewave_Widget2->show();
}

void MainWindow::on_pushButton_Send_clicked()
{
    com_send->start();

    ui->textEdit_Msg->insertPlainText("Sendding peak.txt ! \n");
}

void MainWindow::on_pushButton_Display_demo_clicked()
{
    if(!FlashTimer->isActive()) FlashTimer->start(100); //100ms 解调信号 flash

    demowave_Widget2->show();
}

void MainWindow::PulseWave_pause_slot()
{
    if(FlashTimer_Pulse->isActive()) FlashTimer_Pulse->stop();
}

void MainWindow::PulseWave_restart_slot()
{
    if(!FlashTimer->isActive()) FlashTimer_Pulse->start(10); //10ms 脉冲信号恢复 flash
}

