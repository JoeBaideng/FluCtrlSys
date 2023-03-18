#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"serialcontrol.h"
#include"xmleditor.h"
#include"mystructs.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_refresh_clicked();

    void on_open_clicked();

private:
    Ui::MainWindow *ui;
    SerialControl serial_control_;
    XmlEditor xml_editor;
};
#endif // MAINWINDOW_H
