#include "mainwindow.h"
#include <QApplication>

/**
 * 整体遵循谷歌代码风格
 * 类以大写开头命名，例如："Analyzer", "FastVector"
 * 函数名应当使用"动词"或者"动词＋名词"（动宾词组）的形式。例如："GetName()", "SetValue()",
 * "Erase()", "Reserve()" ....
 * 变量用下划线链接命名
 * const以k开头
 **/

int main(int argc, char *argv[]) {
  QApplication a(argc, argv); // 创建一个应用程序对象
  MainWindow w; // 创建一个主窗口对象
  w.show(); // 显示主窗口
  return a.exec(); // 执行应用程序
}
