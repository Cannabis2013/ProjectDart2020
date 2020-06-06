import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Item
{
    id: body

    // Functions

    function appendHeader(string, orientation)
    {
        var myModel = tableView.getModel();

        myModel.appendHeaderItem(string,orientation);

        //verticalHeader.cellWidth = myModel.preferedCellWidth();
        //upperTopLeftCell.width = myModel.preferedCellWidth();
    }

    function addData(row, column, data)
    {
        var myModel = tableView.getModel();

        var result = myModel.appendData(row,column,data);

        if(!result)
        {
            print("Couldn't add data to model");
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

        anchors.fill: parent
        MyRectangle
        {
            id: upperTopLeftCell

            height: 25

            Layout.row: 0
            Layout.column: 0

            rightBorderWidth: 1
            bottomBorderWidth: 1

            Layout.fillWidth: true
            Layout.fillHeight: true

            visible: true

            color: "darkgray"
        }

        HorizontalHeader {
            id: horizontalHeader

            backgroundColor: "darkgray"
            color: "black"

            borderWidth: 1

            Layout.fillHeight: true
        }
        VerticalHeader {
            id: verticalHeader

            backgroundColor: "darkgray"
            color: "black"

            Layout.fillWidth: true

            borderWidth: 1

            Layout.alignment: Qt.AlignTop
        }

        CustomTableView {
            id: tableView

            Layout.column: 1
            Layout.row: 1

            cellBorderWidth: 1

            Layout.fillHeight: true
            Layout.fillWidth: true

            cellColor: "transparent"

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
    }
}
