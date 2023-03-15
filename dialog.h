#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include"mystructs.h"
namespace Ui {
class SerialDlg;
}

/*
 * 用来可视化选择串口的各项参数，归属于SerialControl类。此对话框复用了2.0版本的dialog
 * */
class SerialDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SerialDlg(QStringList portNameList,QWidget *parent = nullptr);
    ~SerialDlg();
protected:

private:
//    QString portName;
//    QString baudRate;
//    QString dataBit;
//    QString stopBit;
//    int parityCheck;
//    QString fluidControl;
    SerialSet serial_set_;
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
public:
    SerialSet TakeSerialSet();
};

#endif // DIALOG_H
