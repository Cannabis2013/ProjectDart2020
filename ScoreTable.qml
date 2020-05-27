import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Item
{
    function appendHeader(string)
    {
        myModel.appendHeaderItem(string,2);
    }

    function addData(row,column, data)
    {
        var result = myModel.appendData(row,column,data);

        if(!result)
        {
            Qt.quit();
        }

        verticalHeaderRepeater.model = myModel.rowCount();
        horizontalHeaderRepeater.model = myModel.columnCount();

        for(var i = 0;i < verticalHeaderRepeater.count;i++)
        {
            var value = myModel.headerData(i,2);
            var item = verticalHeaderRepeater.itemAt(i).children[0].text = value;
        }
    }

    GridLayout
    {
        anchors.centerIn: parent

        rows: 2
        columns: 2

        rowSpacing: 0
        columnSpacing: 0

        Rectangle
        {
            id: upperTopLeftCell
            Layout.row: 0
            Layout.column: 0

            width: 100
            height: 25

            visible: false


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

                // Signal handling
                onDataChanged: {(myModel.rowCount() > 0 || myModel.columnCount() > 0) ?
                                    upperTopLeftCell.visible = true : upperTopLeftCell.visible = false}
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

    Component.onCompleted:
    {
        appendHeader("Kent KillerHertz");
        appendHeader("Martin Hansen");
        appendHeader("Per");

        addData(0,0,20);
        addData(1,0,17);
        addData(2,0,20);
        addData(0,1,12);
        addData(1,1,15);
        addData(2,1,11);
    }
}

