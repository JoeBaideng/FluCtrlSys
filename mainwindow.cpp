#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"serialcontrol.h"
#include"xmleditor.h"
#include"mystructs.h"

#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    EOCMap eoc_map=xml_editor.ReadFile("template.xml");
    qDebug()<<eoc_map.equip_names;
    qDebug()<<eoc_map.equip_orders_map;
    qDebug()<<eoc_map.order_code_map;
//    serial_control_.OpenDialog();
//    serial_control_.CloseSerialPort();
}

MainWindow::~MainWindow()
{
    delete ui;
}

