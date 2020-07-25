import QtQuick 2.0

import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3


Rectangle{
    id: comboBoxComponentBody

    clip: true

    property var stringModel: ["Item one", "Item two", "Item three"]
    onStringModelChanged: comboBox.model = stringModel

    property color popupBackgroundColor: "white"
    onPopupBackgroundColorChanged: popupItem.color = popupBackgroundColor

    property color popupItemHoveredColor: "white"
    onPopupItemHoveredColorChanged: popupItem.hoveredColor = popupItemHoveredColor
    function currentSelectedText(){
        var currentText = comboBox.currentText;
        return currentText;
    }

    function setModel(strings)
    {
        comboBox.model = strings
    }

    ComboBox
    {
        id: comboBox

        anchors.fill: parent

        model: stringModel
        
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
