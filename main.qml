import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import CustomItems 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    color: "lightgray"

    function addData(row,column, data)
    {
        myModel.appendData(row,column,data);
    }

    title: qsTr("Dart2020")

    TableView
    {
        x: 0
        y: 0
        anchors.fill: parent
        clip: true

        model: CustomTableModel
        {
            id: myModel
        }

        delegate: Rectangle{
            border.color: "black"
            border.width: 1
            implicitWidth: 25
            implicitHeight: 25


            Text {
                id: txt
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                text: display
            }
        }
    }
    Component.onCompleted: {
        addData(0,0,4)
        addData(0,1,2)
        addData(3,4,5)
    }
}
