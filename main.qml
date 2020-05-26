import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    color: "lightgray"

    x:240
    y:240
    width: 400
    height: 300

    function addData(row,column, data)
    {
        myModel.appendData(row,column,data);

        verticalHeaderRepeater.model = myModel.rowCount();
        horizontalHeaderRepeater.model = myModel.columnCount();

        for(var i = 0;i < verticalHeaderRepeater.count;i++)
        {
            var value = myModel.headerData(i,2,0);
            var item = verticalHeaderRepeater.itemAt(i).children[0].text = value;
        }
    }

    title: qsTr("Dart2020")

    GridLayout
    {
        anchors.centerIn: parent

        rows: 2
        columns: 2

        rowSpacing: 0
        columnSpacing: 0

        Rectangle
        {
            Layout.row: 0
            Layout.column: 0

            width: 100
            height: 25


            color: "gray"
        }

        Row
        {
            id: horizontalHeader
            Layout.row: 0
            Layout.column: 1
            Repeater
            {
                id: horizontalHeaderRepeater
                model: myModel.columnCount();
                Rectangle {
                    id: horizontalHeaderCell
                    border.color: "black"
                    border.width: 1
                    color: "gray"
                    width: 25
                    height: 25
                    Text {
                        id: headerCellText
                    }
                }

            }
        }
        Column
        {
            id: verticalHeader
            Layout.row: 1
            Layout.column: 0
            Repeater
            {
                id: verticalHeaderRepeater
                model: myModel.rowCount()
                Rectangle {
                    border.color: "black"
                    border.width: 1
                    color: "gray"
                    width: 100
                    height: 25

                    Text {
                        id: verticalHeaderCellText
                        text: "Column text"
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                    }
                }

            }
        }

        TableView
        {
            Layout.row: 1
            Layout.column: 1

            Layout.fillHeight: true
            Layout.fillWidth: true

            clip: true

            model: CustomTableModel
            {
                id: myModel
            }

            delegate: Rectangle{
                border.color: "green"
                border.width: 1
                implicitWidth: 25
                implicitHeight: 25
                color: "black"

                Text {
                    horizontalAlignment: Text.AlignHCenter
                    verticalAlignment: Text.AlignVCenter
                    anchors.fill: parent
                    text: display
                    color: "white"
                }
            }
        }
    }



    Component.onCompleted: {
        addData(0,0,4)
        addData(0,1,2)
        addData(1,0,1)
        addData(1,1,20)
        addData(2,0,15)
    }
}
