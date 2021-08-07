#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QAbstractTableModel>
#include "linkedlist.h"
#include "itablecontext.h"
#include "dartspointmulticolumnservices.h"

class DartsPointMultiColumnDataModel :
        public QAbstractTableModel,
        protected DartsPointMultiColumnServices
{
    Q_OBJECT
public:
    // Constructor
    DartsPointMultiColumnDataModel();
    // Public properties
    // Fonts properties
    // Columns and rows properties
    Q_PROPERTY(int initalValue WRITE setInitialValue NOTIFY initialValueChanged);
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged);
    Q_PROPERTY(int minimumColumnCount READ minimumColumnCount WRITE setMinimumColumnCount NOTIFY minimumColumnCountChanged);
    Q_PROPERTY(int minimumRowCount READ minimumRowCount WRITE setMinimumRowCount NOTIFY minimumRowCountChanged);
    // public exposed methods
    // Data related
    Q_INVOKABLE bool insertData(const int &indexOfPlayer,
                                const int &point,
                                const int &score);
    Q_INVOKABLE bool removeLastItem(const int &indexOfPlayer);
    Q_INVOKABLE void clearData();
    // Header related
    Q_INVOKABLE void setColumnCount(const int &count);
    Q_INVOKABLE void setRowCount(const int &count);
    // Rows and columns related
    Q_INVOKABLE int rowCount() const;
    Q_INVOKABLE int columnCount() const;
    // Columns and rows exposed methods
    Q_INVOKABLE int minimumColumnCount() const;
    Q_INVOKABLE void setMinimumColumnCount(int minimumColumnCount);
    Q_INVOKABLE int minimumRowCount() const;
    Q_INVOKABLE void setMinimumRowCount(int minimumRowCount);
    // Public non-exposed methods
    // Header non-exposed methods
    // Columns and rows non-exposed virtual method implementations
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    void setInitialValue(int newInitialValue);
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
    void replaceValue(const QModelIndex &index, const PointInputModel &model, DataRows &data);
    QModelIndex createIndexFromPlayerName(const int &indexOfplayer) const;
    PointInputModel addValue(const QModelIndex &index, const QVariant &value);
    void createRowsAndColumns(const QModelIndex &index, const int &delta = 1);
    // Data related
    bool setPlayerData(const int &indexOfPlayer, const int &point, const int &score);
    bool isCellDecorated(const QModelIndex &index);
    int indexOfLastDecoratedCell(const int &index) const;
    int rowCount(const int &column);
    bool isColumnEmpty(const int &col);
    bool isRowEmpty(const int &row);
    // Scores and points
    bool removeData(const QModelIndex &index);
};

#endif // CUSTOMTABLEMODEL_H
