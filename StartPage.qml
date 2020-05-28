import QtQuick 2.0
import QtQuick.Layouts 1.3


Item {
    BorderImage {
        id: background
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        source: "qrc:/pictures/Sandra.jpg"

        anchors.fill: parent

        opacity: 0.25
    }

    GridLayout {
        id: gridLayout

        anchors.fill: parent

        columns: 1

        Text {
            id: pageLabel

            text: qsTr("Dart 2020")

            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

            font.pointSize: 48
        }

        PushButton
        {
            Layout.alignment: Qt.AlignHCenter
            text: "Test button"

            width: 128
            height: 50


        }

        PushButton
        {
            Layout.alignment: Qt.AlignHCenter
            text: "Test button"

            width: 128
            height: 50
        }

        Rectangle
        {
            Layout.fillHeight: true
        }

    }


}
