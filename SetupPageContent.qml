import QtQuick 2.0
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

Rectangle {
    color: "transparent"

    Layout.fillHeight: true
    Layout.fillWidth: true

    GridLayout{
        flow: GridLayout.TopToBottom
        anchors.fill: parent

        MyLineEdit {
            id: titleEdit

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            width: 360
            height: 32

            fontSize: 12

            labelText: "Title"
            labelFontSize: 8
            labelFontColor: "white"
            labelLeftMargin: 10
        }

        MyLineEdit {
            id: legsEdit

            isNumeric: true

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            width: 360
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

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            width: 360
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

            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            width: 360
            height: 32

            fontSize: 12

            labelText: "Keypoint"
            labelFontSize: 8
            labelFontColor: "white"
            labelLeftMargin: 10
        }

        ComboBoxView{
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            width: 360
            height: 32

            labelText: "Game modes"
            labelFontSize: 8
            labelLeftMargin: 10
        }

        ListComponent {
            id: listComponent

            Layout.fillWidth: true
            Layout.fillHeight: true

            componentTitle: "Assign players"
            itemTextColor: "white"
            itemSelectedtextColor: "yellow"
            itemSelectedBackgroundColor: "black"

            itemHoveredColor: Qt.rgba(23,43,22,0.1)

            itemFontSize: 10

            itemWidth: 256
        }

        MyRectangle{
            topBorderWidth: 1

            Layout.fillWidth: true
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
        }
    }
}
