#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QQuickPaintedItem>
#include <qpainter.h>
#include <qcolor.h>
#include <QSGGeometryNode>
#include <qsggeometry.h>
#include <QSGFlatColorMaterial>

typedef QSGNode Node;
typedef QSGGeometryNode GeometryNode;

class CustomTableView : public QQuickItem
{
    Q_OBJECT
public:
    CustomTableView(QQuickItem *parent = 0);

    Q_PROPERTY(int bodyWidth READ getWidth NOTIFY sizeChanged);
    Q_PROPERTY(int bodyHeight READ getHeight WRITE setHeight NOTIFY sizeChanged);
    Q_PROPERTY(int columns READ getColumns WRITE setColumns NOTIFY columnCountChanged);
    Q_PROPERTY(int rows READ getRows WRITE setRows NOTIFY rowCountChanged);

    // QQuickItem interface
    int getWidth() const;
    void setWidth(int getWidth);

    int getHeight() const;
    void setHeight(int getHeight);

    int getColumns() const;
    void setColumns(int columns);

    int getRows() const;
    void setRows(int rows);

signals:
    void sizeChanged();

    void columnCountChanged();
    void rowCountChanged();

protected:
    Node *updatePaintNode(Node *oldNode, UpdatePaintNodeData *) override;

private:
    Node *buildRootNode();

    Node *buildTableFrame(const int &x,
                          const int &y,
                          const int &getWidth,
                          const int &getHeight,
                          const int &borderWidth,
                          const QColor &borderColor,
                          const QColor &backgroundColor = QColor());

    Node *buildRectangle(const int &x,
                         const int &y,
                         const int &w,
                         const int &h, const int &penWidth,
                         const QColor &color,
                         const bool &isMassive);

    int _minWidth = 950, _minHeight = 300;
    int _columns = 0, _rows = 0;
};

#endif // CUSTOMTABLEVIEW_H
