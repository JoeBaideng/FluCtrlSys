#ifndef SIPNDELEGATE_H
#define SIPNDELEGATE_H

#include <QObject>
#include <QWidget>
#include<QStyledItemDelegate>
#include<QSpinBox>
class SpinDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SpinDelegate(QObject*parent=0);
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const ;
    void setEditorData(QWidget *editor, const QModelIndex &index) const ;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const ;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const ;
};

#endif // SIPNDELEGATE_H
