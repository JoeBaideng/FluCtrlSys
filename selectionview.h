#ifndef SELECTIONVIEW_H
#define SELECTIONVIEW_H

#include <QObject>
#include<QWidget>
#include<QTableView>
#include<QStandardItemModel>
#include"mystructs.h"
#include"delegates/combodelegate.h"
#include"delegates/readonlydelegate.h"
#include"delegates/spindelegate.h"
class SelectionView : public QTableView
{
    Q_OBJECT
public:
    SelectionView(QWidget *parent = nullptr);
    void SetHeaders(const QStringList headers);
    void SetRowCount(int count);
    void InitView(EOCMap map);
    QString GetData(const int row,const int col);
    QList<QPair<QString,float>> GetCodeAndTime();
private:
    EOCMap eoc_map_;
    QStandardItemModel *model;
    ComboDelegate*combo_dele_1;
    ComboDelegate*combo_dele_2;
    ReadOnlyDelegate*read_only_dele;
    SpinDelegate*spin_dele;
private:
    bool RowFull(int row);
    QString Invert_16(QString a);
    void GetIdentifyingCode(QString &inst_code);
private slots:
    void OnDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
};

#endif // SELECTIONVIEW_H
