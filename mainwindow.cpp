#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    isStart = false;

    isASCII = false;

    isHEX = false;

    isSave = false;

    isDemo = false;

    AcqMode = 1;

    //set Style Sheet
    setLocalStyleSheet();

    //set Local Message
    setLocalMsg();

    udp_recv = new UDP_Recv(this);

    udp_recv->start();

    //Counting 60s
    udpTimer = new QTimer();
    udpTimer->setTimerType(Qt::PreciseTimer);

    writeToFiles = new WriteToFiles(udp_recv);

    pulsewave_Widget = new pulsewave_widget();

    demowave_Widget = new demowave_widget();

    demodu = new Demodulation(udp_recv);

    com_send = new COM_Send(this);

    //clear window
    if(ui->textEdit_Msg->isFullScreen())
        ui->textEdit_Msg->clear();

    connect(ui->comboBox_Mode, QOverload<int>::of(&QComboBox::currentIndexChanged),this,&MainWindow::on_comboBox_Mode_currentIndexChangedSlot);

    connect(udp_recv,&QThread::finished,this,&MainWindow::FinishUDP_RecvThread);

    connect(udpTimer,&QTimer::timeout,this,&MainWindow::OpenSaveOrDemoThread);

    connect(writeToFiles,&QThread::finished,this,&MainWindow::FinishWriteToFilesThread);

    connect(demodu,&QThread::finished,this,&MainWindow::FinishDemodulationThread);

    connect(udp_recv,&UDP_Recv::SendtoWidget,pulsewave_Widget,&pulsewave_widget::FlashWave3,Qt::BlockingQueuedConnection);

    connect(demodu,&Demodulation::sendToDemoWave_widget,demowave_Widget,&demowave_widget::FlashWave,Qt::BlockingQueuedConnection);

//    connect(demodu,&Demodulation::sendDEMOdataToWrite,writeToFiles,&WriteToFiles::recvPhSlot,Qt::BlockingQueuedConnection);

//    connect(wave_Widget,QOverload<int>::of(&QComboBox::currentIndexChanged),wave_Widget,&wave_widget::on_comboBox_Channel_currentIndexChangedSlot);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLocalStyleSheet()
{
    //set Style Sheet
    QFile file("./my.qss"); //放在build directory下

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
    QString title = QString("Server IP: %1, Port: 7000").arg(IpAddress.toString());
    setWindowTitle(title);

    ui->textEdit_Msg->insertPlainText("Setting Acquisition Card Mode I ! \n");
}

void MainWindow::FinishUDP_RecvThread()
{
    udp_recv->quit();
    udp_recv->wait();
}

void MainWindow::OpenSaveOrDemoThread()
{
    isSave = ui->checkBox_Save->isChecked();

    isDemo = ui->checkBox_Demo->isChecked();

    if(isSave && isStart)
        writeToFiles->start();

    if(isDemo && isStart)
        demodu->start();

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

    ui->textEdit_Msg->insertPlainText("Demodulation have been saved in " + demodu->saveFileDemo+ "\n");
}

void MainWindow::on_pushButton_Start_clicked()
{
    ui->textEdit_Msg->insertPlainText("Started ! \n");

    if(!udp_recv->isRunning())
        udp_recv->start();

    isStart = true;

    if(isHEX) ui->checkBox_ASCII->setDisabled(true);

    if(isASCII){
        ui->checkBox_Hex->setDisabled(true);
        ui->pushButton_Display_pulse->setDisabled(true); //ASCII接收时不能显示波形
    }

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
    isASCII = false;
    isHEX = false;
    isDemo = false;

    ui->checkBox_ASCII->setEnabled(true);
    ui->checkBox_Demo->setEnabled(true);
    ui->checkBox_Hex->setEnabled(true);
    ui->checkBox_Save->setEnabled(true);
    ui->pushButton_Display_pulse->setEnabled(true);
    ui->pushButton_Send->setEnabled(true);

    ui->checkBox_ASCII->setChecked(isStart);
    ui->checkBox_Hex->setChecked(isStart);
    ui->checkBox_Save->setChecked(isSave);
    ui->checkBox_Demo->setChecked(isDemo);

    //clear CHdata
    udp_recv->clearCHdata();

    //end udp_recv Thread
    udp_recv->quit();

    ui->textEdit_Msg->insertPlainText("Stopped ! \n");
}

void MainWindow::on_pushButton_Clear_clicked()
{
    ui->textEdit_Msg->clear();
}

void MainWindow::on_checkBox_Save_clicked()
{
    //设置存储时间间隔
    udpTimer->start(15000);
    isSave = true;
}

void MainWindow::on_checkBox_ASCII_clicked()
{
    isASCII = true;
}

void MainWindow::on_checkBox_Hex_clicked()
{
    isHEX = true;
}



void MainWindow::on_checkBox_Demo_clicked()
{
     udpTimer->start(5000); //设置时间间隔为5秒
     isDemo = true;
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
    pulsewave_Widget->show();
}

void MainWindow::on_pushButton_Send_clicked()
{
    com_send->start();

     ui->textEdit_Msg->insertPlainText("Sendding peak.txt ! \n");
}


void MainWindow::on_pushButton_Display_demo_clicked()
{
    demowave_Widget->show();
}

