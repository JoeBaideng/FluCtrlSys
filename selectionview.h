#ifndef SELECTIONVIEW_H
#define SELECTIONVIEW_H

#include <QObject>
#include<QWidget>
#include<QTableView>
#include<QStandardItemModel>
class SelectionView : public QTableView
{
    Q_OBJECT
public:
    SelectionView(QWidget *parent = nullptr);
    void SetHeaders(const QStringList headers);
    void SetRowCount(int count);
private:
    QStandardItemModel *model;

};

#endif // SELECTIONVIEW_H
