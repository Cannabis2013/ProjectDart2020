import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

Rectangle{
    clip: true
    color: "transparent"
    
    signal buttonOneClicked
    signal buttonTwoClicked

    property string buttonOneTitle: "Button one"
    property string buttonTwoTitle: "Button two"

    onButtonOneTitleChanged: buttonOne.text = buttonOneTitle
    onButtonTwoTitleChanged: buttontwo.text = buttonTwoTitle

    property color buttonBackgroundColor: "green"
    onButtonBackgroundColorChanged: {
        buttonOne.backgroundColor = buttonBackgroundColor
        buttonTwo.backgroundColor = buttonBackgroundColor
    }

    property int buttonWidth: 80
    onButtonWidthChanged: {
        buttonOne.width = buttonWidth
        buttontwo.width = buttonWidth
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
            backgroundColor: buttonBackgroundColor
            
            height: 30
            width: buttonWidth

            onClicked: buttonOneClicked()
        }
        
        PushButton{
            id: buttontwo

            text: buttonTwoTitle
            
            Layout.row: 0
            Layout.column: 1
            
            fontSize: 8
            textColor: "white"
            backgroundColor: buttonBackgroundColor
            
            height: 30
            width: buttonWidth

            onClicked: buttonTwoClicked()
        }
    }
}
