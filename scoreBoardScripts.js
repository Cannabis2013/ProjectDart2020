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
    var tHeight = calculateHeight();
    var tWidth = calculateWidth();
    //fTPBody.updateContentDimensions(tHeight,tWidth);
}

function refreshHeaders()
{
    // Refresh horizontal headers
    fTPBody.horizontalHeaderModel = myModel.columnCount;
    let w = fTPBody.width / myModel.columnCount;
    let hDataCount = fTPBody.horizontalHeaderCount;
    for(var j = 0;j < hDataCount;j++)
    {
        let hHeaderValue = myModel.getHeaderData(j,Qt.Horizontal);
        let columnWidth = w;
        fTPBody.setColumnWidth(j,columnWidth);
        fTPBody.setHorizontalHeaderDataAt(j,hHeaderValue);
    }
    // Refresh vertical headers
    let headerCount = myModel.headerItemCount(Qt.Vertical);
    fTPBody.verticalHeaderModel = headerCount;
    for(var i = 0;i < headerCount;i++)
    {
        let vHeaderValue = myModel.getHeaderData(i,Qt.Vertical);
        let rowHeight = myModel.rowHeightAt(i);
        fTPBody.setRowHeight(i,rowHeight);
        fTPBody.setVerticalHeaderDataAt(i,vHeaderValue);
    }
    fTPBody.requestUpdateCells();
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
    fTPBody.updateViewPosition(x,y);
}

function appendHeader(header,orientation)
{
    myModel.appendHeaderItem(header,headerOrientation);
    var preferedWidth = myModel.preferedHeaderItemWidth();
    fTPBody.updateVerticalHeaderWidth(preferedWidth);
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
