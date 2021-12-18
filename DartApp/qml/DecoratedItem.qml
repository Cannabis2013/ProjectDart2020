import QtQuick 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13
Rectangle
{
    id: imageRect
    clip: true
    color: "transparent"
    signal startAni()
    onStartAni: checkMarkScaleAni.start()
    property url source: imageDecorator.source = source
    Image
    {
        id: imageDecorator
        anchors.fill: parent
        source: imageRect.source
    }
    PropertyAnimation on scale{
        id: checkMarkScaleAni
        from: 0
        to: 1
        running: false
        duration: 125
        onFinished: checkMarkRotationAni.start()
    }
    PropertyAnimation on rotation {
        id: checkMarkRotationAni
        from: 360
        to:0
        running: false
        duration: 125
    }
}
