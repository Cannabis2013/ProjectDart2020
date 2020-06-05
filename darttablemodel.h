#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QAbstractTableModel>
#include <qfontmetrics.h>

class DartTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    DartTableModel();


    // public methods


    Q_INVOKABLE bool appendData(int row, int column, int data);
    Q_INVOKABLE void appendHeaderItem(const QVariant &data, const int &orientation = Qt::Vertical);

    Q_INVOKABLE QString headerData(int index, int orientation) const;

    Q_INVOKABLE int rowCount() const;
    Q_INVOKABLE int columnCount() const;

    Q_INVOKABLE int columnWithAt(const int &column, const QString &fontFamily = "MS Sans Serif", const int &pointSize = 12) const;

    Q_INVOKABLE int rowHeightAt(const int &row, const QString &fontFamily = "MS Sans Serif", const int &pointSize = 12) const;
    // Pure virtual implementations
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    // Virtual implementations
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool insertRows(int row, int count, const QModelIndex &) override;
    bool insertColumns(int column, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &) override;
    bool removeColumns(int column, int count, const QModelIndex &) override;

private:

    int lastDecoratedCellIndex(int row);

    QList<QList<int>> _cellData;
    QList<QString> _verticalHeaderData;
    QList<QString> _horizontalHeaderData;

    int _rows = 0;
    int _columns = 0;

public:
};

#endif // CUSTOMTABLEMODEL_H
