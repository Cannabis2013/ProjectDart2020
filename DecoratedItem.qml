import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13
Rectangle
{
    id: imageRect
    clip: true
    color: "transparent"
    property url source: imageDecorator.source = source
    Image
    {
        id: imageDecorator
        anchors.fill: parent
        source: imageRect.source
    }
}
