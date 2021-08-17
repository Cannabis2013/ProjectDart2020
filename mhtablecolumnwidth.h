#ifndef MHTABLECOLUMNWIDTH_H
#define MHTABLECOLUMNWIDTH_H

#include <qobject.h>
#include <qvector.h>
class MHTableColumnWidth : public QObject
{
    Q_OBJECT
public:
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
        return _columnWidths.at(column);
    }
signals:
    void minimumColumnWidthChanged();
private:
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
    QVector<int> _columnWidths;
    int _minimumWidth = 64;
};

#endif // MHTABLECOLUMNWIDTHS_H
