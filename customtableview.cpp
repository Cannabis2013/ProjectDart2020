#include "customtableview.h"

CustomTableView::CustomTableView(QQuickItem *parent):
    QQuickItem(parent)

{
    setFlag(QQuickItem::ItemHasContents,true);
}


Node *CustomTableView::updatePaintNode(Node *oldNode, QQuickItem::UpdatePaintNodeData *)
{
    /*
     * QSGNode needs two things:
     *  - Material
     *  - Geometry
     */
    if(!oldNode) {
        oldNode = buildRootNode();

        auto frame = buildTableFrame(0,0,_minWidth,_minHeight,1,QColor(Qt::black),QColor());

        oldNode->appendChildNode(frame);
    }

    oldNode->markDirty(QSGNode::DirtyGeometry);

    return oldNode;
}

Node *CustomTableView::buildRootNode()
{
    auto root = new GeometryNode();
    auto geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),0);

    root->setGeometry(geometry);
    root->setMaterial(new QSGFlatColorMaterial());

    root->setFlag(Node::OwnsGeometry);
    root->setFlag(Node::OwnsMaterial);

    return root;
}

Node *CustomTableView::buildTableFrame(const int &x, const int &y, const int &w, const int &h, const int &borderWidth, const QColor &borderColor, const QColor &backgroundColor)
{
    auto root = buildRootNode();

    if(backgroundColor != QColor())
    {
        auto backgroundNode = buildRectangle(x,y,w,h,borderWidth,backgroundColor,true);

        root->appendChildNode(backgroundNode);
    }

    auto frameNode = buildRectangle(x,y,w,h,borderWidth,borderColor,false);

    root->appendChildNode(frameNode);

    return root;
}

Node *CustomTableView::buildRectangle(const int &x, const int &y, const int &w, const int &h,const int &penWidth, const QColor &color, const bool &isMassive)
{
    auto node = new GeometryNode;

    auto drawingMode = isMassive ? GL_POLYGON : GL_LINE_LOOP;

    auto rectGeo = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(),4);

    rectGeo->setDrawingMode(drawingMode);
    if(!isMassive)
        rectGeo->setLineWidth(penWidth);

    auto material = new QSGFlatColorMaterial;

    material->setColor(color);

    rectGeo->vertexDataAsPoint2D()[0].set(0,0);
    rectGeo->vertexDataAsPoint2D()[1].set(w,0);
    rectGeo->vertexDataAsPoint2D()[2].set(w,h);
    rectGeo->vertexDataAsPoint2D()[3].set(0,h);

    node->setMaterial(material);
    node->setGeometry(rectGeo);

    node->setFlag(Node::OwnsGeometry);
    node->setFlag(Node::OwnsMaterial);

    return node;
}

int CustomTableView::getRows() const
{
    return _rows;
}

void CustomTableView::setRows(int rows)
{
    _rows = rows;
}

int CustomTableView::getColumns() const
{
    return _columns;
}

void CustomTableView::setColumns(int columns)
{
    _columns = columns;
}

int CustomTableView::getHeight() const
{
    return _minHeight;
}

void CustomTableView::setHeight(int height)
{
    _minHeight = height;
}

int CustomTableView::getWidth() const
{
    return _minWidth;
}

void CustomTableView::setWidth(int width)
{
    _minWidth = width;
}
