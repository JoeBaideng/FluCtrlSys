#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"serialcontrol.h"
#include"xmleditor.h"
#include"mystructs.h"
#include<QDebug>

//消息队列：先在view类中生成消息队列以及时间，再在mainwindow中发送给串口

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList headers;
    headers<<"模块"<<"命令"<<"参数设置"<<"时间"<<"故障检查"<<"备注"<<"执行进度";
    EOCMap eoc_map=xml_editor.ReadFile("template.xml");
    ui->selection_view->SetHeaders(headers);
    ui->selection_view->InitView(eoc_map);

}

MainWindow::~MainWindow()
{
    delete ui;
    serial_control_.CloseSerialPort();
}



//表格1发送数据，表格里的数据由selectionview整理后打包，再由串口发送
void MainWindow::on_btn_send_1_clicked()
{
    QList<QPair<QString,float>>data=ui->selection_view->GetCodeAndTime();
    for(int i=0;i<data.size();i++)
    {
        serial_control_.SendData(data[i].first);
        //等待
        QEventLoop eventloop;
        QTimer::singleShot(data[i].second*1000,&eventloop,SLOT(quit()));
        eventloop.exec();
    }
}
//关闭串口
void MainWindow::on_action_close_serial_triggered()
{
    serial_control_.CloseSerialPort();
}
//打开串口对话框
void MainWindow::on_action_open_dlg_triggered()
{
    serial_control_.OpenDialog();
}


void MainWindow::on_act_refresh_serial_triggered()
{
    serial_control_.RefreshDeviceList();
}
