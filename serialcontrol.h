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

//串口控制量
struct SerialSet
{
    QString port_name;//串口名
    QString baud_rate;//波特率
    QString data_bit;//数据位
    QString stop_bit;//停止位
    int parity_check;//奇偶校验
    QString flu_control;//流控制
};
/*
 * SerialControl对串口进行控制以及串口数据的收发
 *
 * */
class SerialControl
{
public:
    SerialControl();
private:
    QSerialPort*serial_port_;
    SerialSet serial_set_;


private:
    bool IsOpened();
};

#endif // SERIALCONTROL_H
