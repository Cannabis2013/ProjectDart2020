#include "customtableview.h"


CustomTableView::CustomTableView(QQuickItem *parent):
    QQuickPaintedItem(parent)
{

}

void CustomTableView::paint(QPainter *painter)
{
    auto pen = QPen();

    pen.setWidth(4);
    pen.setColor(QColor(Qt::blue));

    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing,true);

    painter->drawRect(boundingRect());
}

int CustomTableView::getHeight() const
{
    return _height;
}

void CustomTableView::setHeight(int height)
{
    _height = height;
}

int CustomTableView::getWidth() const
{
    return _width;
}

void CustomTableView::setWidth(int width)
{
    _width = width;
}

int CustomTableView::getX() const
{
    return _x;
}

void CustomTableView::setX(int x)
{
    _x = x;
}

int CustomTableView::getY() const
{
    return _y;
}

void CustomTableView::setY(int y)
{
    _y = y;
}

int CustomTableView::getColor() const
{
    return _color;
}

void CustomTableView::setColor(int color)
{
    _color = color;
}
