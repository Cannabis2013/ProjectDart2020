#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QQuickPaintedItem>
#include <qpainter.h>

class CustomTableView : public QQuickPaintedItem
{
public:
    CustomTableView();

    // QQuickPaintedItem interface
    void paint(QPainter *painter) override;

private:
};

#endif // CUSTOMTABLEVIEW_H
