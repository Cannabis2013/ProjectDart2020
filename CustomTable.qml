import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Rectangle{
    clip: true
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

        verticalHeader.Layout.minimumWidth = preferedWidth*1.05;
        upperTopLeftCell.Layout.minimumWidth = verticalHeader.width;
        upperTopLeftCell.Layout.minimumHeight = 25;
        upperTopLeftCell.Layout.maximumHeight = 25;
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
        return tableView.width
    }

    GridLayout
    {
        id: mainLayout

        anchors.fill: parent

        rows: 2
        columns: 2

        rowSpacing: 0
        columnSpacing: 0


        MyRectangle
        {
            id: upperTopLeftCell

            height: 25

            Layout.row: 0
            Layout.column: 0

            Layout.minimumWidth: 128

            rightBorderWidth: 1
            bottomBorderWidth: 1

            color: "transparent"

            onWidthChanged: {
                if(width == 0)
                    width = verticalHeader.width;
            }
        }

        VerticalHeader {
            id: verticalHeader

            Layout.row: 1
            Layout.column: 0

            Layout.fillHeight: true

            backgroundColor: "lightgray"
            color: "black"

            borderWidth: 1

            Layout.alignment: Qt.AlignTop
        }

        Flickable{
            id: flickableTable

            clip: true

            Layout.row: 0
            Layout.column: 1

            Layout.rowSpan: 2

            contentHeight: contentItem.childrenRect.height
            contentWidth: contentItem.childrenRect.width

            boundsMovement: Flickable.StopAtBounds

            Layout.alignment: Qt.AlignTop

            Layout.fillWidth: true
            Layout.fillHeight: true

            GridLayout{
                id: flickableLayout
                anchors.fill: flickableLayout.contentItem

                rowSpacing: 0
                columnSpacing: 0

                flow: GridLayout.TopToBottom

                HorizontalHeader {
                    id: horizontalHeader

                    Layout.fillWidth: true
                    Layout.minimumHeight: 25

                    backgroundColor: "lightgray"
                    color: "black"

                    borderWidth: 1

                }

                CustomTableView {
                    id: tableView

                    cellBorderWidth: 1

                    Layout.fillHeight: true
                    Layout.fillWidth: true

                    Layout.minimumHeight: verticalHeader.height
                    Layout.maximumHeight: verticalHeader.height

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
    Component.onCompleted: {

    }
}
