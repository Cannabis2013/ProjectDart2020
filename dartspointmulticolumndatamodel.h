#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QAbstractTableModel>
#include <qfontmetrics.h>
#include "LinkedList.h"
#include "idatamodeltablecellsizes.h"
#include "itablecellstylistics.h"
#include "idatamodeltabledimensions.h"
#include "itableheadercontext.h"
#include "dartspointmulticolumnservices.h"

class DartsPointMultiColumnDataModel :
        public QAbstractTableModel,
        protected DartsPointMultiColumnServices
{
    Q_OBJECT
public:
    // Public types
    typedef QPair<int,int> PointInputModel;
    enum HeaderFillMode{DynamicNumerics = 0x1,
                        FixedStrings = 0x2};
    enum AppendDataMode{SingleAppend = 0x4,
                        MultiAppend = 0x8};
    // Constructor
    DartsPointMultiColumnDataModel();
    // Public properties
    // Fonts properties
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged);
    // Header properties
    Q_PROPERTY(int headerFontSize READ headerFontSize WRITE setHeaderFontSize NOTIFY headerFontSizeChanged)
    // Columns and rows properties
    Q_PROPERTY(double columnWidthScale READ scale WRITE setScale NOTIFY columnWidthScaleChanged);
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged);
    Q_PROPERTY(int minimumColumnCount READ minimumColumnCount WRITE setMinimumColumnCount NOTIFY minimumColumnCountChanged);
    Q_PROPERTY(int minimumRowCount READ minimumRowCount WRITE setMinimumRowCount NOTIFY minimumRowCountChanged);
    // Data properties
    Q_PROPERTY(int initialValue READ initialValue WRITE setInitialValue NOTIFY initialValueChanged);
    Q_PROPERTY(int attempts READ numberOfAttemps WRITE setNumberOfAttemps NOTIFY numberOfThrowsChanged);
    // public exposed methods
    // Data related
    Q_INVOKABLE bool insertData(const QString &playerName,
                                   const int &point,
                                   const int &score);
    Q_INVOKABLE int editData(const int &row, const int &column, const int &point, const int &score);
    Q_INVOKABLE QVariant getData(const int &row, const int &column, const int &mode);
    Q_INVOKABLE bool removeLastItem(const QString &playerName);
    Q_INVOKABLE void clearData();
    // Header related
    Q_INVOKABLE void appendHeaderItem(const QVariant &data);
    Q_INVOKABLE QString getHeaderData(const int &index, const int &orientation) const;
    Q_INVOKABLE int horizontalHeaderCount() const;
    Q_INVOKABLE int verticalHeaderCount() const;
    Q_INVOKABLE int headerItemCount() const;
    Q_INVOKABLE int preferedHeaderItemWidth() const;
    Q_INVOKABLE void setColumnCount(const int &count);
    Q_INVOKABLE void setRowCount(const int &count);
    // Rows and columns related
    Q_INVOKABLE int rowCount() const;
    Q_INVOKABLE int columnCount() const;
    // Columns and rows exposed methods
    Q_INVOKABLE double columnWidthAt(const int &column) const;
    Q_INVOKABLE double rowHeightAt(const int &row) const;
    Q_INVOKABLE int minimumColumnCount() const;
    Q_INVOKABLE void setMinimumColumnCount(int minimumColumnCount);
    Q_INVOKABLE int minimumRowCount() const;
    Q_INVOKABLE void setMinimumRowCount(int minimumRowCount);
    Q_INVOKABLE int initialValue() const;
    Q_INVOKABLE void setInitialValue(int initialValue);
    Q_INVOKABLE int numberOfAttemps() const;
    Q_INVOKABLE void setNumberOfAttemps(const int &count);
    Q_INVOKABLE double scale() const;
    Q_INVOKABLE void setScale(const double &scale);
    // Public non-exposed methods
    // Header non-exposed methods
    QVector<QString> getVerticalHeaderData() const;
    void setVerticalHeaderData(const QVector<QString> &verticalHeaderData);
    // Columns and rows non-exposed virtual method implementations
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    void setColumnWidthAt(const int &column,const double &w);
    int columnWidthsAt(const int &index) const;
    int headerFontSize() const;
    void setHeaderFontSize(int headerFontSize);
    void setVerticalHeaderStringWidth(double verticalHeaderStringWidth);
signals:
    void fillModeChanged();
    void columnWidthScaleChanged();
    void numberOfThrowsChanged();
    void columnCountChanged();
    void headerOrientationChanged();
    void minimumColumnCountChanged();
    void minimumRowCountChanged();
    void initialValueChanged();
    void fontChanged();
    void scaleChanged();
    void appendModeChanged();
    void headerFontSizeChanged();
protected:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool insertRows(int row, int count, const QModelIndex &) override;
    bool insertColumns(int column, int count, const QModelIndex &) override;
    bool removeRows(int row, int count, const QModelIndex &) override;
    bool removeColumns(int column, int count, const QModelIndex &) override;
private slots:
    void updateInitialCellValues();
private:
    // Assistance methods
    QModelIndex createIndexFromPlayerName(const QString &playerName) const;
    PointInputModel addValue(const QModelIndex &index, const QVariant &value);
    void updateColumnWidth(const QModelIndex &index, const PointInputModel &model);
    void createRowsAndColumns(const QModelIndex &index, const int &delta);
    // Data related
    bool setPlayerData(const QString &playerName, const int &point,const int &score);
    bool isCellDecorated(const QModelIndex &index);
    int indexOfLastDecoratedCell(const int &index) const;
    int rowCount(const int &column);
    bool isColumnEmpty(const int &col);
    bool isRowEmpty(const int &row);
    // Largest vertical header string width
    double _verticalHeaderStringWidth = 64;
    // Column widths
    QList<double> _columnWidths;
    // Scores and points
    QPair<int,int> removeData(const QModelIndex &index);
    QList<LinkedList<PointInputModel>> _data;
};

#endif // CUSTOMTABLEMODEL_H
