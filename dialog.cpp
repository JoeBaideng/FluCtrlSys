#include "dialog.h"
#include "ui_dialog.h"
#include<QDebug>
#include<QStringList>
SerialDlg::SerialDlg(QStringList portNameList,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialDlg)
{
    ui->setupUi(this);
    GetPortNameList(portNameList);
    SerialSetInit();
}

SerialDlg::~SerialDlg()
{
    delete ui;
}

//获取从外部传来的串口名列表
void SerialDlg::GetPortNameList(QStringList portNameList)
{
    port_name_list_=portNameList;
}

//取得设置好的串口参数
SerialSet SerialDlg::TakeSerialSet()
{
    return serial_set_;
}

//初始化串口参数列表
void SerialDlg::SerialSetInit()
{
    QStringList baud_list;   //波特率
    QStringList parity_list; //校验位
    QStringList dataBits_list;   //数据位
    QStringList stop_bits_list;   //停止位
    // 波特率    //波特率默认选择下拉第三项：9600
    baud_list<<"1200"<<"2400"<<"4800"<<"9600"
           <<"14400"<<"19200"<<"38400"<<"56000"
          <<"57600"<<"115200";
    ui->comboBoxBaudRate->addItems(baud_list);
    ui->comboBoxBaudRate->setCurrentIndex(3);
    // 校验      //校验默认选择无
    parity_list<<"无"<<"奇"<<"偶";
    ui->comBoxParityCheck->addItems(parity_list);
    ui->comBoxParityCheck->setCurrentIndex(0);
    // 数据位      //数据位默认选择8位
    dataBits_list<<"5"<<"6"<<"7"<<"8";
    ui->comboBoxDataBit->addItems(dataBits_list);
    ui->comboBoxDataBit->setCurrentIndex(3);
    // 停止位      //停止位默认选择1位
    stop_bits_list<<"1"<<"2";
    ui->comboBoxStopBit->addItems(stop_bits_list);
    ui->comboBoxStopBit->setCurrentIndex(0);

    ui->comboBoxSerial->addItems(port_name_list_);
    serial_set_.port_name=ui->comboBoxSerial->currentText();
    serial_set_.baud_rate=ui->comboBoxBaudRate->currentText();
    serial_set_.data_bit=ui->comboBoxDataBit->currentText();
    serial_set_.stop_bit=ui->comboBoxStopBit->currentText();
    serial_set_.parity_check=ui->comBoxParityCheck->currentIndex();
    serial_set_.flu_control=ui->comboBoxFluidControl->currentText();
}
//这几个槽函数作为数据改变时的响应
void SerialDlg::on_comboBoxSerial_currentIndexChanged(const QString &arg1)
{
    serial_set_.port_name=ui->comboBoxSerial->currentText();
}

void SerialDlg::on_comboBoxBaudRate_currentIndexChanged(const QString &arg1)
{
    serial_set_.baud_rate=ui->comboBoxBaudRate->currentText();
}

void SerialDlg::on_comboBoxDataBit_currentIndexChanged(const QString &arg1)
{
    serial_set_.data_bit=ui->comboBoxDataBit->currentText();
}

void SerialDlg::on_comboBoxStopBit_currentIndexChanged(const QString &arg1)
{
    serial_set_.stop_bit=ui->comboBoxStopBit->currentText();
}

void SerialDlg::on_comBoxParityCheck_currentIndexChanged(const QString &arg1)
{
    serial_set_.parity_check=ui->comBoxParityCheck->currentIndex();
}

void SerialDlg::on_comboBoxFluidControl_currentIndexChanged(const QString &arg1)
{
    serial_set_.flu_control=ui->comboBoxFluidControl->currentText();
}
