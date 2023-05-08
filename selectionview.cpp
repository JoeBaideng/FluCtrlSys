#include "selectionview.h"
#include<QStandardItemModel>
#include<QHeaderView>
#include<QComboBox>
#include<QDebug>

// 构造函数，初始化数据模型和选择模型，并连接数据改变信号和槽函数
SelectionView::SelectionView(QWidget *parent)
{
    model = new QStandardItemModel();
    model->setRowCount(10);
    model->setParent(parent);
    this->setModel(model);
    // 创建一个 QItemSelectionModel 来管理数据的选择
    QItemSelectionModel *selectionModel = new QItemSelectionModel(model);
    // 连接数据改变信号和槽函数
    connect(model, &QAbstractItemModel::dataChanged, this, &SelectionView::OnDataChanged);
}

// 设置表头
void SelectionView::SetHeaders(const QStringList headers)
{
    model->setHorizontalHeaderLabels(headers);
}

// 设置行数
void SelectionView::SetRowCount(int count)
{
    model->setRowCount(count);
}

// 初始化表格视图
void SelectionView::InitView(EOCMap map)
{
    eoc_map_ = map;
    combo_dele_1 = new ComboDelegate(eoc_map_.equip_names, this, model);
    combo_dele_2 = new ComboDelegate(this, model);
    read_only_dele = new ReadOnlyDelegate(this);
    spin_dele = new SpinDelegate();

    this->setItemDelegateForColumn(0, combo_dele_1); // 第一列使用 combo_dele_1 委托
    this->setItemDelegateForColumn(1, combo_dele_2); // 第二列使用 combo_dele_2 委托
    this->setItemDelegateForColumn(3, spin_dele); // 第四列使用 spin_dele 委托

    this->setEditTriggers(QAbstractItemView::AllEditTriggers);// 可进行单击编辑
    this->setSelectionBehavior(QAbstractItemView::SelectRows);// 选择整行
    this->setSelectionMode(QAbstractItemView::SingleSelection); // 只能选择一行
    this->setContextMenuPolicy(Qt::CustomContextMenu); // 可弹出右键菜单
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);// 自适应列宽
}

// 获取指定行、指定列的数据
QString SelectionView::GetData(const int row, const int col)
{
    QString data = model->data(model->index(row, col)).toString();
    return data;
}

// 整理得到代码串和持续时间，而后交给主窗口去发送给串口
QList<QPair<QString, float>> SelectionView::GetCodeAndTime()
{
    QList<QPair<QString, float>> data;
    int row_count = model->rowCount();
    for (int i = 0; i < row_count; i++)
    {
        if (RowFull(i))
        {
            float time = GetData(i,3).toFloat();
            QString parameter = model->data(model->index(i, 2)).toString();
            QString orderName = model->data(model->index(i, 1)).toString();
            QString code = eoc_map_.order_code_map[orderName];
            code[9] = parameter[0];
            code[10] = parameter[1];
            code[12] = parameter[2];
            code[13] = parameter[3];
            code.remove(QRegExp("\\s"));
            GetIdentifyingCode(code);
            qDebug()<<"code is: "<<code;
            QPair<QString, float> pair(code, time);
            data.append(pair);
        }
    }
    return data;
}

// 判断一行是否都有数据
bool SelectionView::RowFull(int row)
{
    int col_count = 4;
    for (int col = 0; col < col_count; col++)
    {
        QString data = GetData(row, col);
        if (data.isEmpty())
        {
            return false;
        }
    }
    return true;
}

// 反转两个字节
QString SelectionView::Invert_16(QString a)
{
    if(a.size() != 4) return a;
    QString b = a;
    b[0] = a[2];
    b[1] = a[3];
    b[2] = a[0];
    b[3] = a[1];
    return b;
}

// 获取数据的验证码并更新到原来的指令码中
void SelectionView::GetIdentifyingCode(QString &inst_code)
{
    int n = inst_code.size() / 2;
    QString str[n-2];
    int temp[n-2];
    int result = 0;
    QString IDCode;
    bool ok;
    for (int i = 0; i < n - 2; ++i)
    {
        str[i] += inst_code[2 * i];
        str[i] += inst_code[2 * i + 1];
        temp[i] = str[i].toInt(&ok, 16);
        result += temp[i];
    }
    IDCode = QString("%1").arg(result, 4, 16, QLatin1Char('0'));
    IDCode = Invert_16(IDCode);
    inst_code.replace(inst_code.size() - 4, 4, IDCode);
}

// 数据改变的槽函数
void SelectionView::OnDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    if(topLeft == bottomRight && topLeft.column() == 0)
    {
        // 获取该单元格的设备名称
        const QString equip = model->data(topLeft).toString();
        // 获取该设备对应的指令列表
        const QStringList orders = eoc_map_.equip_orders_map[equip];

        // 获取当前单元格的编辑器（也就是下拉框）
        if (!isPersistentEditorOpen(model->index(topLeft.row(), 1)))
        {
            this->openPersistentEditor(model->index(topLeft.row(), 1));
        }
        QWidget *editor = this->indexWidget(model->index(topLeft.row(), 1));

        bool isCombo = editor != NULL && qobject_cast<QComboBox *>(editor) != nullptr;
        if (isCombo)
        {
            // 如果编辑器是下拉框，则进行类型转换，并获取对应的模型
            QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
            QStandardItemModel *comboModel = qobject_cast<QStandardItemModel*>(comboBox->model());

            // 清空原有的下拉框选项
            comboModel->clear();
            // 添加新的选项
            foreach (const QString &order, orders) {
                comboModel->appendRow(new QStandardItem(order));
            }


        }
    }
}
