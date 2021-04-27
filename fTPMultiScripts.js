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
    fTPModel.setInitialValue(value);
}

function getHeaderItemCount(orientation){
    var count = fTPModel.headerItemCount(orientation);
    return count;
}

function clearTable(){
    fTPModel.clearData();
}

function getHeaderItem(index, orientation)
{
    var item = fTPModel.getHeaderData(index,orientation);
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
    fTPBody.horizontalHeaderModel = fTPModel.columnCount;
    let hDataCount = fTPBody.horizontalHeaderCount;
    for(var j = 0;j < hDataCount;j++)
    {
        let hHeaderValue = fTPModel.getHeaderData(j,Qt.Horizontal);
        let columnWidth = fTPModel.columnWidthAt(j);
        fTPBody.setColumnWidth(j,columnWidth);
        fTPBody.setHorizontalHeaderDataAt(j,hHeaderValue);
    }
    // Refresh vertical headers
    let headerCount = fTPModel.headerItemCount(Qt.Vertical);
    fTPBody.verticalHeaderModel = headerCount;
    for(var i = 0;i < headerCount;i++)
    {
        let vHeaderValue = fTPModel.getHeaderData(i,Qt.Vertical);
        let rowHeight = fTPModel.rowHeightAt(i);
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
    var columnCount = fTPModel.columnCount;
    var result = 0;
    for(var c = 0;c < columnCount;c++){
        var w = fTPModel.columnWidthAt(c);
        result += w;
    }
    return result;
}

function totalHeaderHeight()
{
    var rowCount = fTPModel.rowCount();
    var totalHeight = 0;
    for(var r = 0;r < rowCount;r++)
    {
        var h = fTPModel.rowHeightAt(r);
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
    fTPModel.appendHeaderItem(header,headerOrientation);
    var preferedWidth = fTPModel.preferedHeaderItemWidth();
    fTPBody.updateVerticalHeaderWidth(preferedWidth);
}

function setData(playerName,point,score){
    var result = fTPModel.insertData(playerName,point,score);
    if(!result)
        print("Couldn't add data to model");
}

function takeData(playerName,){
    var result = fTPModel.removeLastItem(playerName,-1);
    if(!result)
        print("Couldn't take data");
}

function editData(row,column,point,score){
    var result = fTPModel.editData(row,column,point,score);
    if(!result)
        print("Couldn't edit data");
}

function addHeaderData(data)
{
    for(var i = 0; i < data.length;i++)
    {
        var assignedPlayerName = data[i];
        scoreBoardItemSlot.item.appendHeader(assignedPlayerName,Qt.Horizontal);
        scoreBoardItemSlot.item.setData(assignedPlayerName,0,defaultVal,undefined);
    }
}
