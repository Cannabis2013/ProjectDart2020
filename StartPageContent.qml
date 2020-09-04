import QtQuick 2.0
import QtQuick.Layouts 1.3

Content
{
    id: startPageContentBody

    color: "transparent"

    signal setupGameClicked
    signal manageContentClicked
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
        flow: GridLayout.TopToBottom

        PageLabelItem {
            id: label

            height: 64
            width: 384
            Layout.fillWidth: true
            Layout.maximumHeight: 64

            text: "Dart2020"
        }
        
        Rectangle
        {
            Layout.fillHeight: true
            Layout.maximumHeight: 32
        }

        PushButton
        {
            Layout.alignment: Qt.AlignHCenter
            fontSize: 16
            width: 256
            height: 64
            text: "Select tournament \n and play"
            textColor: "white"
            backgroundColor: "green"
            onClicked: setupGameClicked()
        }

        PushButton{
            Layout.alignment: Qt.AlignHCenter
            fontSize: 16
            width: 256
            height: 64
            text: "Manage tournaments \n and players"
            textColor: "white"
            backgroundColor: "green"
            onClicked: manageContentClicked()
        }


        PushButton
        {
            Layout.alignment: Qt.AlignHCenter
            fontSize: 16
            width: 256
            height: 64
            text: "Settings"
            textColor: "white"
            backgroundColor: "green"
            onClicked: settingsButtonClicked()
        }

        PushButton
        {
            Layout.alignment: Qt.AlignHCenter
            fontSize: 16
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
