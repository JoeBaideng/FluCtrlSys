#ifndef COMBODELEGATE1_H
#define COMBODELEGATE1_H

#include <QObject>
#include <QWidget>
#include<QStyledItemDelegate>
#include<QStringList>

class ComboDelegate:public QStyledItemDelegate
{
    Q_OBJECT
public:
    ComboDelegate(QObject*parent=0);
    ComboDelegate(QStringList strList,QObject*parent=0);
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const ;
    void setEditorData(QWidget *editor, const QModelIndex &index) const ;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const ;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const ;
    void setComboItems(QStringList list);
private:
    QStringList _strList;
};

#endif // COMBODELEGATE1_H
