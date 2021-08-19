#ifndef MHTABLECOLUMNWIDTH_H
#define MHTABLECOLUMNWIDTH_H

#include <qobject.h>
#include <qvector.h>
class MHTableColumnWidth : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged);
    Q_PROPERTY(int minimumColumnWidth READ minimumColumnWidth WRITE setMinimumColumnWidth NOTIFY minimumColumnWidthChanged);
    Q_INVOKABLE void updateColumnWidth(const int &column, const int &width)
    {
        if(invalidColumn(column))
            insertColumn(column);
        setColumnWidthAt(column,width);
    }
    Q_INVOKABLE int columnWidthAt(const int &column) const
    {
        if(column < 0 || column >= _columnWidths.count())
            return _minimumWidth;
        return widthAt(column);
    }
signals:
    void minimumColumnWidthChanged();
    void scaleChanged();
private:
    int widthAt(const int &column) const
    {
        auto ws = _columnWidths.at(column)*scale();
        if(ws < _minimumWidth)
            ws = _minimumWidth*scale();
        return ws;
    }
    bool invalidColumn(const int &column) const
    {
        return column > indexOfLastColumn();
    }
    int minimumColumnWidth() const
    {
        return _minimumWidth;
    }
    void setMinimumColumnWidth(const int &width)
    {
        _minimumWidth = width;
        emit minimumColumnWidthChanged();
    }
    void insertColumn(const int &column)
    {
        auto delta = column - indexOfLastColumn();
        QVector<int> l = QVector<int>(delta,minimumColumnWidth());
        _columnWidths.append(l);
    }
    int indexOfLastColumn() const
    {
        return _columnWidths.count() - 1;
    }
    void setColumnWidthAt(const int &column, const int &width)
    {
        _columnWidths.replace(column,width);
    }
    double scale() const
    {
        return _scale;
    }
    void setScale(double newScale)
    {
        if (_scale == newScale)
        return;
        _scale = newScale;
        emit scaleChanged();
    }
    QVector<int> _columnWidths;
    int _minimumWidth = 0;
    double _scale;
};
#endif // MHTABLECOLUMNWIDTHS_H
