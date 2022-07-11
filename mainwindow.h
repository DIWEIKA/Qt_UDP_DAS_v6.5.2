#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QQueue>
#include "CirQueue.h"
#include <memory>
#include <fstream>
#include <sstream>
#include <QDateTime>
#include <QTime>
#include <QTimer>
#include <QtNetwork>
#include <recvdata.h>
#include <QtDebug>
#include <vector>
#include <winsock2.h>
#include <windows.h>
#include "writetofiles.h"
#include "udp_recv.h"
#include "pulsewave_widget.h"
#include "pulsewave_widget2.h"
#include "demowave_widget.h"
#include "demowave_widget2.h"
#include "demodulation.h"
#include "com_send.h"
#include "demodata_save.h"
#include "ui_mainwindow.h"


typedef unsigned char BYTE;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

 //使用前向声明
class WriteToFiles;
class UDP_Recv;
class pulsewave_widget;
class pulsewave_widget2;
class demowave_widget;
class demowave_widget2;
class Demodulation;
class COM_Send;
class DemoData_Save;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;

    QTimer* SaveTimer;
    QTimer* DemoTimer;
    QTimer* FlashTimer_Pulse;
    QTimer* FlashTimer;
    UDP_Recv* udp_recv;
    WriteToFiles* writeToFiles;
    pulsewave_widget *pulsewave_Widget;
    pulsewave_widget2 *pulsewave_Widget2;
    demowave_widget *demowave_Widget;
    demowave_widget2 *demowave_Widget2;
    Demodulation *demodu;
    COM_Send *com_send;
    DemoData_Save *demodata_save;
    bool isSave;
    bool isDemo;
    bool isStart;
    bool isHEX;
    int AcqMode; //采集卡模式选择

    void setLocalStyleSheet();
    void setLocalMsg();
    void OpenSaveThread();
    void OpenDemoSaveThread();
    void stopThread();


private slots:
    void FinishUDP_RecvThread();
    void FinishWriteToFilesThread();
    void FinishDemodulationThread();
    void FinishDemoData_saveThread();

    void on_pushButton_Start_clicked();

    void on_pushButton_Stop_clicked();

    void on_pushButton_Clear_clicked();

    void on_checkBox_Save_clicked();

    void on_checkBox_Hex_clicked();

    void on_pushButton_Display_pulse_clicked();

    void on_checkBox_Demo_clicked();

    void on_comboBox_Mode_currentIndexChangedSlot();

    void on_pushButton_Send_clicked();

    void on_pushButton_Display_demo_clicked();

    void PulseWave_pause_slot();
    void PulseWave_restart_slot();

private:

};
#endif // MAINWINDOW_H
