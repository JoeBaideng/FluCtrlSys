#ifndef SERIALCONTROL_H
#define SERIALCONTROL_H
#include <QMainWindow>
#include<QComboBox>
#include<QStandardItemModel>
#include<QSplitter>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include<QPair>
#include<QLabel>
#include<QAction>
#include<QTimer>
#include<QObject>
#include"mystructs.h"

/*
 * SerialControl对串口进行控制以及串口数据的收发
 *
 * */
class SerialControl :public QObject
{
    Q_OBJECT
public:
    SerialControl();
private:
    QSerialPort*serial_port_;
    SerialSet serial_set_;
    QStringList port_name_list;


private:
    void InitSerial();
public:
    bool IsOpened();
    void OpenDialog();
    bool OpenSerialPort();
    void CloseSerialPort();
    void SendData(const QString data);
    void RefreshDeviceList();
    QString ReadData();
};

#endif // SERIALCONTROL_H
