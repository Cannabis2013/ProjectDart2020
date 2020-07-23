#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QAbstractTableModel>
#include <qfontmetrics.h>

const int defaultCellWidth = 25;
const int defaultCellHeight = 25;
const QString defaultFontFamily = "MS Sans Serif";
const int defaultPointSize = 12;

class ScoreDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    // Constructor
    ScoreDataModel();
    // Public types
    enum HeaderFillMode{IncrementingIntegerFill = 0x1, SymbolFill = 0x2, NonFill = 0x4};
    // Public properties
    Q_PROPERTY(int headerFillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged);
    Q_PROPERTY(double columnWidthScale READ scale WRITE setScale NOTIFY columnWidthScaleChanged);
    Q_PROPERTY(int throwCount READ numberOfThrows WRITE setNumberOfThrows NOTIFY numberOfThrowsChanged);
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged);
    Q_PROPERTY(int headerOrientation READ headerOrientation WRITE setHeaderOrientation NOTIFY headerOrientationChanged);
    Q_PROPERTY(int minimumColumnCount READ minimumColumnCount WRITE setMinimumColumnCount NOTIFY minimumColumnCountChanged);
    Q_PROPERTY(int minimumRowCount READ minimumRowCount WRITE setMinimumRowCount NOTIFY minimumRowCountChanged);
    Q_PROPERTY(int initialValue READ initialValue WRITE setInitialValue NOTIFY initialValueChanged);
    // public methods
    Q_INVOKABLE int editData(const int &row, const int &column, const int &data);
    Q_INVOKABLE bool appendData(const QString &playerName, const int &data, const int &headerOrientation = -1);
    Q_INVOKABLE int takeLastItem(const QString &playerName, const int &headerOrientation = -1);
    Q_INVOKABLE void appendHeaderItem(const QVariant &data, const int &headerOrientation = -1);
    Q_INVOKABLE void clearData();
    Q_INVOKABLE QString getHeaderData(const int &index, const int &headerOrientation = -1) const;
    Q_INVOKABLE int headerItemCount(const int &headerOrientation = -1) const;
    Q_INVOKABLE int rowCount() const;
    Q_INVOKABLE int columnCount() const;
    Q_INVOKABLE double columnWidthAt(const int &column, const QString &fontFamily = defaultFontFamily, const int &pointSize = defaultPointSize) const;
    Q_INVOKABLE double columnHeightAt(const int &column, const QString &fontFamily = defaultFontFamily, const int &pointSize = defaultPointSize) const;
    Q_INVOKABLE double rowHeightAt(const int &row, const QString &fontFamily = "MS Sans Serif", const int &pointSize = defaultPointSize) const;
    Q_INVOKABLE double rowWidthAt(const int &row, const QString &fontFamily = "MS Sans Serif", const int &pointSize = defaultPointSize) const;
    Q_INVOKABLE int horizontalHeaderCount() const;
    Q_INVOKABLE int verticalHeaderCount() const;
    Q_INVOKABLE double scale() const;
    Q_INVOKABLE void setScale(double scale);
    Q_INVOKABLE int fillMode() const;
    Q_INVOKABLE void setFillMode(int fillMode);
    Q_INVOKABLE int preferedCellWidth(const QString &fontFamily = defaultFontFamily, const int &pointSize = defaultPointSize) const;
    Q_INVOKABLE void setColumnCount(const int &count);
    // Public pure virtual method implementations
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;

    // Public virtual method implementations
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    Q_INVOKABLE int headerOrientation() const;
    Q_INVOKABLE void setHeaderOrientation(int headerOrientation);

    // Public exposed properties
    Q_INVOKABLE int numberOfThrows() const;
    Q_INVOKABLE void setNumberOfThrows(const int &count);
    Q_INVOKABLE int minimumColumnCount() const;
    Q_INVOKABLE void setMinimumColumnCount(int minimumColumnCount);
    Q_INVOKABLE int minimumRowCount() const;
    Q_INVOKABLE void setMinimumRowCount(int minimumRowCount);
    Q_INVOKABLE int initialValue() const;
    Q_INVOKABLE void setInitialValue(int initialValue);

signals:
    void fillModeChanged();
    void columnWidthScaleChanged();
    void numberOfThrowsChanged();
    void columnCountChanged();
    void headerOrientationChanged();
    void minimumColumnCountChanged();
    void minimumRowCountChanged();
    void initialValueChanged();
protected:
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool insertRows(int row, int count, const QModelIndex &) override;
    bool insertColumns(int column, int count, const QModelIndex &) override;
    bool removeRows(int row, int count, const QModelIndex &) override;
    bool removeColumns(int column, int count, const QModelIndex &) override;
private slots:
    void updateInitialCellValues();
private:
    bool isCellDecorated(const QModelIndex &index);
    int indexOfLastDecoratedCell(const int &index, const int &orientation);
    int rowCount(const int &column);
    bool isColumnEmpty(const int &col);
    bool isRowEmpty(const int &row);
    int removeData(const QModelIndex &index);
    int indexOfHeaderItem(const QString &data, const int &orientation);
    QList<QList<int>> _cellData;
    QList<QString> _verticalHeaderData;
    QList<QString> _horizontalHeaderData;
    int _rows = 0;
    int _columns = 0;
    double _scale = 1.05;
    int _fillMode = HeaderFillMode::NonFill;
    int _numberOfThrows = 3;
    int _headerOrientation = 0x2;
    int _minimumColumnCount = 0;
    int _minimumRowCount = 0;
    int _initialValue = 0;
};

#endif // CUSTOMTABLEMODEL_H
