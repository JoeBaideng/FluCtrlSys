#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"serialcontrol.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    serial_control_.OpenDialog();
//    serial_control_.CloseSerialPort();
}

MainWindow::~MainWindow()
{
    delete ui;
}

