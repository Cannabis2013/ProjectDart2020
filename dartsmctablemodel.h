#ifndef DARTSMCTABLEMODEL_H
#define DARTSMCTABLEMODEL_H

#include <QAbstractTableModel>
#include "linkedlist.h"
#include "itablecontext.h"
#include "dartspmcservices.h"

/*
 * A method is described as 'exposed' if it's reacheable from any QML context
 */

class DartsMCTableModel :
        public QAbstractTableModel,
        protected DartsPMCServices
{
    Q_OBJECT
public:
    // Constructor
    DartsMCTableModel();
    // Public properties
    // Fonts properties
    // Columns and rows properties
    Q_PROPERTY(int initalValue READ initialValue WRITE setInitialValue NOTIFY initialValueChanged);
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged);
    Q_PROPERTY(int minimumColumnCount READ minimumColumnCount WRITE setMinimumColumnCount NOTIFY minimumColumnCountChanged);
    // public exposed methods
    Q_INVOKABLE bool insertData(const int &indexOfPlayer, const int &point, const int &score);
    Q_INVOKABLE bool removeLastItem(const int &indexOfPlayer);
    Q_INVOKABLE void clearData();
    Q_INVOKABLE void setColumnCount(const int &count);
    Q_INVOKABLE int columnCount() const;
    Q_INVOKABLE int minimumColumnCount() const;
    Q_INVOKABLE void setMinimumColumnCount(int minimumColumnCount);
    Q_INVOKABLE QVariantList columnData(const int &column) const;
    Q_INVOKABLE QVariantList rowData(const int &row) const;
    Q_INVOKABLE int lastDecoratedColumn(const int &indexOfPlayer) const;
    // Public non-exposed methods
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    void setInitialValue(int newInitialValue);
    int initialValue() const;
signals:
    void columnCountChanged();
    void minimumColumnCountChanged();
    void minimumRowCountChanged();
    void initialValueChanged();
protected:
    QVariant data(const QModelIndex &index, int) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool insertRows(int row, int count, const QModelIndex &) override;
    bool insertColumns(int column, int count, const QModelIndex &) override;
    bool removeRows(int row, int count, const QModelIndex &) override;
    bool removeColumns(int column, int count, const QModelIndex &) override;
private slots:
    void updateInitialCellValues();
private:
    // Assistance methods
    void createColumnsIfNecessary(const int &column);
    void replaceValue(const QModelIndex &index, const TableData &model, Rows &data);
    QModelIndex createIndexFromPlayerName(const int &indexOfplayer) const;
    TableData addValue(const QModelIndex &index, const QVariant &value);
    void createRowsAndColumns(const QModelIndex &index, const int &delta = 1);
    int indexOfLastDecoratedCell(const int &row) const;
    // Scores and points
    bool removeData(const QModelIndex &index);
};

#endif // CUSTOMTABLEMODEL_H
