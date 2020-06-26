import QtQuick 2.0
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

Rectangle {
    color: "transparent"

    Layout.fillHeight: true
    Layout.fillWidth: true

    Layout.maximumWidth: defaultPageContentWidth

    Layout.alignment: Qt.AlignHCenter

    GridLayout{
        flow: GridLayout.TopToBottom
        anchors.fill: parent

        MyLineEdit {
            id: titleEdit

            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true

            height: 32

            onWidthChanged: print(width)

            fontSize: 12

            labelText: "Title"
            labelFontSize: 8
            labelFontColor: "white"
            labelLeftMargin: 10
        }

        MyLineEdit {
            id: legsEdit

            isNumeric: true

            Layout.fillWidth: true

            Layout.alignment: Qt.AlignTop

            height: 32

            fontSize: 12

            labelText: "Number of legs"
            labelFontSize: 8
            labelFontColor: "white"
            labelLeftMargin: 10

        }

        MyLineEdit {
            id: maxPlayerEdit

            isNumeric: true

            Layout.fillWidth: true

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            height: 32

            fontSize: 12

            labelText: "Max allowered players"
            labelFontSize: 8
            labelFontColor: "white"
            labelLeftMargin: 10
        }

        MyLineEdit {
            id: keyPointEdit

            isNumeric: true

            Layout.fillWidth: true

            height: 32

            fontSize: 12

            labelText: "Keypoint"
            labelFontSize: 8
            labelFontColor: "white"
            labelLeftMargin: 10
        }

        ComboBoxView{
            height: 32

            Layout.fillWidth: true

            labelText: "Game modes"
            labelFontSize: 8
            labelLeftMargin: 10
        }

        Rectangle{
            height: 10
        }

        ListComponent {
            id: listComponent

            Layout.alignment: Qt.AlignHCenter

            width: 320
            height: 256

            componentTitle: "Assign players"
            itemTextColor: "black"
            itemSelectedBackgroundColor: "white"

            itemHoveredColor: Qt.rgba(23,43,22,0.1)

            color: "silver"

            radius: 15

            itemFontSize: 8

            itemWidth: 256
        }

        MyRectangle{
            bottomBorderWidth: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        ButtonsComponent {
            Layout.column: 0
            Layout.row: 9
            clip: true
            color: "transparent"
            height: 30
            width: 200
            Layout.alignment: Qt.AlignBottom |Qt.AlignHCenter

            onSaveClicked: {
                // Save tournament and go back to previous page

                var tournamentTitle = titleEdit.currentText;
                var legs = legsEdit.currentText;
                var maxPlayers = maxPlayerEdit.currentText;
                var keyPoint = keyPointEdit.currentText;

                backButtonPressed();
            }
        }

        Component.onCompleted: {
            var playerCount = projectDart.playersCount();

            for(var i = 0;i < playerCount;i++)
            {
                var playerID = projectDart.playerIDFromIndex(i);

                var playerFirstName = projectDart.playerFirstName(playerID);
                var playerLastName = projectDart.playerLastName(playerID);
                var playerEMail = projectDart.playerEmail(playerID);

                listComponent.addPlayerItem(playerFirstName,playerLastName,playerEMail, playerID);
            }

            listComponent.addPlayerItem("Martin","Hansen","havnetrold2002@yahoo.dk","333-333-333");
        }
    }
}
