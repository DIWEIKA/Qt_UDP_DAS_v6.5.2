#ifndef DEMODATA_SAVE_H
#define DEMODATA_SAVE_H

#include <QThread>
#include <mainwindow.h>

class Demodulation;

class DemoData_Save : public QThread
{
    Q_OBJECT
public:
    DemoData_Save(Demodulation* demodulation);
    ~DemoData_Save();
    QString& SaveFileDemo() {return saveFileDemo;}
private:
    Demodulation* m_demodulation;

    QDateTime dateTime; //当前系统时间
    QString saveFileDemo;
    ofstream outfileDemo;
    int peakNum;

signals:

protected:
    void run();

};

#endif // DEMODATA_SAVE_H
