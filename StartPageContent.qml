import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle
{
    id: startPageContentBody

    color: "transparent"

    signal setupGameClicked
    signal settingsButtonClicked
    signal loginButtonClicked // Experimental
    signal logoutButtonClicked // Experimental
    signal quitButtonClicked

    property color labelBackgroundColor: "black"
    onLabelBackgroundColorChanged: {
        titleEdit.labelBackgroundColor = labelBackgroundColor;
        legsEdit.labelBackgroundColor = labelBackgroundColor;
        maxPlayerEdit.labelBackgroundColor = labelBackgroundColor;
    }

    Image {
        id: dartLogo
        source: "qrc:/pictures/Ressources/pngfuel.com.png"

        x: parent.width/2 - 200
        y: 5

        width: 130
        height: 130
    }

    Image {
        id: tuborgImage

        source: "qrc:/pictures/Ressources/tuborgclassic.png"

        x: parent.width/2 + 70
        y: 5

        width: 130
        height: 130

        rotation: 25
    }

    Image{
        id: fckImage
        source: "qrc:/pictures/Ressources/fck.png"

        x: parent.width / 2 - width/2
        y: 350

        width: 150
        height: 150
    }

    GridLayout {
        id: gridLayout

        anchors.fill: parent
        rowSpacing: 5
        
        columns: 3

        PageLabelItem {

            id: label

            height: 64
            width: 384

            Layout.fillWidth: true
            Layout.columnSpan: 3

            Layout.row: 0
            Layout.column: 0

            Layout.maximumHeight: 64
        }
        
        Rectangle
        {
            Layout.row: 1
            Layout.column: 0
            Layout.columnSpan: 3
            Layout.fillHeight: true
            Layout.maximumHeight: 32
        }

        PushButton
        {
            Layout.row: 2
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
            Layout.row: 3
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
            Layout.row: 4
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

            id: emptyRect
            Layout.row: 5
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
