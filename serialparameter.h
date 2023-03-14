#ifndef SERIALPARAMETER_H
#define SERIALPARAMETER_H
#include<QString>
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

#endif // SERIALPARAMETER_H
