import QtQuick 2.0

import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3


Rectangle{
    id: body

    clip: true

    function currentSelectedText(){
        var currentText = gameModeSelector.currentText;

        return currentText;
    }

    function setModel(strings)
    {
        gameModeSelector.model = strings
    }

    ComboBox
    {
        id: gameModeSelector
        
        anchors.fill: parent

        model: ["First to post", "Round race", "Circular mode"]
        
        delegate: Rectangle
        {
            id: delegateBody
            width: parent.width
            height:60

            border.width: 0

            color: "gray"

            x: 0
            y: 0

            PushButton{
                id: popupItem

                anchors.fill: parent
                text: modelData

                backgroundColor: "gray"

                textColor: "black"

                hoveredTextColor: "blue"
                hoveredColor: "gray"

                buttonRadius: 0

                onClicked: {
                    gameModeSelector.currentIndex = gameModeSelector.indexOfValue(text);
                    gameModeSelector.popup.close();

                }
            }
        }
    }
}
