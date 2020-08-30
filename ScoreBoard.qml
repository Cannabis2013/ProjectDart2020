import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

Rectangle{
    id: scoreBoardBody
    clip: true

    function viewContentWidth(){return flickableTable.contentWidth;}
    function viewContentHeight(){return flickableTable.contentHeight;}

    property int headerOrientation: Qt.Vertical
    onHeaderOrientationChanged: myModel.setHeaderOrientation(headerOrientation)
    property int pointFontSize: 16
    onPointFontSizeChanged: {
        myModel.pointFontPointSize = pointFontSize;
        cellDelegate.pointFontSize = pointFontSize;
    }

    property int scoreFontSize: 16
    onScoreFontSizeChanged: {
        myModel.scoreFontPointSize = scoreFontSize;
        cellDelegate.scoreFontSize = scoreFontSize;
    }

    property bool displayPoints: false
    onDisplayPointsChanged:  cellDelegate.pointDisplayVisible = displayPoints

    property int pointDisplayWidth: 20
    onPointDisplayWidthChanged: cellDelegate.pointDisplayWidth = pointDisplayWidth

    property int pointDisplayHeight: 20


    property int horizontalHeaderHeight: 20
    onHorizontalHeaderHeightChanged: horizontalHeader.height = horizontalHeaderHeight
    property bool staticVerticalHeaderWidth: false
    property int verticalHeaderWidth: 25
    onVerticalHeaderWidthChanged: verticalHeader.width = verticalHeaderWidth
    property int verticalHeaderFillMode: 0x02
    onVerticalHeaderFillModeChanged: myModel.verticalFillMode = verticalHeaderFillMode
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: cellDelegate.borderWidth = cellBorderWidth
    property int throwsPerRound: 3
    onThrowsPerRoundChanged: myModel.throwCount = throwsPerRound;
    property int minimumColumnsCount: 0
    onMinimumColumnsCountChanged: setMinimumColumnsCount(minimumColumnsCount)
    function setInitialValue(value)
    {
        myModel.setInitialValue(value);
    }

    function setMinimumColumnsCount(count)
    {
        myModel.setMinimumColumnCount(count);
    }

    function getHeaderItemCount(orientation){
        var count = myModel.headerItemCount(orientation);
        return count;
    }

    function clearTable(){
        myModel.clearData();
    }

    function getHeaderItem(index, orientation)
    {
        var item = myModel.getHeaderData(index,orientation);
        return item;
    }

    function appendHeader(string)
    {
        myModel.appendHeaderItem(string);
        var preferedWidth = myModel.preferedCellWidth();
        verticalHeader.width = preferedWidth*1.05;
        flickableVHeader.Layout.minimumWidth = preferedWidth*1.05;
    }

    function appendData(playerName, point,score){
        var result = myModel.appendData(playerName,point,score);
        if(!result)
            print("Couldn't add data to model");
    }
    function takeData(playerName)
    {
        var result = myModel.removeLastItem(playerName);
        if(!result)
            print("Couldn't take data");
    }
    function editData(row,column,point,score)
    {
        var result = myModel.editData(row,column,point,score);
        if(!result)
            print("Couldn't edit data");
    }

    function updateScoreBoard()
    {
        updateContentDimensions();
        refreshHeaders();

        //flickableTable.contentX = flickableTable.contentWidth - flickableTable.width;
    }

    function updateContentDimensions()
    {
        var tHeight = totalHeaderHeight();
        var tWidth = totalColumnsWidth();
        flickableVHeader.contentHeight = tHeight;
        flickableTable.contentHeight = tHeight;
        flickableTable.contentWidth = tWidth;
        flickableHHeader.contentWidth = tWidth;
    }

    function refreshHeaders()
    {
        var nIndex = horizontalHeader.dataCount();
        horizontalHeader.model = myModel.columnCount;
        var hDataCount = horizontalHeader.dataCount();
        for(var j = 0;j < hDataCount;j++)
        {
            var hHeaderValue = myModel.getHeaderData(j,1);
            horizontalHeader.setData(j,hHeaderValue);
            var columnWidth = myModel.columnWidthAt(j);
            horizontalHeader.setColumnWidth(j,columnWidth);
        }

        var headerCount = myModel.headerItemCount(0x2);
        verticalHeader.model = headerCount;
        for(var i = 0;i < headerCount;i++)
        {
            var vHeaderValue = myModel.getHeaderData(i,2);
            var rowHeight = myModel.rowHeightAt(i);
            verticalHeader.setRowHeight(i,rowHeight);
            verticalHeader.setData(i,vHeaderValue);
        }
        tableView.forceLayout();
    }

    function totalColumnsWidth()
    {
        var columnCount = myModel.columnCount;
        var result = 0;
        for(var c = 0;c < columnCount;c++){
            var w = myModel.columnWidthAt(c);
            result += w;
        }
        return result;
    }

    function totalHeaderHeight()
    {
        var rowCount = myModel.rowCount();
        var totalHeight = 0;
        for(var r = 0;r < rowCount;r++)
        {
            var h = myModel.rowHeightAt(r);
            totalHeight += h;
        }
        return totalHeight;
    }

    function setViewPosition(x,y)
    {
        flickableTable.contentX = x;
        flickableTable.contentY = y
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
            onContentXChanged: flickableHHeader.contentX = contentX
            onContentYChanged: flickableVHeader.contentY = contentY

            TableView {
                id: tableView
                interactive: false
                clip: true
                anchors.fill: parent
                columnWidthProvider: function(column)
                {
                    return myModel.columnWidthAt(column);
                }

                rowHeightProvider: function(row)
                {
                    return myModel.rowHeightAt(row);
                }

                model: ScoreModel {
                    id: myModel
                    onDataChanged: updateScoreBoard();
                    throwCount : scoreBoardBody.throwsPerRound
                    headerOrientation: scoreBoardBody.headerOrientation
                    pointFontPointSize: scoreBoardBody.pointFontSize
                    scoreFontPointSize: scoreBoardBody.scoreFontSize
                    scale: 2
                }

                delegate: CellDelegate {
                    id: cellDelegate
                    cellBorderWidth: scoreBoardBody.cellBorderWidth
                    cellColor: "purple"
                    scoreFontSize: scoreBoardBody.scoreFontSize
                    pointFontSize: scoreBoardBody.pointFontSize
                    pointDisplayVisible: scoreBoardBody.displayPoints
                    pointDisplayWidth: scoreBoardBody.pointDisplayWidth
                    onNotifyLocation: setViewPosition(x,y)
                    text: display
                }
            }
        }
    }
}
