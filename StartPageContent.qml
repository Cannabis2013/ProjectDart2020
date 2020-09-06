import QtQuick 2.12
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
        StartMenuButton
        {
            Layout.alignment: Qt.AlignHCenter
            text: "Select tournament \n and play"
            onClicked: setupGameClicked()
        }

        StartMenuButton {
            Layout.alignment: Qt.AlignHCenter
            text: "Manage tournaments \n and players"
            onClicked: manageContentClicked()
        }
        StartMenuButton
        {
            Layout.alignment: Qt.AlignHCenter
            text: "Settings"
            onClicked: settingsButtonClicked()
        }

        StartMenuButton
        {
            Layout.alignment: Qt.AlignHCenter
            text: "Quit"
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
