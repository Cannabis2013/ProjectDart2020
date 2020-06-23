import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

Page {
    id: setupPageBody

    property color labelBackgroundColor: "black"
    onLabelBackgroundColorChanged: {
        titleEdit.labelBackgroundColor = labelBackgroundColor;
        legsEdit.labelBackgroundColor = labelBackgroundColor;
        maxPlayerEdit.labelBackgroundColor = labelBackgroundColor;
    }

    GridLayout{
        anchors.fill: parent

        columns: 1

        rowSpacing: 10

        anchors.leftMargin: 20
        anchors.topMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 5

        PushButton
        {
            width: 65
            height: 30

            Layout.row: 0
            Layout.column: 0
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft

            textColor: "white"

            text: "Back"

            fontSize: 10

            onClicked: backButtonPressed()
        }

        MyRectangle
        {
            id: upperLayoutSpacer

            Layout.row: 1

            topBorderWidth: 1

            Layout.fillWidth: true

            height: 12
        }

        MyLineEdit {
            id: titleEdit

            Layout.row: 2
            Layout.column: 0
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

            Layout.row: 3
            Layout.column: 0
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

            Layout.row: 4
            Layout.column: 0
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

            Layout.row: 5
            Layout.column: 0
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

            Layout.row: 6
            Layout.column: 0
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            width: 360
            height: 32

            labelText: "Game modes"
            labelFontSize: 8
            labelLeftMargin: 10
        }

        ListComponent {
            id: listComponent

            Layout.column: 0
            Layout.row: 7
            Layout.fillWidth: true
            Layout.fillHeight: true

            itemTextColor: "white"
            itemSelectedtextColor: "yellow"
            itemSelectedBackgroundColor: "black"

            itemHoveredColor: Qt.rgba(23,43,22,0.1)

            itemFontSize: 10

            itemWidth: 256
        }

        MyRectangle{
            Layout.row: 8
            Layout.column: 0

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
