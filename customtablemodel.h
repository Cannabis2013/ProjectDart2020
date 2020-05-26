#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QAbstractTableModel>

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CustomTableModel();

    // public methods

    Q_INVOKABLE void appendData(int row, int column, int data);

    // Pure virtual implementations
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    // Virtual implementations
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool insertRows(int row, int count, const QModelIndex &) override;
    bool insertColumns(int column, int count, const QModelIndex &parent) override;

private:

    int lastDecoratedCellIndex(int row);

    QList<QList<int>> _cellData;
    QList<QString> _horizontalHeader;
    QList<QString> _verticalHeader;

    int _rows = 0;
    int _columns = 0;
};

#endif // CUSTOMTABLEMODEL_H
