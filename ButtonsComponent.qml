import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

Rectangle{
    id: body
    clip: true
    color: "transparent"
    
    signal buttonOneClicked
    signal buttonTwoClicked

    property bool buttonOneEnabled: true
    onButtonOneEnabledChanged: buttonOne.enabled = buttonOneEnabled

    property bool buttonTwoEnabled: true
    onButtonTwoEnabledChanged: buttonTwo.enabled = buttonTwoEnabled

    property string buttonOneTitle: "Button one"
    property string buttonTwoTitle: "Button two"

    onButtonOneTitleChanged: buttonOne.text = buttonOneTitle
    onButtonTwoTitleChanged: buttonTwo.text = buttonTwoTitle

    property color buttonBackgroundColor: "green"
    onButtonBackgroundColorChanged: {
        buttonOne.backgroundColor = buttonBackgroundColor
        buttonTwo.backgroundColor = buttonBackgroundColor
    }
    property color buttonsHoveredColor: "white"
    onButtonsHoveredColorChanged: {
        buttonOne.hoveredColor = buttonsHoveredColor;
        buttonTwo.hoveredColor = buttonsHoveredColor;
    }

    property int buttonWidth: 80
    onButtonWidthChanged: {
        buttonOne.width = buttonWidth
        buttonTwo.width = buttonWidth
    }

    Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
    
    GridLayout{
        rows: 1
        columns: 3
        
        anchors.fill: parent
        
        rowSpacing: 5
        
        PushButton{
            id: buttonOne
            text: buttonOneTitle
            Layout.row: 0
            Layout.column: 0
            fontSize: 8
            textColor: "white"
            backgroundColor: body.buttonBackgroundColor
            hoveredColor: body.buttonsHoveredColor
            height: 30
            width: buttonWidth
            onClicked: buttonOneClicked()
            Layout.alignment: Qt.AlignRight
            enabled: buttonOneEnabled
        }
        
        PushButton{
            id: buttonTwo
            text: buttonTwoTitle
            Layout.row: 0
            Layout.column: 1
            fontSize: 8
            textColor: "white"
            backgroundColor: body.buttonBackgroundColor
            hoveredColor: body.buttonsHoveredColor
            height: 30
            width: buttonWidth
            onClicked: buttonTwoClicked()
            Layout.alignment: Qt.AlignLeft
            enabled: buttonTwoEnabled
        }
    }
}
