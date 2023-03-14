#include "serialcontrol.h"
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
#include<QMessageBox>
#include<QDebug>
#include<QObject>
#include"dialog.h"
/*
 * 串口控制模块
 *
 *
 */
SerialControl::SerialControl()
{
    serial_port_=new QSerialPort;
    InitSerial();
}

bool SerialControl::IsOpened()
{
    return serial_port_->isOpen();
}
//获取串口列表
void SerialControl::InitSerial()
{

    const auto infos = QSerialPortInfo::availablePorts();
    for(const QSerialPortInfo &info : infos)
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            port_name_list.append(info.portName());
            serial.close();
        }
    }
}
//打开参数选择对话框
void SerialControl::OpenDialog()
{
    SerialDlg*dlg=new SerialDlg(port_name_list);
    if(IsOpened())
    {
        QMessageBox::StandardButton result = QMessageBox::information(NULL, tr("注意"),tr("串口已被打开！若要修改设置请先关闭串口"));
        return;
    }
    int res=dlg->exec();
    //串口参数设置
    if(res==QDialog::Accepted)
    {
        serial_set_=dlg->TakeSerialSet();
        QMessageBox::StandardButton if_open=QMessageBox::question(NULL,
                                                                 tr("提示"),
                                                                 tr("是否立即打开该串口？"),
                                                                 QMessageBox::Ok | QMessageBox::Cancel,
                                                                 QMessageBox::Ok);
        if(if_open==QMessageBox::Ok)
        {
            bool isOpened=OpenSerialPort();
            qDebug()<<isOpened;
        }

    }
    if (res == QDialog::Rejected)
    {
        return;
    }
}

//打开串口
bool SerialControl::OpenSerialPort()
{
    serial_port_->setPortName(serial_set_.port_name);
    //已打开，返回
    if(IsOpened())
    {
        QMessageBox::about(NULL, tr("打开串口"), tr("串口已经打开！"));
        return true;
    }
    //打开失败
    if(!serial_port_->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        QMessageBox::critical(NULL, tr("打开串口"), tr("串口打开失败！"));
        return false;
    }
    //打开成功
    bool x=serial_port_->setBaudRate(serial_set_.baud_rate.toInt(),QSerialPort::AllDirections);//设置波特率和读写方向
    qDebug()<<x;
    switch(serial_set_.data_bit.toInt())
    {
    case 8: serial_port_->setDataBits(QSerialPort::Data8); break;
    case 7: serial_port_->setDataBits(QSerialPort::Data7); break;
    case 6: serial_port_->setDataBits(QSerialPort::Data6); break;
    case 5: serial_port_->setDataBits(QSerialPort::Data5); break;
    default: break;
    }
    switch(serial_set_.stop_bit.toInt())
    {
    case 1: serial_port_->setStopBits(QSerialPort::OneStop);break;
    case 2: serial_port_->setStopBits(QSerialPort::TwoStop);break;
    default:break;
    }
    switch(serial_set_.parity_check)
    {
    case 0: serial_port_->setParity(QSerialPort::NoParity);break;
    case 1: serial_port_->setParity(QSerialPort::OddParity); break;
    case 2: serial_port_->setParity(QSerialPort::EvenParity); break;
    default:break;
    }
    serial_port_->setFlowControl(QSerialPort::NoFlowControl);
    QMessageBox::about(NULL, tr("打开串口"), tr("串口打开成功！"));
    //ui->actionDisConnect->setEnabled(true);
    //serialStatusLabel->setText(tr("串口已连接"));
    return true;
}

void SerialControl::CloseSerialPort()
{
    if(IsOpened())
        serial_port_->close();
}

void SerialControl::SendData(const QString data)
{
    if(!serial_port_->isOpen())
        return;
    QByteArray send_data=QByteArray::fromHex(data.toLatin1());
    serial_port_->write(send_data);
    qDebug()<<send_data;
}

QString SerialControl::ReadData()
{
    QByteArray byte_data = serial_port_->readAll();
    if(byte_data.isEmpty())
        return "";
    //将数据转换为hex格式并以空格分隔->去掉头尾空白字符->转换为大写形式
    QString frame_data;
    frame_data.prepend(byte_data.toHex());
    return frame_data;
}
