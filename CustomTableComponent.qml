import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Rectangle{
    color: "#330000ff"

    radius: 15


    property int horizontalHeaderHeight: 20
    onHorizontalHeaderHeightChanged: horizontalHeader.height = horizontalHeaderHeight

    property bool staticVerticalHeaderWidth: false

    property int verticalHeaderWidth: 25
    onVerticalHeaderWidthChanged: staticVerticalHeaderWidth ?
                                      verticalHeader.width = verticalHeaderWidth :
                                      verticalHeader.width = verticalHeader.width

    property int verticalHeaderFillMode: 0x02
    onVerticalHeaderFillModeChanged: tableView.verticalHeaderFillMode = verticalHeaderFillMode

    function appendHeader(string, orientation)
    {
        var myModel = tableView.getModel();

        myModel.appendHeaderItem(string,orientation);

        var preferedWidth = myModel.preferedCellWidth();

        verticalHeader.cellWidth = preferedWidth;
        verticalHeader.width = preferedWidth
        upperTopLeftCell.width = preferedWidth;
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
        }

        for(var j = 0;j < horizontalHeader.dataCount();j++)
        {
            var hHeaderValue = myModel.headerData(j,1);

            horizontalHeader.setData(j,hHeaderValue);

            var columnWidth = myModel.columnWithAt(j);

            horizontalHeader.setColumnWidth(j,columnWidth);
        }
    }

    function calcContentHeight(){
        return horizontalHeader.height + tableView.height
    }

    function calcContentWidth(){
        return verticalHeader.width + tableView.width
    }


    Flickable
    {
        id: customTableBody

        clip: true

        contentHeight: calcContentHeight()
        contentWidth: calcContentWidth()

        anchors.fill: parent
        anchors.margins: 15

        // Functions

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

                color: "transparent"

                onWidthChanged: {
                    if(width == 0)
                        width = verticalHeader.width;
                }
            }

            HorizontalHeader {
                id: horizontalHeader

                Layout.column: 1
                Layout.row: 0

                backgroundColor: "darkgray"
                color: "black"

                borderWidth: 1

                height: 25
            }
            VerticalHeader {
                id: verticalHeader

                backgroundColor: "darkgray"
                color: "black"

                Layout.column: 0
                Layout.row: 1

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

                cellColor: "white"

                onDataHasChanged: {
                    if(getModel().verticalHeaderCount() > 0)
                        upperTopLeftCell.visible = true
                    else
                        upperTopLeftCell.visible = false
                }
            }
        }
    }
}
