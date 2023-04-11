#include "combodelegate.h"
#include<QComboBox>
#include<QLineEdit>
#include<QListView>
/*
 * 下拉框代理
 * */
ComboDelegate::ComboDelegate(QObject *parent,QAbstractItemModel *model):QStyledItemDelegate(parent),_model(model)
{

}
/*************可以通过构造函数初始化下拉框列表*************/
ComboDelegate::ComboDelegate(QStringList strList,QObject*parent,QAbstractItemModel *model):QStyledItemDelegate(parent),_model(model)
{
    _strList=strList;
}
QWidget *ComboDelegate:: createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/)const
{
    QComboBox*editor=new QComboBox(parent);
    // 将编辑模式设置为 InstantPopup
    editor->setEditable(true);
    editor->lineEdit()->setReadOnly(true);
//    editor->setView(new QListView(editor));
//    editor->setModel(_model);
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
