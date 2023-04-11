#include "selectionview.h"
#include<QStandardItemModel>
#include<QHeaderView>
#include<QComboBox>
#include<QDebug>
SelectionView::SelectionView(QWidget *parent)
{
    model=new QStandardItemModel();
    model->setRowCount(10);
    model->setParent(parent);
    this->setModel(model);
    QItemSelectionModel *selectionModel=new QItemSelectionModel(model);
    connect(model, &QAbstractItemModel::dataChanged, this, &SelectionView::OnDataChanged);

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
    combo_dele_1=new ComboDelegate(eoc_map_.equip_names,this,model);
    combo_dele_2=new ComboDelegate(this,model);
    read_only_dele=new ReadOnlyDelegate(this);
    spin_dele=new SpinDelegate();

    this->setItemDelegateForColumn(0,combo_dele_1);
    this->setItemDelegateForColumn(1,combo_dele_2);
    this->setItemDelegateForColumn(3,spin_dele);

    this->setEditTriggers(QAbstractItemView::AllEditTriggers);//单击编辑
    this->setSelectionBehavior(QAbstractItemView::SelectRows); //选择整行
    this->setSelectionMode(QAbstractItemView::SingleSelection); //只选择一行
    this->setContextMenuPolicy(Qt::CustomContextMenu); //可弹出右键菜单
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//自适应列宽
}

QString SelectionView::GetData(const int row, const int col)
{
    QString data=model->data(model->index(row,col)).toString();
    return data;
}
//表格数据发生改变时的响应槽函数
void SelectionView::OnDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    if(topLeft==bottomRight&&topLeft.column()==0)//第一列的数据发送改变
    {
        qDebug()<<topLeft;
        const QString equip=model->data(topLeft).toString();

        const QStringList orders=eoc_map_.equip_orders_map[equip];
        qDebug()<<orders;

        // 获取当前单元格的编辑器（也就是下拉框）
        if(!isPersistentEditorOpen(model->index(topLeft.row(), 1)))
        {
            this->openPersistentEditor(model->index(topLeft.row(), 1));
        }
        QWidget *editor = this->indexWidget(model->index(topLeft.row(), 1));
        qDebug()<<model->index(topLeft.row(), 1);

        bool isCombo=editor != NULL && qobject_cast<QComboBox *>(editor) != nullptr;
        qDebug()<<isCombo;
        if (isCombo)
        {
            // 如果编辑器是下拉框，则进行类型转换，并获取对应的模型
            QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
            QStandardItemModel *comboModel = qobject_cast<QStandardItemModel*>(comboBox->model());

            // 调用 clear 方法清空原有的下拉框选项
            comboModel->clear();
            // 添加新的选项
            foreach (const QString &order, orders) {
                comboModel->appendRow(new QStandardItem(order));
            }
        }
    }
}
