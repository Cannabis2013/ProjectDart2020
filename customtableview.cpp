#include "customtableview.h"



CustomTableView::CustomTableView(QQuickItem *parent):
    QQuickItem(parent)
{
    setFlag(QQuickItem::ItemHasContents,true);
}



QColor CustomTableView::getColor() const
{
    return _color;
}

void CustomTableView::setColor(const QColor &color)
{
    if(_color != color) {
            _color = color;
            _needUpdate = true;
            update();
            emit colorChanged();
        }
}

QSGNode *CustomTableView::updatePaintNode(QSGNode *oldNode, QQuickItem::UpdatePaintNodeData *updatedNote)
{
    Q_UNUSED(updatedNote)
    auto node = static_cast<QSGGeometryNode *>(oldNode);

    if(!node) {
        node = new QSGGeometryNode;

        auto geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 4);

        geometry->setDrawingMode(GL_POLYGON);

        geometry->vertexDataAsPoint2D()[0].set(0,0);
        geometry->vertexDataAsPoint2D()[1].set(width(),0);
        geometry->vertexDataAsPoint2D()[2].set(width(),height());
        geometry->vertexDataAsPoint2D()[3].set(0,height());

        node->setGeometry(geometry);
        node->setFlag(QSGNode::OwnsGeometry);
        node->setFlag(QSGNode::OwnsMaterial);
    }

    if(_needUpdate) {
        auto material = new QSGFlatColorMaterial;
        material->setColor(_color);
        node->setMaterial(material);
        _needUpdate = false;
    }

    return node;
}
