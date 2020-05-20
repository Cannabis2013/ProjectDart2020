#ifndef CUSTOMTABLE_H
#define CUSTOMTABLE_H

#include <QQuickPaintedItem>
#include <qpainter.h>

class CustomTable : public QQuickPaintedItem
{
public:
    CustomTable();

    // QQuickPaintedItem interface
    void paint(QPainter *painter) override
    {

    }
};

#endif // CUSTOMTABLE_H
