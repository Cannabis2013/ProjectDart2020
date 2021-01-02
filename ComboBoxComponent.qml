import QtQuick 2.0

import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.13

UserInputContent{
    id: comboBoxComponentBody
    property var stringModel: ["Item one", "Item two", "Item three"]
    onStringModelChanged: comboBox.model = stringModel

    property color popupBackgroundColor: "white"
    onPopupBackgroundColorChanged: popupItem.color = popupBackgroundColor

    property color popupItemHoveredColor: "white"
    onPopupItemHoveredColorChanged: popupItem.hoveredColor = popupItemHoveredColor
    currentValue : comboBox.currentText

    onCurrentIndexChanged: comboBox.currentIndex = comboBoxComponentBody.currentIndex

    layer.enabled: true
    layer.effect: OpacityMask{
        maskSource: Item {
            width: comboBox.width
            height: comboBox.height
            Rectangle{
                anchors.fill: parent
                radius: 20
            }
        }
    }
    ComboBox
    {
        id: comboBox
        anchors.fill: parent
        model: stringModel
        onCurrentValueChanged: valueChanged(currentValue)
        delegate: Rectangle
        {
            id: delegateBody
            width: parent.width
            height:60
            border.width: 0
            color: popupBackgroundColor
            x: 0
            y: 0
            PushButton{
                id: popupItem

                anchors.fill: parent
                text: modelData

                backgroundColor: popupBackgroundColor

                textColor: "black"

                hoveredTextColor: "blue"
                hoveredColor: popupItemHoveredColor

                buttonRadius: 0

                onClicked: {
                    comboBox.currentIndex = comboBox.indexOfValue(text);
                    comboBox.popup.close();
                }
            }
        }
    }
}
