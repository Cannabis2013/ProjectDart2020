function viewContentWidth()
{
    return flickableTable.contentWidth;
}
function viewContentHeight()
{
    return flickableTable.contentHeight;
}
function setInitialValue(value)
{
    myModel.setInitialValue(value);
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
        var hHeaderValue = myModel.getHeaderData(j,scoreBoardBody.headerOrientation);
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
