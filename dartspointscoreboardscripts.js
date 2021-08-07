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
    multiColumnPointBoard.requestUpdateCells();
}

function updateContentDimensions()
{
    var tHeight = calculateHeight();
    var tWidth = calculateWidth();
    multiColumnPointBoard.updateContentDimensions(tHeight,tWidth);
}

function refreshHeaders()
{
    refreshHorizontalHeader();
    refreshVerticalHeader();
}

function refreshHorizontalHeader()
{
    let count = dartsDataModel.columnCount;
    multiColumnPointBoard.horizontalHeaderModel = count;
    for(var i = 0; i < count;i++)
    {
        let hHeaderValue = horizontalHeaderModel.roundByAttempt(i);
        let columnWidth = 128;
        multiColumnPointBoard.setHorizontalHeaderWidthAt(i,columnWidth);
        multiColumnPointBoard.setHorizontalHeaderDataAt(i,hHeaderValue);
    }
}

function refreshVerticalHeader()
{
    let headerCount = verticalHeaderModel.count();
    multiColumnPointBoard.verticalHeaderModel = headerCount;
    for(var i = 0;i < headerCount;i++)
    {
        let vHeaderValue = verticalHeaderModel.item(i);
        let rowHeight = 64;
        multiColumnPointBoard.setRowHeight(i,rowHeight);
        multiColumnPointBoard.setVerticalHeaderDataAt(i,vHeaderValue);
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
        var w = 128;
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
        var h = 64;
        totalHeight += h;
    }
    return totalHeight;
}

function setViewPosition(x,y)
{
    multiColumnPointBoard.updateViewPosition(x,y);
}

function appendHeader(header)
{
    verticalHeaderModel.appendItem(header);
    var preferedWidth = 128;
    multiColumnPointBoard.updateVerticalHeaderWidth(preferedWidth);
}

function setData(playerName,score,point){
    let indexOf = verticalHeaderModel.indexOf(playerName);
    var result = dartsDataModel.insertData(indexOf,point,score);
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
        appendHeader(assignedPlayerName);
        multiColumnPointBoard.setData(assignedPlayerName,0,defaultVal);
    }
}

function clearAll()
{
    dartsDataModel.clearData();
    verticalHeaderModel.clear();
}

function handleTextChanged(text,ref)
{
    notifyCellPosition(ref.x,ref.y);
    convertInputFromJson(text,ref);
}

function convertInputFromJson(json,ref)
{
    var j = JSON.parse(json);
    ref.point = j["point"];
    ref.score = j["score"];
}
