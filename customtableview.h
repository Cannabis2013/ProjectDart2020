#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QQuickPaintedItem>
#include <qpainter.h>
#include <qcolor.h>
#include <QSGGeometryNode>
#include <qsggeometry.h>
#include <QSGFlatColorMaterial>

class CustomTableView : public QQuickItem
{
    Q_OBJECT
public:
    CustomTableView(QQuickItem *parent = 0);

    Q_PROPERTY(QColor color READ getColor WRITE setColor NOTIFY colorChanged);


    QColor getColor() const;
    void setColor(const QColor &color);

signals:
    void colorChanged();

    // QQuickItem interface
protected:
    QSGNode *updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *updatedNote) override;

private:
    QColor _color = QColor(Qt::red);
    bool _needUpdate = true;


};

#endif // CUSTOMTABLEVIEW_H
