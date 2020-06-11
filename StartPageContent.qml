import QtQuick 2.0
import QtQuick.Layouts 1.3


Rectangle
{
    id: body

    signal setupGameClicked
    signal settingsButtonClicked
    signal loginButtonClicked // Experimental
    signal logoutButtonClicked // Experimental
    signal quitButtonClicked

    GridLayout {
        id: gridLayout

        anchors.fill: parent
        rowSpacing: 5
        
        columns: 3
        
        Rectangle
        {
            Layout.row: 0
            Layout.column: 0
            Layout.columnSpan: 3
            Layout.fillHeight: true
            Layout.maximumHeight: 32
        }

        PushButton
        {
            Layout.row: 1
            Layout.column: 1
            Layout.alignment: Qt.AlignHCenter

            fontSize: 10

            width: 256
            height: 64

            text: "Create or setup tournament \n and play"

            textColor: "white"
            backgroundColor: "green"

            onClicked: setupGameClicked()
        }

        PushButton
        {
            Layout.row: 2
            Layout.column: 1
            Layout.alignment: Qt.AlignHCenter

            fontSize: 10

            width: 256
            height: 64

            text: "Settings"

            textColor: "white"
            backgroundColor: "green"

            onClicked: settingsButtonClicked()
        }

        PushButton
        {
            Layout.row: 3
            Layout.column: 1
            Layout.alignment: Qt.AlignHCenter

            fontSize: 10

            width: 256
            height: 64

            text: "Quit"

            textColor: "white"
            backgroundColor: "green"

            onClicked: quitButtonClicked()
        }
        
        Rectangle
        {
            Layout.row: 4
            Layout.column: 1
            
            Layout.fillHeight: true

            border.width: 1
        }

    }
    LoginComponent {

        width: 132

        height: 54

        clip: true

        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
}
