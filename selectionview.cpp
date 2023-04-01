#include "selectionview.h"
#include<QStandardItemModel>
#include<QHeaderView>
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

void SelectionView::InitView(EOCMap map)
{
    eoc_map_=map;
    combo_dele_1=new ComboDelegate(eoc_map_.equip_names);
    combo_dele_2=new ComboDelegate();
    read_only_dele=new ReadOnlyDelegate(this);
    spin_dele=new SpinDelegate();

    this->setItemDelegateForColumn(0,combo_dele_1);
    this->setItemDelegateForColumn(1,combo_dele_2);
    this->setItemDelegateForColumn(3,spin_dele);

    this->setSelectionBehavior(QAbstractItemView::SelectRows); //选择整行
    this->setSelectionMode(QAbstractItemView::SingleSelection); //只选择一行
    this->setContextMenuPolicy(Qt::CustomContextMenu); //可弹出右键菜单
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
}
