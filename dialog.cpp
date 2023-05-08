#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QStringList>

SerialDlg::SerialDlg(QStringList portNameList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialDlg)
{
    ui->setupUi(this);
    GetPortNameList(portNameList);  // 获取从外部传来的串口名列表
    SerialSetInit();  // 初始化串口参数列表
}

SerialDlg::~SerialDlg()
{
    delete ui;
}

// 获取从外部传来的串口名列表
void SerialDlg::GetPortNameList(QStringList portNameList)
{
    port_name_list_ = portNameList;
}

// 取得设置好的串口参数
SerialSet SerialDlg::TakeSerialSet()
{
    return serial_set_;
}

// 初始化串口参数列表
void SerialDlg::SerialSetInit()
{
    QStringList baud_list;  // 波特率
    QStringList parity_list;  // 校验位
    QStringList dataBits_list;  // 数据位
    QStringList stop_bits_list;  // 停止位

    // 添加波特率列表，波特率默认选择下拉第三项：9600
    baud_list << "1200" << "2400" << "4800" << "9600"
              << "14400" << "19200" << "38400" << "56000"
              << "57600" << "115200";
    ui->comboBoxBaudRate->addItems(baud_list);
    ui->comboBoxBaudRate->setCurrentIndex(3);

    // 添加校验位列表，默认选择无
    parity_list << "无" << "奇" << "偶";
    ui->comBoxParityCheck->addItems(parity_list);
    ui->comBoxParityCheck->setCurrentIndex(0);

    // 添加数据位列表，默认选择8位
    dataBits_list << "5" << "6" << "7" << "8";
    ui->comboBoxDataBit->addItems(dataBits_list);
    ui->comboBoxDataBit->setCurrentIndex(3);

    // 添加停止位列表，默认选择1位
    stop_bits_list << "1" << "2";
    ui->comboBoxStopBit->addItems(stop_bits_list);
    ui->comboBoxStopBit->setCurrentIndex(0);

    // 添加串口名列表，获取当前选择的串口参数
    ui->comboBoxSerial->addItems(port_name_list_);
    serial_set_.port_name = ui->comboBoxSerial->currentText();
    serial_set_.baud_rate = ui->comboBoxBaudRate->currentText();
    serial_set_.data_bit = ui->comboBoxDataBit->currentText();
    serial_set_.stop_bit = ui->comboBoxStopBit->currentText();
    serial_set_.parity_check = ui->comBoxParityCheck->currentIndex();
    serial_set_.flu_control = ui->comboBoxFluidControl->currentText();
}

// 当选择的串口发生变化时，更新串口名参数
void SerialDlg::on_comboBoxSerial_currentIndexChanged(const QString &arg1)
{
    serial_set_.port_name = ui->comboBoxSerial->currentText();
}

// 当选择的波特率发生变化时，更新串口波特率参数
void SerialDlg::on_comboBoxBaudRate_currentIndexChanged(const QString &arg1)
{
    serial_set_.baud_rate = ui->comboBoxBaudRate->currentText();
}

// 当选择的数据位发生变化时，更新串口数据位参数
void SerialDlg::on_comboBoxDataBit_currentIndexChanged(const QString &arg1)
{
    serial_set_.data_bit = ui->comboBoxDataBit->currentText();
}

// 当选择的停止位发生变化时，更新串口停止位参数
void SerialDlg::on_comboBoxStopBit_currentIndexChanged(const QString &arg1)
{
    serial_set_.stop_bit = ui->comboBoxStopBit->currentText();
}

// 当选择的校验位发生变化时，更新串口校验位参数
void SerialDlg::on_comBoxParityCheck_currentIndexChanged(const QString &arg1)
{
    serial_set_.parity_check = ui->comBoxParityCheck->currentIndex();
}

// 当选择的流控制发生变化时，更新串口流控制参数
void SerialDlg::on_comboBoxFluidControl_currentIndexChanged(const QString &arg1)
{
    serial_set_.flu_control = ui->comboBoxFluidControl->currentText();
}
