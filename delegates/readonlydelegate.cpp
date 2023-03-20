#include "readonlydelegate.h"
/*
 * 只读代理，禁止修改某一列
 * */
ReadOnlyDelegate::ReadOnlyDelegate()
{

}
QWidget *ReadOnlyDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const //final
{
    Q_UNUSED(parent)
    Q_UNUSED(option)
    Q_UNUSED(index)
    return NULL;
}
