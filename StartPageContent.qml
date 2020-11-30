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

    Image{
        id: fckImage
        source: "qrc:/pictures/Ressources/fck.png"

        x: parent.width / 2 - width/2
        y: 5

        width: 150
        height: 150
    }

    Image {
        id: dartLogo
        source: "qrc:/pictures/Ressources/pngfuel.com.png"

        x: parent.width/2 - 175
        y: 5

        width: 130
        height: 130
    }

    Image {
        id: tuborgImage

        source: "qrc:/pictures/Ressources/tuborgclassic.png"

        x: parent.width/2 + 25
        y: 25

        width: 130
        height: 130

        rotation: 25
    }

    Rectangle{
        id: backgroundRect
        anchors.fill: parent
        color:ThemeContext.pageColor
        opacity: 0.5
    }

    GridLayout {
        id: gridLayout

        anchors.fill: parent
        rowSpacing: 5
        flow: GridLayout.TopToBottom

        Rectangle{
            height: 192
            color: "transparent"
        }

        StartMenuButton
        {
            Layout.alignment: Qt.AlignHCenter
            text: "Select tournament \n and play"
            onClicked: setupGameClicked()
            backgroundColor: ThemeContext.startPageButtonColor
            hoveredColor: ThemeContext.startPageButtonColor
        }

        StartMenuButton {
            Layout.alignment: Qt.AlignHCenter
            text: "Manage tournaments \n and players"
            onClicked: manageContentClicked()
            backgroundColor: ThemeContext.startPageButtonColor
            hoveredColor: ThemeContext.startPageButtonColor
        }
        StartMenuButton
        {
            Layout.alignment: Qt.AlignHCenter
            text: "Settings"
            onClicked: settingsButtonClicked()
            backgroundColor: ThemeContext.startPageButtonColor
            hoveredColor: ThemeContext.startPageButtonColor
        }

        StartMenuButton
        {
            Layout.alignment: Qt.AlignHCenter
            text: "Quit"
            onClicked: quitButtonClicked()
            backgroundColor: ThemeContext.startPageButtonColor
            hoveredColor: ThemeContext.startPageButtonColor
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

    Component.onCompleted: requestSetPageTitle("Welcome to Dart2020")
}
