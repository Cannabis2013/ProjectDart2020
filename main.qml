import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import CustomItems 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    color: "lightgray"
    width: 640
    height: 480
    title: qsTr("Dart2020")

    Item {
        id: customItem
        anchors.centerIn: parent

        width: 320
        height: 240
        CustomTableView
        {
            color: 2
            anchors.centerIn: parent
        }
    }

}
