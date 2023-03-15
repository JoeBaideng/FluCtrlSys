#include "xmleditor.h"
#include<QFile>
#include<QMessageBox>
#include"mystructs.h"
#include<QDebug>
XmlEditor::XmlEditor(QObject *parent) : QObject(parent)
{

}

//打开一个文件，生成DOM树
bool XmlEditor::OpenFile(QString path, QDomDocument &doc)
{
    QFile file(path);
    if (!file.open(QFileDevice::ReadOnly)) {
        QMessageBox::information(NULL, "提示", "文件打开失败！");
        return false;
    }

    if (!doc.setContent(&file)) {
        QMessageBox::information(NULL, "提示", "操作的文件不是XML文件！");
        file.close();
        return false;
    }
    return true;
}

EOCMap XmlEditor::ReadFile(QString path)
{
    EOCMap eoc_map;
    QDomDocument doc;
    if(OpenFile(path,doc));
    {
        // 获得根节点
        QDomElement root = doc.documentElement();
        qDebug() << "根节点：" << root.nodeName();
        // 获取所有Equipment节点
        QDomNodeList equip_list = root.elementsByTagName("Equipment");

        /* 获取属性中的值 */
        for (int i = 0; i < equip_list.count(); i++)
        {
            // 获取链表中的值
            QDomElement element = equip_list.at(i).toElement();
            QString equip_name=element.attribute("name");
            QStringList order_list_str;

            QDomNodeList order_list=element.elementsByTagName("Order");
            for(int j=0;j<order_list.count();j++)
            {
                QDomElement order=order_list.at(j).toElement();//每个设备下的命令，属性包括名称和代码
                QString order_name=order.attribute("name");//拉取名称
                QString order_code=order.attribute("code");//拉取代码
                order_list_str.push_back(order_name);//将名称汇总到这台设备名下，生成e_o图
                eoc_map.order_code_map.insert(order_name,order_code);//将命令名称与代码一一对应，生成o_c图

            }
            eoc_map.equip_orders_map.insert(equip_name,order_list_str);//将设备名与该设备的命令列表对应
        }
    }

    return eoc_map;
}


