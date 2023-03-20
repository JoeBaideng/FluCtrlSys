#include "combodelegate.h"
#include<QComboBox>
/*
 * 下拉框代理
 * */
ComboDelegate::ComboDelegate(QObject *parent)
{

}
/*************可以通过构造函数初始化下拉框列表*************/
ComboDelegate::ComboDelegate(QStringList strList,QObject*parent):QStyledItemDelegate(parent)
{
    _strList=strList;
}
QWidget *ComboDelegate:: createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/)const
{
    QComboBox*editor=new QComboBox(parent);
    editor->addItems(_strList);
    editor->installEventFilter(const_cast<ComboDelegate*>(this));
    return editor;
}

void ComboDelegate::setEditorData(QWidget *editor, const QModelIndex &index)const
{
    QString str=index.model()->data(index).toString();
    QComboBox*box=static_cast<QComboBox*>(editor);
    int i=box->findText(str);
    box->setCurrentIndex(i);
}
void ComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index)const
{
    QComboBox*box=static_cast<QComboBox*>(editor);
    QString str=box->currentText();
    model->setData(index,str);
}
void ComboDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index)const
{
    editor->setGeometry(option.rect);
}

void ComboDelegate::setComboItems(QStringList list)
{
    _strList=list;
}
