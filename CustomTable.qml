import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Rectangle{
    id: body

    clip: true

    property int fontSize: 12
    onFontSizeChanged: {

    }

    property int horizontalHeaderHeight: 20
    onHorizontalHeaderHeightChanged: horizontalHeader.height = horizontalHeaderHeight

    property bool staticVerticalHeaderWidth: false

    property int verticalHeaderWidth: 25
    onVerticalHeaderWidthChanged: verticalHeader.width = verticalHeaderWidth

    property int verticalHeaderFillMode: 0x02
    onVerticalHeaderFillModeChanged: tableView.verticalHeaderFillMode = verticalHeaderFillMode

    function getHeaderItemCount(orientation){
        var myModel = tableView.getModel();
        var count = myModel.headerItemCount(orientation);
        return count;
    }

    function getHeaderItem(index, orientation)
    {
        var myModel = tableView.getModel();
        var item = myModel.headerData(index,orientation);
        return item;
    }

    function appendHeader(string, orientation)
    {
        var myModel = tableView.getModel();

        myModel.appendHeaderItem(string,orientation);

        var preferedWidth = myModel.preferedCellWidth();

        verticalHeader.width = preferedWidth*1.05;
        flickableVHeader.Layout.minimumWidth = preferedWidth*1.05;
    }

    function appendData(playerName, data, orientation){
        var myModel = tableView.getModel();

        var result = myModel.appendData(playerName,data, orientation);

        if(!result)
        {
            print("Couldn't add data to model");
            Qt.quit();
        }

        verticalHeader.model = myModel.rowCount();
        horizontalHeader.model = myModel.columnCount();

        for(var i = 0;i < verticalHeader.dataCount();i++)
        {
            var vHeaderValue = myModel.headerData(i,2);
            verticalHeader.setData(i,vHeaderValue);
        }

        for(var j = 0;j < horizontalHeader.dataCount();j++)
        {
            var hHeaderValue = myModel.headerData(j,1);

            horizontalHeader.setData(j,hHeaderValue);

            var columnWidth = myModel.columnWidthAt(j);

            horizontalHeader.setColumnWidth(j,columnWidth);
        }

        flickableTable.contentWidth = totalColumnsWidth();
        flickableHHeader.contentWidth = totalColumnsWidth();
    }

    function addData(row, column, data)
    {
        var myModel = tableView.getModel();

        var result = myModel.addData(row,column,data);

        if(!result)
        {
            print("Couldn't add data to model");
            Qt.quit();
        }

        verticalHeader.model = myModel.rowCount();
        horizontalHeader.model = myModel.columnCount();

        for(var i = 0;i < verticalHeader.dataCount();i++)
        {
            var vHeaderValue = myModel.headerData(i,2);
            verticalHeader.setData(i,vHeaderValue);
        }

        for(var j = 0;j < horizontalHeader.dataCount();j++)
        {
            var hHeaderValue = myModel.headerData(j,1);

            horizontalHeader.setData(j,hHeaderValue);

            var columnWidth = myModel.columnWidthAt(j);

            horizontalHeader.setColumnWidth(j,columnWidth);
        }

        flickableTable.contentWidth = totalColumnsWidth();
        flickableHHeader.contentWidth = totalColumnsWidth();
    }

    function totalColumnsWidth()
    {
        var myModel = tableView.getModel();
        var columnCount = myModel.columnCount();
        var result = 0;

        for(var c = 0;c < columnCount;c++){
            var w = myModel.columnWidthAt(c);
            result += w;
        }

        return result;
    }

    function totalHeaderHeight()
    {
        var myModel = tableView.getModel();
        var rowCount = myModel.rowCount();

        var totalHeight = 0;

        for(var r = 0;r < rowCount;r++)
        {
            var h = myModel.rowHeightAt(r);
            totalHeight += h;
        }

        return totalHeight;
    }

    GridLayout
    {
        id: mainLayout

        anchors.fill: parent

        rows: 2
        columns: 2

        rowSpacing: 0
        columnSpacing: 0

        Flickable{
            id: flickableVHeader

            clip: true

            Layout.fillHeight: true

            Layout.row: 1
            Layout.column: 0

            interactive: false

            VerticalHeader {
                id: verticalHeader
                anchors.fill: parent

                backgroundColor: "lightgray"
                color: "black"

                borderWidth: 1

                Layout.alignment: Qt.AlignTop
            }
        }

        Flickable{
            id: flickableHHeader

            clip: true

            Layout.fillWidth: true
            Layout.minimumHeight: 25

            contentHeight: 25

            Layout.row: 0
            Layout.column: 1

            interactive: false

            HorizontalHeader {
                id: horizontalHeader

                anchors.fill: flickableHHeader.contentItem

                backgroundColor: "lightgray"
                color: "black"

                borderWidth: 1
            }
        }

        Flickable{
            id: flickableTable

            clip: true

            Layout.row: 1
            Layout.column: 1

            Layout.fillWidth: true
            Layout.fillHeight: true

            boundsMovement: Flickable.StopAtBounds


            onContentXChanged: {
                flickableHHeader.contentX = contentX
            }
            onContentYChanged : {
                flickableVHeader.contentY = contentY;
            }

            CustomTableView {
                id: tableView

                anchors.fill: parent

                cellBorderWidth: 1

                cellColor: "white"
            }
        }
    }
    Component.onCompleted: {
        var tHeight = totalHeaderHeight();
        flickableVHeader.contentHeight = tHeight;
        flickableTable.contentHeight = tHeight;
    }
}
