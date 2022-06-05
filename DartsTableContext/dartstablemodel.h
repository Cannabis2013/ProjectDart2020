#ifndef DARTSTABLEMODEL_H
#define DARTSTABLEMODEL_H

#include <QAbstractTableModel>
#include "DartsTableContext/LinkedList/linkedlist.h"
#include "DartsTableContext/TableSectionsSLAs/itablesectioncontext.h"
#include "DartsTableContext/dartstableslas.h"

class DartsTableModel : public DartsTableSLAs
{
    Q_OBJECT
public:
    DartsTableModel();
    Q_PROPERTY(int initalValue READ initialValue WRITE setInitialValue NOTIFY initialValueChanged);
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged);
    Q_PROPERTY(int minimumColumnCount READ minimumColumnCount WRITE setMinimumColumnCount NOTIFY minimumColumnCountChanged);
    // public exposed methods
    Q_INVOKABLE bool insertData(const int &row, const int &score);
    Q_INVOKABLE bool removeLastItem(const int &row);
    Q_INVOKABLE void clearData();
    Q_INVOKABLE QVariantList columnData(const int &column) const;
    Q_INVOKABLE QVariantList rowData(const int &row) const;
    // Public non-exposed methods
    int rowCount(const QModelIndex &index = QModelIndex()) const override;
    int columnCount(const QModelIndex &index = QModelIndex()) const override;
    void setInitialValue(int newInitialValue);
    int initialValue() const;
signals:
    void columnCountChanged();
    void minimumColumnCountChanged();
    void minimumRowCountChanged();
    void initialValueChanged();
protected:
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole) override;
    bool insertRows(int row, int count, const QModelIndex &) override;
    bool insertColumns(int column, int count, const QModelIndex &) override;
    bool removeRows(int row, int count, const QModelIndex &) override;
    bool removeColumns(int column, int count, const QModelIndex &) override;
private slots:
    void updateInitialCellValues();
private:
    void setColumnCount(const int &count);
    int minimumColumnCount() const;
    void setMinimumColumnCount(int minimumColumnCount);
    // Assistance methods
    void removeColumnsIfNecessary(const int &column);
    void createRowsAndColumns(const QModelIndex &index, const int &delta = 1);
    // Scores and points
    bool removeData(const QModelIndex &index);
};
#endif // CUSTOMTABLEMODEL_H
