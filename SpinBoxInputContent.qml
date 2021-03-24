import QtQuick 2.0
import QtQuick.Controls 2.5

import QtGraphicalEffects 1.13

UserInputContent{
    id: spinBoxBody
    /*
      UserInputContent interface
      */
    fontSize: 12
    onFontSizeChanged: spinBox.font.pointSize = fontSize
    currentValue: spinBox.value
    onSetValue: spinBox.value = value
    property int borderRadius: 20
    onBorderRadiusChanged: maskRect.radius = borderRadius
    SpinBox {
        id: spinBox
        layer.enabled: true
        layer.effect: OpacityMask{
            maskSource: Item {
                width: spinBox.width
                height: spinBox.height
                Rectangle{
                    id: maskRect
                    anchors.fill: parent
                    radius: spinBoxBody.borderRadius
                }
            }
        }
        value: 1
        anchors.fill: parent
        font.pointSize: spinBoxBody.fontSize
        onValueChanged: spinBoxBody.valueChanged(value)
    }
}
