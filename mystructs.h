#ifndef SERIALPARAMETER_H
#define SERIALPARAMETER_H
#include<QString>
#include<QMap>
#include<QStringList>

/*
 * 这个头文件用来存放一些结构体，方便不同的类调用
 *
 * */
//串口的各项参数，作为结构体
struct SerialSet
{
    QString port_name;//串口名
    QString baud_rate;//波特率
    QString data_bit;//数据位
    QString stop_bit;//停止位
    int parity_check;//奇偶校验
    QString flu_control;//流控制
};
//设备-命令以及命令-代码的k-v图，这种对应关系会在装载下拉框选项中用到
struct EOCMap
{
    QStringList equip_names;
    QMap<QString,QStringList> equip_orders_map;
    QMap<QString,QString> order_code_map;
};

#endif // SERIALPARAMETER_H
