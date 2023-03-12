#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class SerialDlg;
}
//串口控制量,与SerialControl类中的相同
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
 * 用来可视化选择串口的各项参数，归属于SerialControl类。此对话框复用了2.0版本的dialog
 * */
class SerialDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SerialDlg(QStringList portNameList,QWidget *parent = nullptr);
    ~SerialDlg();
private:
//    QString portName;
//    QString baudRate;
//    QString dataBit;
//    QString stopBit;
//    int parityCheck;
//    QString fluidControl;
    SerialSet serial_set_dlg_;
    Ui::SerialDlg *ui;
private:
    QStringList port_name_list_;
private slots:
    void on_comboBoxSerial_currentIndexChanged(const QString &arg1);
    void on_comboBoxBaudRate_currentIndexChanged(const QString &arg1);
    void on_comboBoxDataBit_currentIndexChanged(const QString &arg1);
    void on_comboBoxStopBit_currentIndexChanged(const QString &arg1);
    void on_comBoxParityCheck_currentIndexChanged(const QString &arg1);
    void on_comboBoxFluidControl_currentIndexChanged(const QString &arg1);
private:
    void SerialSetInit();
    void GetPortNameList(QStringList portNameList);
};

#endif // DIALOG_H
