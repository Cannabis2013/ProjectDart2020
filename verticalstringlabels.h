#ifndef VERTICALSTRINGLABELS_H
#define VERTICALSTRINGLABELS_H

#include <qobject.h>
#include "iheaderlabels.h"

#define OUT_OF_RANGE_MSG "Index out of range";
#define ITEM_NOT_FOUND_MSG "Item not found";

class VerticalStringLabels :
        public QObject,
        public IHeaderLabels<QString>
{
    Q_OBJECT
public:
    Q_INVOKABLE void appendItem(const QString &item) override;
    Q_INVOKABLE void appendItems(const QVector<QString> &items) override;
    Q_INVOKABLE void removeItem(const int &index) override;
    Q_INVOKABLE void clear() override;
    Q_INVOKABLE int indexOf(const QString &item) const override;
    Q_INVOKABLE int count() const override;
    Q_INVOKABLE QString item(const int &index) const override;
    Q_INVOKABLE QVector<QString> items() const override;
signals:
    void dataChanged();
private:
    bool isValid(const int &index) const;
    bool isValid(const QString &item) const;
    QVector<QString> _header;
};

#endif // VERTICALHEADERLABELS_H
