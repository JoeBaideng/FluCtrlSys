#ifndef XMLEDITOR_H
#define XMLEDITOR_H
#include<QFile>
#include<QDomDocument>
#include <QObject>
#include<QMap>
#include<QStringList>
#include<QString>
#include"mystructs.h"
class XmlEditor : public QObject
{
    Q_OBJECT
public:
    explicit XmlEditor(QObject *parent = nullptr);
    EOCMap ReadFile(QString path);

private:
    bool OpenFile(QString path,QDomDocument &doc);
signals:

};

#endif // XMLEDITOR_H
