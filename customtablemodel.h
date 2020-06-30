#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QAbstractTableModel>
#include <qfontmetrics.h>

const int defaultCellWidth = 25;
const int defaultCellHeight = 25;
const QString defaultFontFamily = "MS Sans Serif";
const int defaultPointSize = 12;

class CustomTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:

    // Public types
    enum HeaderFillMode{IncrementingIntegerFill = 0x1, SymbolFill = 0x2, NonFill = 0x4};

    Q_PROPERTY(int headerFillMode READ fillMode WRITE setFillMode NOTIFY fillModeChanged);
    Q_PROPERTY(double columnWidthScale READ scale WRITE setScale NOTIFY columnWidthScaleChanged);

    CustomTableModel();

    // public methods
    Q_INVOKABLE bool appendData(int row, int column, int data);
    Q_INVOKABLE void appendHeaderItem(const QVariant &data, const int &orientation = Qt::Vertical);

    Q_INVOKABLE QString headerData(const int &index, const int &orientation) const;

    Q_INVOKABLE int headerItemCount(const int &orientation) const;

    Q_INVOKABLE int rowCount() const;
    Q_INVOKABLE int columnCount() const;

    Q_INVOKABLE double columnWithAt(const int &column, const QString &fontFamily = defaultFontFamily, const int &pointSize = defaultPointSize) const;
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

    // Public pure virtual method implementations
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    // Public virtual method implementations
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

signals:
    void fillModeChanged();
    void columnWidthScaleChanged();

protected:
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    bool insertRows(int row, int count, const QModelIndex &) override;
    bool insertColumns(int column, int count, const QModelIndex &) override;
    bool removeRows(int row, int count, const QModelIndex &) override;
    bool removeColumns(int column, int count, const QModelIndex &) override;

private:
    int lastDecoratedCellIndex(int row);

    QList<QList<int>> _cellData;

    QList<QString> _verticalHeaderData;
    QList<QString> _horizontalHeaderData;

    int _rows = 0;
    int _columns = 0;
    double _scale = 1.05;

    int _fillMode = HeaderFillMode::NonFill;
};

#endif // CUSTOMTABLEMODEL_H
