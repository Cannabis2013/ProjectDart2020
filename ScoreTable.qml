import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Item
{
    id: tableView
    function appendHeader(string)
    {
        myModel.appendHeaderItem(string,1);
    }

    function addData(row,column, data)
    {
        var result = myModel.appendData(row,column,data);

        if(!result)
        {
            Qt.quit();
        }

        var modelRowCount = myModel.rowCount();
        var modelColumnCount = myModel.columnCount();

        verticalHeader.model = modelRowCount;
        horizontalHeader.model = modelColumnCount;

        for(var i = 0;i < verticalHeader.dataCount();i++)
        {
            var vHeaderValue = myModel.headerData(i,2);
            verticalHeader.setData(i,vHeaderValue);
        }

        for(var j = 0;j < horizontalHeader.dataCount();j++)
        {
            var hHeaderValue = myModel.headerData(j,1);
            horizontalHeader.setData(j,hHeaderValue);
        }
    }

    GridLayout
    {
        id: mainLayout
        rows: 2
        columns: 2

        rowSpacing: 0
        columnSpacing: 0

        onWidthChanged: tableView.width = width
        onHeightChanged: tableView.height = height

        Rectangle
        {
            id: upperTopLeftCell
            Layout.row: 0
            Layout.column: 0


            visible: false

            color: "transparent"
        }

        HorizontalHeader {
            id: horizontalHeader
        }
        VerticalHeader {
            id: verticalHeader
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
        addData(0,2,5);
    }


}

