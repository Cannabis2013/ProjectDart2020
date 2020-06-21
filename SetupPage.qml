import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0


Rectangle{
    id: body

    color: "#A54141"

    signal backButtonPressed

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

        ComboBoxView{

            Layout.row: 5
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
            Layout.row: 6
            Layout.fillWidth: true

            height: 192

            itemTextColor: "white"
            itemSelectedtextColor: "yellow"
            itemSelectedBackgroundColor: "black"

            itemHoveredColor: Qt.rgba(23,43,22,0.1)

            itemFontSize: 10

            itemWidth: 256
        }

        MyRectangle{
            Layout.row: 7
            Layout.column: 0

            topBorderWidth: 1

            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        ButtonsComponent {
            Layout.column: 0
            Layout.row: 8
            clip: true
            color: "transparent"
            height: 30
            width: 200
            Layout.alignment: Qt.AlignBottom |Qt.AlignHCenter
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
        }

        /*
        listComponent.addItem("Martin","Hansen","havnetrold2002@yahoo.dk", "232-322-111");
        listComponent.addItem("Kent","Killerhertz","Killerhertz@gmail.com", "644-233-442");
        listComponent.addItem("Nicolai","Hansen","nicolaimaler2890@live.dk", "112-666-324");
        listComponent.addItem("Mark", "Fuglelort", "Fuglelortergodt@lortemail.dk", "001-213-433");
        */
    }
}
