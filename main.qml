import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import CustomItems 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    color: "lightgray"

    minimumWidth: 480
    maximumWidth: 480

    minimumHeight: 800
    maximumHeight: 800
    title: qsTr("Dart2020")

    MouseArea
    {
        anchors.fill: parent
        onClicked: Qt.quit()
    }



    ScrollView
    {
        width: 480
        height: 320
        clip: true

        x: 0
        y: applicationWindow.height/2 - width/2

        padding: 5

        CustomTableView
        {
            id: tableView

            implicitWidth: bodyWidth
            implicitHeight: bodyHeight


        }
    }    

}
