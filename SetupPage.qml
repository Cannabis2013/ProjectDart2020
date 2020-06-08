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
        rows:2

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
            Layout.row: 1

            topBorderWidth: 1

            Layout.fillWidth: true

            height: 12
        }

        MyLineEdit {
            Layout.row: 2
            Layout.column: 0
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.fillWidth: true

            height: 32

            fontSize: 12

            labelText: "Title"
            labelFontSize: 8
            labelLeftMargin: 10
        }

        MyLineEdit {
            Layout.row: 3
            Layout.column: 0
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.fillWidth: true

            height: 32

            fontSize: 12

            labelText: "Number of legs"
            labelFontSize: 8
            labelLeftMargin: 10
        }

        MyLineEdit {
            Layout.row: 4
            Layout.column: 0
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            Layout.fillWidth: true

            height: 32

            fontSize: 12

            labelText: "Max allowered players"
            labelFontSize: 8
            labelLeftMargin: 10
        }

        ListComponent {
            id: listComponent

            Layout.column: 0
            Layout.row: 5
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
