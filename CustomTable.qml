import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Item
{
    id: body

    function appendHeader(string, orientation)
    {
        var myModel = tableView.getModel();

        myModel.appendHeaderItem(string,orientation);
    }

    function addData(row, column, data)
    {
        var myModel = tableView.getModel();

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

            var rowHeight = myModel.rowHeightAt(i);

            verticalHeader.setRowHeight(i,rowHeight);
        }

        for(var j = 0;j < horizontalHeader.dataCount();j++)
        {
            var hHeaderValue = myModel.headerData(j,1);

            horizontalHeader.setData(j,hHeaderValue);

            var columnWidth = myModel.columnWithAt(j);

            horizontalHeader.setCellWidth(j,columnWidth);
        }
    }

    GridLayout
    {
        id: mainLayout
        rows: 2
        columns: 2

        rowSpacing: 0
        columnSpacing: 0

        anchors.centerIn: body

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

        CustomTableView {
            id: tableView

            Layout.column: 1
            Layout.row: 1

            Layout.fillHeight: true
            Layout.fillWidth: true

            cellColor: "transparent"
            cellBorderWidth: 1

            onDataHasChanged: {
                if(getModel().rowCount() > 0 || getModel().columnCount() > 0)
                    upperTopLeftCell.visible = true
                else
                    upperTopLeftCell.visible = false
            }
        }
    }


    Component.onCompleted:
    {
        appendHeader("Kent KillerHertz",1);
        appendHeader("Martin Hansen",1);
        appendHeader("Per",1);

        addData(0,0,20);
        addData(1,0,17);
        addData(2,0,20);
        addData(0,1,12);
        addData(1,1,15);
        addData(2,1,11);
        addData(0,2,5);
    }
}
