import QtQuick 2.0
import QtQuick.Controls 2.5

import QtGraphicalEffects 1.13

UserInputContent{
    id: body
    /*
      UserInputContent interface
      */
    fontSize: 12
    onFontSizeChanged: spinBox.font.pointSize = fontSize
    currentValue: spinBox.value
    onSetValue: spinBox.value = value
    SpinBox {
        id: spinBox
        layer.enabled: true
        layer.effect: OpacityMask{
            maskSource: Item {
                width: spinBox.width
                height: spinBox.height
                Rectangle{
                    anchors.fill: parent
                    radius: 20
                }
            }
        }
        value: 1
        anchors.fill: parent
        font.pointSize: body.fontSize
        onValueChanged: body.valueChanged(value)
    }
}
