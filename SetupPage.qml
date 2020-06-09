import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

Rectangle{
    id: body

    color: "#A54141"

    signal backButtonPressed

    GridLayout{
        anchors.fill: parent

        columns: 1

        rowSpacing: 10

        anchors.margins: 20

        PushButton
        {
            width: 65
            height: 30

            Layout.row: 0
            Layout.column: 0
            Layout.alignment: Qt.AlignTop | Qt.AlignLeft

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

            width: 380
            height: 32

            fontSize: 12

            labelText: "Title"
            labelFontSize: 8
            labelLeftMargin: 10
        }

        MyLineEdit {
            id: legsEdit
            Layout.row: 3
            Layout.column: 0
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            width: 380
            height: 32

            fontSize: 12

            labelText: "Number of legs"
            labelFontSize: 8
            labelLeftMargin: 10
        }

        MyLineEdit {

            id: maxPlayerEdit
            Layout.row: 4
            Layout.column: 0
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            width: 380
            height: 32

            fontSize: 12

            labelText: "Max allowered players"
            labelFontSize: 8
            labelLeftMargin: 10
        }

        ListComponent {
            id: listComponent

            Layout.column: 0
            Layout.row: 6
            Layout.fillWidth: true

            height: 192

            itemSelectedColor: "black"

            itemFontSize: 10

            itemWidth: 224
        }

        MyRectangle
        {
            id: lowerLayoutSpacer

            Layout.fillWidth: true
            Layout.fillHeight: true

            Layout.column: 0
            Layout.row: 7
        }
    }

    Component.onCompleted: {
        listComponent.addItem("Martin","Hansen","havnetrold2002@yahoo.dk", "232-322-111");
        listComponent.addItem("Kent","Killerhertz","Killerhertz@gmail.com", "644-233-442");
        listComponent.addItem("Nicolai","Hansen","nicolaimaler2890@live.dk", "112-666-324");
        listComponent.addItem("Mark", "Fuglelort", "Fuglelortergodt@lortemail.dk", "001-213-433");
    }
}
