import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

ApplicationWindow {
    id: applicationWindow
    visible: true
    color: "lightgray"


    x: 960 - width/2
    y: 1080/2 - height/2

    width: 400
    height: 500

    title: qsTr("Dart2020")

    StartPage
    {
        anchors.fill: parent
    }

}

