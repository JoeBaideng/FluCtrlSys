#ifndef READONLYDELEGATE_H
#define READONLYDELEGATE_H

#include <QObject>
#include <QWidget>
#include<QItemDelegate>
class ReadOnlyDelegate:public QItemDelegate
{
    Q_OBJECT
public:
    ReadOnlyDelegate();
    ReadOnlyDelegate(QWidget *parent = NULL):QItemDelegate(parent)
    {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const override;
};

#endif // READONLYDELEGATE_H
