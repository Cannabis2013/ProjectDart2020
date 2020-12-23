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
}

function updateContentDimensions()
{
    var tHeight = totalHeaderHeight();
    var tWidth = totalColumnsWidth();
    body.updateContentDimensions(tHeight,tWidth);
}

function refreshHeaders()
{
    // Refresh horizontal headers
    body.horizontalHeaderModel = myModel.columnCount;
    let hDataCount = body.horizontalHeaderCount;
    for(var j = 0;j < hDataCount;j++)
    {
        let hHeaderValue = myModel.getHeaderData(j,Qt.Horizontal);
        let columnWidth = myModel.columnWidthAt(j);
        body.setColumnWidth(j,columnWidth);
        body.setHorizontalHeaderDataAt(j,hHeaderValue);
    }
    // Refresh vertical headers
    let headerCount = myModel.headerItemCount(Qt.Vertical);
    body.verticalHeaderModel = headerCount;
    for(var i = 0;i < headerCount;i++)
    {
        let vHeaderValue = myModel.getHeaderData(i,Qt.Vertical);
        let rowHeight = myModel.rowHeightAt(i);
        body.setRowHeight(i,rowHeight);
        body.setVerticalHeaderDataAt(i,vHeaderValue);
    }
    body.requestUpdateCells();
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
    body.updateViewPosition(x,y);
}

function appendHeader(header,orientation)
{
    myModel.appendHeaderItem(header,headerOrientation);
    var preferedWidth = myModel.preferedHeaderItemWidth(orientation);
    body.updateVerticalHeaderWidth(preferedWidth);
}

function setData(playerName,point,score){
    var result = myModel.insertData(playerName,point,score);
    if(!result)
        print("Couldn't add data to model");
}

function takeData(playerName){
    var result = myModel.removeLastItem(playerName,-1);
    if(!result)
        print("Couldn't take data");
}

function editData(row,column,point,score){
    var result = myModel.editData(row,column,point,score);
    if(!result)
        print("Couldn't edit data");
}
