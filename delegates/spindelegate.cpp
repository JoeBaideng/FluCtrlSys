#include "spindelegate.h"
#include<QSpinBox>
#include<QDoubleSpinBox>
/*
 * 数字代理
 * */
SpinDelegate::SpinDelegate(QObject*parent)
{

}
QWidget *SpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/*option*/, const QModelIndex &/*index*/) const
{
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setMinimum(0);
    //editor->setMaximum(100);
    //editor->setSingleStep(0.1);
    return editor;
}
void SpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
}
void SpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                  const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    int value = spinBox->value();
    model->setData(index, value, Qt::EditRole);
}
void SpinDelegate::updateEditorGeometry(QWidget *editor,
                          const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
