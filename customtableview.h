#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QQuickPaintedItem>
#include <qpainter.h>

class CustomTableView : public QQuickPaintedItem
{
public:
    CustomTableView(QQuickItem *parent = 0);

    Q_PROPERTY(int color READ getColor() WRITE setColor());

    // QQuickPaintedItem interface
    void paint(QPainter *painter) override;

    int getHeight() const;
    void setHeight(int getHeight);

    int getWidth() const;
    void setWidth(int getWidth);

    int getX() const;
    void setX(int getX);

    int getY() const;
    void setY(int getY);

    int getColor() const;
    void setColor(int color);

private:
    int _height, _width;
    int _x, _y;
    int _color;
};

#endif // CUSTOMTABLEVIEW_H
