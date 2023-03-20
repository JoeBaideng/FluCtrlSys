#include "selectionview.h"
#include<QStandardItemModel>
SelectionView::SelectionView(QWidget *parent)
{
    model=new QStandardItemModel();
    model->setRowCount(10);
    model->setParent(parent);
    this->setModel(model);
    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);


}

//设置表头
void SelectionView::SetHeaders(const QStringList headers)
{
    model->setHorizontalHeaderLabels(headers);
}

void SelectionView::SetRowCount(int count)
{
    model->setRowCount(count);
}
