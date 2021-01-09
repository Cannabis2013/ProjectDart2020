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
    refreshHeaders();
}

function refreshHeaders()
{
    // Refresh horizontal headers
    fTPBody.horizontalHeaderModel = fTPModel.columnCount;
    let columnWidth = fTPBody.width / fTPModel.columnCount;
    let hDataCount = fTPBody.horizontalHeaderCount;
    for(var j = 0;j < hDataCount;j++)
    {
        let hHeaderValue = fTPModel.getHeaderData(j,Qt.Horizontal);
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
    fTPBody.requestUpdateCells();
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

function takeData(playerName,point,score){
    var result = fTPModel.insertData(playerName,point,score);
    if(!result)
        print("Couldn't take data");
}

function editData(row,column,point,score){
    var result = fTPModel.editData(row,column,point,score);
    if(!result)
        print("Couldn't edit data");
}
