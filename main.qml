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

    MouseArea
    {
        anchors.fill: parent
        onClicked: Qt.quit()
    }

    CustomTableView
    {
        id: spinningRect
        x: 20
        y: 20
        width: 200
        height: 200
        color: "red"
        onColorChanged: console.log("color was changed");
        transformOrigin: "Center"
        PropertyAnimation on rotation {
                        from: 0
                        to: 360
                        duration: 5000
                        loops: Animation.Infinite
                    }
    }

}
