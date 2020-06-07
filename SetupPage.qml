import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3

import ApplicationInterface 1.0

Rectangle{
    id: body

    color: "#A54141"

    GridLayout{
        anchors.fill: parent

        columns: 1
        rows:2

        rowSpacing: 10

        anchors.margins: 20

        MyLineEdit {
            Layout.row: 0
            Layout.column: 0
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            width: 250
            height: 32

            fontSize: 12

            labelText: "Title"
            labelFontSize: 10
            labelLeftMargin: 10
        }

        MyLineEdit {
            Layout.row: 1
            Layout.column: 0
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter

            width: 250
            height: 32

            fontSize: 12

            labelText: "Number of legs"
            labelFontSize: 10
            labelLeftMargin: 10
        }

        GridLayout
        {
            id: bodyLayout

            Layout.row: 2
            Layout.column: 0

            Layout.fillWidth: true
            Layout.fillHeight: true

            rows:2
            columns: 2
            Label{

                Layout.row: 0
                Layout.column: 0
                text: "Pick players"
                font.pointSize: 24

                anchors.fill: parent
                horizontalAlignment: Qt.AlignHCenter
            }

            MyListView {
                id: pickPlayerView

                Layout.row: 1
                Layout.column: 0

                Component.onCompleted: {
                    addItem("Martin","Hansen","havnetrold2002@yahoo.dk", "232-322-111");
                    addItem("Kent","Killerhertz","Killerhertz@gmail.com", "644-233-442");
                }
            }
        }

        Rectangle
        {
            Layout.fillHeight: true
        }
    }
}
