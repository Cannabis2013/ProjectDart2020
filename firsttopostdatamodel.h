#ifndef CUSTOMTABLEMODEL_H
#define CUSTOMTABLEMODEL_H

#include <QAbstractTableModel>
#include <qfontmetrics.h>

const int defaultCellWidth = 25;
const int defaultCellHeight = 25;
const QString defaultFontFamily = "MS Sans Serif";
const int defaultPointSize = 12;

typedef QPair<int,int> scoreModel;

/*
 * Orientation:
 *  - The datamodel orientation is based on the axis for which player names are listed
 */

class FirstToPostDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    // Public types
    enum HeaderFillMode{DynamicNumerics = 0x1,
                        FixedStrings = 0x2};
    enum AppendDataMode{SingleAppend = 0x4,
                        MultiAppend = 0x8};
    // Constructor
    FirstToPostDataModel();
    // Public properties
    // Fonts properties
    Q_PROPERTY(int scoreFontPointSize READ scoreFontSize WRITE setScoreFontSize NOTIFY fontChanged);
    Q_PROPERTY(int pointFontPointSize READ pointFontSize WRITE setPointFontSize NOTIFY fontChanged);
    Q_PROPERTY(QString scoreFontFamily READ scoreFontFamily WRITE setScoreFontFamily NOTIFY fontChanged);
    Q_PROPERTY(QString pointFontFamily READ pointFontFamily WRITE setPointFontFamily NOTIFY fontChanged);
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged);
    // Header properties
    Q_PROPERTY(int verticalFillMode READ verticalHeaderFillMode WRITE setVerticalHeaderFillMode NOTIFY fillModeChanged);
    Q_PROPERTY(int horizontalFillMode READ horizontalHeaderFillMode WRITE setHorizontalHeaderFillMode NOTIFY fillModeChanged);
    Q_PROPERTY(int headerOrientation READ headerOrientation WRITE setHeaderOrientation NOTIFY headerOrientationChanged);
    // Columns and rows properties
    Q_PROPERTY(double columnWidthScale READ scale WRITE setScale NOTIFY columnWidthScaleChanged);
    Q_PROPERTY(int columnCount READ columnCount WRITE setColumnCount NOTIFY columnCountChanged);
    Q_PROPERTY(int minimumColumnCount READ minimumColumnCount WRITE setMinimumColumnCount NOTIFY minimumColumnCountChanged);
    Q_PROPERTY(int minimumRowCount READ minimumRowCount WRITE setMinimumRowCount NOTIFY minimumRowCountChanged);
    // Data properties
    Q_PROPERTY(int appendMode READ appendMode WRITE setAppendMode NOTIFY appendModeChanged);
    Q_PROPERTY(int initialValue READ initialValue WRITE setInitialValue NOTIFY initialValueChanged);
    Q_PROPERTY(int throwCount READ numberOfThrows WRITE setNumberOfThrows NOTIFY numberOfThrowsChanged);
    // public exposed methods
    // Data related
    Q_INVOKABLE QVariant getData(const int &row, const int &column, const int &mode);
    Q_INVOKABLE int editData(const int &row, const int &column, const int &point, const int &score);
    Q_INVOKABLE bool insertData(const QString &playerName,
                                   const int &point,
                                   const int &score);
    Q_INVOKABLE bool removeLastItem(const QString &playerName,
                                    const int &headerOrientation = -1);
    Q_INVOKABLE void clearData();
    // Header related
    Q_INVOKABLE void appendHeaderItem(const QVariant &data, const int &headerOrientation = -1);
    Q_INVOKABLE QString getHeaderData(const int &index, const int &headerOrientation = -1) const;
    Q_INVOKABLE int horizontalHeaderCount() const;
    Q_INVOKABLE int verticalHeaderCount() const;
    Q_INVOKABLE int headerItemCount(const int &headerOrientation = -1) const;
    Q_INVOKABLE int preferedHeaderItemWidth(const int &orientation = Qt::Vertical) const;
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

    // Public virtual method implementations
    Q_INVOKABLE int headerOrientation() const;
    Q_INVOKABLE void setHeaderOrientation(int headerOrientation);
    Q_INVOKABLE int numberOfThrows() const;
    Q_INVOKABLE void setNumberOfThrows(const int &count);

    // Public non-exposed methods
    // Font non-exposed methods
    double scale() const;
    void setScale(double scale);
    int scoreFontSize() const;
    void setScoreFontSize(int scoreFontSize);
    int pointFontSize() const;
    void setPointFontSize(int pointFontSize);
    QString scoreFontFamily() const;
    void setScoreFontFamily(const QString &scoreFontFamily);
    QString pointFontFamily() const;
    void setPointFontFamily(const QString &pointFontFamily);

    int currentVerticalHeaderItemWidth() const;
    int currentHorizontalHeaderItemWidth() const;

    void setCurrentHorizontalHeaderItemWidth(int currentHorizontalHeaderItemWidth);
    void setCurrentVerticalHeaderItemWidth(int currentVerticalHeaderItemWidth);
    // Header non-exposed methods
    int horizontalHeaderFillMode() const;
    int verticalHeaderFillMode() const;
    void setHorizontalHeaderFillMode(const int &fillMode);
    void setVerticalHeaderFillMode(const int &fillMode);
    QStringList getVerticalHeaderData() const;
    void setVerticalHeaderData(const QList<QString> &verticalHeaderData);
    QStringList getHorizontalHeaderData() const;
    void setHorizontalHeaderData(const QList<QString> &horizontalHeaderData);
    // Data non-exposed methods
    int appendMode() const;
    void setAppendMode(int appendMode);
    // Columns and rows non-exposed virtual method implementations
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    void setColumnWidthAt(const int &column,const double &w);

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
    // Data related
    bool setPlayerData(const QString &playerName,
                       const int &point,
                       const int &score,
                       const int &headerOrientation = -1);
    bool appendPlayerData(const QString &playerName,
                                      const int &point,
                                      const int &score,
                                      const int &headerOrientation = -1);
    bool isCellDecorated(const QModelIndex &index);
    int indexOfLastDecoratedCell(const int &index, const int &orientation);
    int rowCount(const int &column);
    bool isColumnEmpty(const int &col);
    bool isRowEmpty(const int &row);
    QPair<int,int> removeData(const QModelIndex &index);
    int indexOfHeaderItem(const QString &data, const int &orientation);
    /*
     * Font metrics related
     */
    QRect stringWidth(const QString &string,
                      const QString &family = "",
                      const int &pointSize = -1) const;
    // State member variables
    // Data
    int _appendMode = AppendDataMode::MultiAppend;
    /*
     * Row and column fields
     */
    int _rows = 0;
    int _columns = 0;
    double _scale = 1.05;
    int _horizontalFillMode = HeaderFillMode::DynamicNumerics;
    int _verticalFillMode = HeaderFillMode::FixedStrings;
    int _numberOfThrows = 3;
    int _headerOrientation = 0x2;
    int _minimumColumnCount = 0;
    int _minimumRowCount = 0;
    int _initialValue = 0;

    /*
     * Font related
     *  - Score/point font size
     *  - Score/point font family
     */
    int _scoreFontSize = 12;
    int _pointFontSize = 8;

    QString _scoreFontFamily = "MS Sans Serif";
    QString _pointFontFamily = "MS Sans Serif";
    /*
     * Headerdata
     */
    QStringList _verticalHeaderData;
    QStringList _horizontalHeaderData;

    int _currentVerticalHeaderItemWidth = 0;
    int _currentHorizontalHeaderItemWidth = 0;
    /*
     * Column widths
     */
    QList<double> _columnWidths;
    /*
     * Scores and points
     */
    QList<QList<scoreModel>> _data;
};

#endif // CUSTOMTABLEMODEL_H