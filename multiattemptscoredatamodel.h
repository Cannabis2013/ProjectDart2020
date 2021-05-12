#ifndef HORIZONTALFTPSINGLEDATAMODEL_H
#define HORIZONTALFTPSINGLEDATAMODEL_H

#include <QAbstractTableModel>
#include <qfontmetrics.h>
#include "LinkedList.h"

class MultiAttemptScoreDataModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    // Public types
    typedef QPair<int,int> scoreModel;
    enum HeaderFillMode{
        DynamicNumerics = 0x1,
        FixedStrings = 0x2,
        NoFillMode = 0x3
    };
    // Constructor
    // Public properties
    // Fonts properties
    Q_PROPERTY(int scoreFontPointSize READ scoreFontSize WRITE setScoreFontSize NOTIFY fontChanged);
    Q_PROPERTY(int pointFontPointSize READ pointFontSize WRITE setPointFontSize NOTIFY fontChanged);
    Q_PROPERTY(QString scoreFontFamily READ scoreFontFamily WRITE setScoreFontFamily NOTIFY fontChanged);
    Q_PROPERTY(QString pointFontFamily READ pointFontFamily WRITE setPointFontFamily NOTIFY fontChanged);
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged);
    // Header properties
    Q_PROPERTY(int horizontalFillMode READ horizontalHeaderFillMode WRITE setHorizontalHeaderFillMode NOTIFY fillModeChanged);
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
                                const int &score);
    Q_INVOKABLE int editData(const int &row, const int &column, const int &point, const int &score);
    Q_INVOKABLE bool removeLastItem(const QString &playerName);
    Q_INVOKABLE void clearData();
    // Header related
    Q_INVOKABLE void appendHeaderItem(const QVariant &data);
    Q_INVOKABLE QString getHeaderData(const int &index) const;
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
    /*
     * Public virtual method implementations
     *  - Header orientation
     *  - Number of row/column increment
     */
    Q_INVOKABLE int numberOfAttemps() const;
    Q_INVOKABLE void setNumberOfAttemps(const int &count);
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
    // Header non-exposed methods
    int horizontalHeaderFillMode() const;
    void setHorizontalHeaderFillMode(const int &fillMode);
    QStringList getVerticalHeaderData() const;
    void setVerticalHeaderData(const QList<QString> &horizontalHeaderData);
    // Columns and rows non-exposed virtual method implementations
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    void setColumnWidthAt(const int &column,const double &w);
    int columnWidthsAt(const int &index) const;
    int headerFontSize() const;
    void setHeaderFontSize(int headerFontSize);
signals:
    void fillModeChanged();
    void columnWidthScaleChanged();
    void numberOfThrowsChanged();
    void columnCountChanged();
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
private:
    // Data related
    double rowHeightFromHeaderData(const int& row) const;
    double rowHeightFromCellDataAt(const int& row) const;
    void updateInitialCellValues();
    void setInitialColumnWidths(const int& count);
    void initializeFieldsHorizontally(const int& startColumn, const int& initialValue = -1);
    bool isIndexValid(const QModelIndex& index);
    bool setPlayerData(const QString &playerName,
                       const int &score);
    bool isCellDecorated(const QModelIndex &index);
    int indexOfLastDecoratedField();
    bool isRowEmpty(const int &row);
    bool removeData(const QModelIndex &index);
    int indexOfHeaderItem(const QString &data);
    void addVerticalHeaderData(const QString &data);
    /*
     * Font metrics related
     */
    int stringWidth(const QString &string,
                      const QString &family = "",
                      const int &pointSize = -1) const;
    // Const member variables
    const QString preferedFontFamily = "MS Sans Serif";
    const int preferedPointSize = 12;
    const int minimumPreferedColumnWidth = 64;
    const int minimumPreferedRowHeight = 25;
    void updateColumnWidth(const int &column, const int &data);
    // State member variables
    /*
     * Row and column fields
     */
    int _rows = 0;
    int _columns = 0;
    double _scale = 1.05;
    int _horizontalFillMode = HeaderFillMode::NoFillMode;
    int _attemps = 3;
    int _minimumColumnCount = 0;
    int _minimumRowCount = 0;
    int _initialValue = -1;

    /*
     * Font related
     *  - Score/point/header font size
     *  - Score/point/header font family
     */
    int _scoreFontSize = 12;
    int _pointFontSize = 8;
    int _headerFontSize = 12;

    QString _scoreFontFamily = "MS Sans Serif";
    QString _pointFontFamily = "MS Sans Serif";
    /*
     * Headerdata
     */
    QStringList _verticalHeaderData;
    double greatestVerticalHeaderWidth = 0;
    /*
     * Column widths
     */
    QList<double> _columnWidths;
    /*
     * Scores
     */
    QList<int> _data;
};

#endif // HORIZONTALFTPSINGLEDATAMODEL_H
