import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: applicationWindow
    visible: true
    color: "lightgray"

    x:240
    y:240
    width: 400
    height: 300

    title: qsTr("Dart2020")


    ScoreTable
    {
        anchors.centerIn: parent
    }
}

