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

    //set Local Message
    setLocalMsg();

    //new UDP_Recv Thread
    udp_recv = new UDP_Recv(this);

    udp_recv->start();

    //Counting 60s
    udpTimer = new QTimer();
    udpTimer->setTimerType(Qt::PreciseTimer);

    //new WriteToFiles Thread
    writeToFiles = new WriteToFiles(udp_recv);

    //clear window
    if(ui->textEdit_Msg->isFullScreen())
        ui->textEdit_Msg->clear();

    connect(udp_recv,&QThread::finished,this,&MainWindow::FinishUDP_RecvThread);

    //Every 60s emit a timeout(), connect OpenWriteToFilesThread
    connect(udpTimer,&QTimer::timeout,this,&MainWindow::OpenWriteToFilesThread);

    //Every time dealMsg is finished, connect dealMsgFinshedSlot()
    connect(writeToFiles,&QThread::finished,this,&MainWindow::FinishWriteToFilesThread);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLocalMsg()
{
    //获取本机的计算机名
    QString localHostName = QHostInfo:: localHostName();
    qDebug() <<"localHostName: "<<localHostName<<endl;

    ui->textEdit_Msg->insertPlainText("localHostName: "+localHostName+'\n');

    //获取本机IP
    QHostInfo info = QHostInfo::fromName(localHostName);
    QList<QHostAddress> strIpAddress  = info.addresses();
    QHostAddress IpAddress =  strIpAddress.back();
    qDebug() << "IpAddress: " << IpAddress<<endl;
    qDebug()<<"--------------------------"<<endl;

    ui->textEdit_Msg->insertPlainText("IpAddress: "+IpAddress.toString()+'\n');

    //设置窗口的标题
    QString title = QString("Server IP: %1, Port: 7000").arg(IpAddress.toString());
    setWindowTitle(title);
}


void MainWindow::FinishUDP_RecvThread()
{
    //quit Thread
    udp_recv->quit();

    udp_recv->wait();

}

void MainWindow::OpenWriteToFilesThread()
{
    isSave = ui->checkBox_Save->isChecked();

    if(isSave && isStart){
        writeToFiles->start();
    }

}

void MainWindow::FinishWriteToFilesThread()
{
    //quit Thread
    writeToFiles->quit();

    writeToFiles->wait();

    ui->textEdit_Msg->insertPlainText(" Files have been saved in " + writeToFiles->saveFilenameAll+'\n');

}

void MainWindow::on_pushButton_Start_clicked()
{
    isStart = true;

    ui->textEdit_Msg->insertPlainText(" Started ! ");
}

void MainWindow::on_pushButton_Stop_clicked()
{
    isStart = false;
    isSave = false;

    ui->checkBox_ASCII->setChecked(isStart);
    ui->checkBox_Hex->setChecked(isStart);
    ui->checkBox_Save->setChecked(isSave);

    //clear CHdata
    udp_recv->clearCHdata();

    ui->textEdit_Msg->insertPlainText(" Stopped ! ");
}

void MainWindow::on_pushButton_Clear_clicked()
{

    ui->textEdit_Msg->clear();

}


void MainWindow::on_checkBox_Save_clicked()
{

    udpTimer->start(1000);

}


void MainWindow::on_checkBox_ASCII_clicked()
{
    isASCII = true;
}


void MainWindow::on_checkBox_Hex_clicked()
{
    isHEX = true;
}


void MainWindow::on_pushButton_Display_clicked()
{
    wave_widget *v = new wave_widget();

    v->show();
}

