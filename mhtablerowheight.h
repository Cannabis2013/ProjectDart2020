#ifndef MHTABLEROWHEIGHT_H
#define MHTABLEROWHEIGHT_H

#include <qobject.h>
#include <qvector.h>

class MHTablerowHeight : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(double scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(int minimumRowHeight READ minimumRowHeight WRITE setMinimumRowHeight NOTIFY minimumRowHeightChanged)
    Q_INVOKABLE void updateRowHeight(const int &row, const int &height)
    {
        if(invalidRow(row))
            insert(row);
        setRowHeightAt(row,height);
    }
    Q_INVOKABLE int rowHeightAt(const int &row) const
    {
        if(invalidRow(row))
            return -1;
        return heightAt(row);
    }
    double scale() const
    {
        return _scale;
    }
    void setScale(double newScale)
    {
        _scale = newScale;
        emit scaleChanged();
    }
signals:
    void minimumRowHeightChanged();
    void scaleChanged();

private:
    int heightAt(const int &row) const
    {
        auto h = _rowHeights.at(row);
        auto hs = h*scale();
        if(h < minimumRowHeight())
            hs = minimumRowHeight()*scale();
        return hs;
    }
    int minimumRowHeight() const
    {
        return _minimumRowHeight;
    }
    void setMinimumRowHeight(int newMinimumRowHeight)
    {
        if (_minimumRowHeight == newMinimumRowHeight)
            return;
        _minimumRowHeight = newMinimumRowHeight;
        emit minimumRowHeightChanged();
    }
    void insert(const int &row)
    {
        auto delta = row - indexOfLastRow();
        QVector<int> newRowHeights = QVector<int>(delta,minimumRowHeight());
        _rowHeights.append(newRowHeights);
    }
    bool invalidRow(const int &row) const
    {
        return row > indexOfLastRow();
    }

    int indexOfLastRow() const
    {
        return _rowHeights.count() - 1;
    }
    void setRowHeightAt(const int &row, const int &height)
    {
        _rowHeights.replace(row,height);
    }
    QVector<int> _rowHeights;
    int _minimumRowHeight = 32;
    double _scale;
};
#endif // MHTABLEROWHEIGHT_H
