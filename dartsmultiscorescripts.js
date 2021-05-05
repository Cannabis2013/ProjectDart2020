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
    dartsDataModel.setInitialValue(value);
}

function getHeaderItemCount(orientation){
    var count = dartsDataModel.headerItemCount(orientation);
    return count;
}

function clearTable(){
    dartsDataModel.clearData();
}

function getHeaderItem(index, orientation)
{
    var item = dartsDataModel.getHeaderData(index,orientation);
    return item;
}

function updateScoreBoard()
{
    updateContentDimensions();
    refreshHeaders();
    fTPBody.requestUpdateCells();
}

function updateContentDimensions()
{
    var tHeight = calculateHeight();
    var tWidth = calculateWidth();
    fTPBody.updateContentDimensions(tHeight,tWidth);
}

function refreshHeaders()
{
    // Refresh horizontal headers
    fTPBody.horizontalHeaderModel = dartsDataModel.columnCount;
    let hDataCount = fTPBody.horizontalHeaderCount;
    for(var j = 0;j < hDataCount;j++)
    {
        let hHeaderValue = dartsDataModel.getHeaderData(j,Qt.Horizontal);
        let columnWidth = dartsDataModel.columnWidthAt(j);
        fTPBody.setColumnWidth(j,columnWidth);
        fTPBody.setHorizontalHeaderDataAt(j,hHeaderValue);
    }
    // Refresh vertical headers
    let headerCount = dartsDataModel.headerItemCount(Qt.Vertical);
    fTPBody.verticalHeaderModel = headerCount;
    for(var i = 0;i < headerCount;i++)
    {
        let vHeaderValue = dartsDataModel.getHeaderData(i,Qt.Vertical);
        let rowHeight = dartsDataModel.rowHeightAt(i);
        fTPBody.setRowHeight(i,rowHeight);
        fTPBody.setVerticalHeaderDataAt(i,vHeaderValue);
    }
}

function calculateHeight()
{
    return totalHeaderHeight();
}

function calculateWidth()
{
    return totalColumnsWidth();
}

function totalColumnsWidth()
{
    var columnCount = dartsDataModel.columnCount;
    var result = 0;
    for(var c = 0;c < columnCount;c++){
        var w = dartsDataModel.columnWidthAt(c);
        result += w;
    }
    return result;
}

function totalHeaderHeight()
{
    var rowCount = dartsDataModel.rowCount();
    var totalHeight = 0;
    for(var r = 0;r < rowCount;r++)
    {
        var h = dartsDataModel.rowHeightAt(r);
        totalHeight += h;
    }
    return totalHeight;
}

function setViewPosition(x,y)
{
    fTPBody.updateViewPosition(x,y);
}

function appendHeader(header,orientation)
{
    dartsDataModel.appendHeaderItem(header,headerOrientation);
    var preferedWidth = dartsDataModel.preferedHeaderItemWidth();
    fTPBody.updateVerticalHeaderWidth(preferedWidth);
}

function setData(playerName,score){
    var result = dartsDataModel.insertData(playerName,score);
    if(!result)
        print("Couldn't add data to model");
}

function takeData(playerName,){
    var result = dartsDataModel.removeLastItem(playerName,-1);
    if(!result)
        print("Couldn't take data");
}

function editData(row,column,score){
    var result = dartsDataModel.editData(row,column,score);
    if(!result)
        print("Couldn't edit data");
}

function addHeaderData(data,defaultVal)
{
    for(var i = 0; i < data.length;i++)
    {
        var assignedPlayerName = data[i];
        scoreBoardItemSlot.item.appendHeader(assignedPlayerName,Qt.Horizontal);
        scoreBoardItemSlot.item.setData(assignedPlayerName,0,defaultVal,undefined);
    }
}
