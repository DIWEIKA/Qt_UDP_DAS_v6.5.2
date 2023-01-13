#include "com_send.h"

COM_Send::COM_Send(MainWindow* Mainwindow)
{
    mainWindow = Mainwindow;

    myCom = new Win_QextSerialPort("COM3",QextSerialBase::EventDriven); //设置本地端口

    myCom->setParity(PAR_NONE); //奇偶校验设置，我们设置为无校验
    myCom->setDataBits(DATA_8);//数据位设置，我们设置为8位数据位
    myCom->setStopBits(STOP_1);//停止位设置，我们设置为1位停止位
    myCom->setPortName("COM3"); //设置本地端口号
    myCom->setBaudRate(BAUD115200); //设置波特率

    filePath = QString("C:/Qt_UDP_DAS/peak.txt"); //build所在目录下

    if (filePath.isEmpty())
    {
//        mainWindow->ui->textEdit_Msg->insertPlainText(QString("Warning! Empty File! ")+"\n");
        return;
    }

    //文件路径显示到发送框
//    mainWindow->ui->textEdit_Msg->insertPlainText(QString("Configeration File Directory: ")+filePath+"\n");
}

void COM_Send::run()
{
    //1. 打开peak.txt
    configFile = new QFile(filePath);

    if (!configFile->exists())
    {
//        mainWindow->ui->textEdit_Msg->insertPlainText(QString("Warning! File is Not Exist! ")+"\n");
        return;
    }

    if (!configFile->open(QIODevice::ReadOnly))
    {
//        mainWindow->ui->textEdit_Msg->insertPlainText(QString("Warning! File Open Failed! ")+"\n");
        return;
    }

    //2. 读取peak.txt至peakData
    peakData = configFile->readAll();

    configFile->close();

    if (peakData.isEmpty())
    {
//        mainWindow->ui->textEdit_Msg->insertPlainText(QString("Warning! File Content is Empty! ")+"\n");
        return;
    }

    //3. 打开串口
    myCom->open(QIODevice::ReadWrite);

    if(myCom->isOpen()){

        //4. peakData >> myCom
        myCom->write(peakData);

//        mainWindow->ui->textEdit_Msg->insertPlainText(QString("Send to COM Successful! ")+"\n");
    }

    else
//        mainWindow->ui->textEdit_Msg->insertPlainText(QString("Open COM Failed! ")+"\n");

    qDebug() << "com_send Thread is over " << endl;
}
