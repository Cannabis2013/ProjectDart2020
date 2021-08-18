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

function clearTable(){
    dartsDataModel.clearData();
}

function refreshHeaders()
{
    // Refresh h/v headers
    refreshHorizontalHeader();
    refreshVerticalHeader();
    // Update flickable content to align table to header sections
    updateContentDimensions();
}

function refreshHorizontalHeader()
{
    let count = dartsDataModel.columnCount;
    pmcBoard.horizontalHeaderModel = count;
    for(var i = 0; i < count;i++)
    {
        let hHeaderValue = horizontalHeaderModel.roundByAttempt(i);
        let columnWidth = tableColumnWidths.columnWidthAt(i);
        pmcBoard.setHorizontalHeaderWidthAt(i,columnWidth);
        pmcBoard.setHorizontalHeaderDataAt(i,hHeaderValue);
    }
}

function refreshVerticalHeader()
{
    let headerCount = verticalHeaderModel.count();
    pmcBoard.verticalHeaderModel = headerCount;
    for(var row = 0;row < headerCount;row++)
    {
        let vHeaderValue = verticalHeaderModel.item(row);
        let rowHeight = tableHeightProvider.rowHeightAt(row);
        pmcBoard.setVerticalHeaderHeightAt(row,rowHeight);
        pmcBoard.setVerticalHeaderDataAt(row,vHeaderValue);
    }
}

function updateContentDimensions()
{
    var tHeight = calculateHeight();
    var tWidth = calculateWidth();
    pmcBoard.updateContentDimensions(tHeight,tWidth);
}

function calculateHeight()
{
    return totalHeaderHeight();
}

function calculateWidth()
{
    return totalColumnsWidth();
}

function updateScoreBoard()
{
    updateContentDimensions();
    refreshHeaders();
    pmcBoard.requestUpdateCells();
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
        var h = 96;
        totalHeight += h;
    }
    return totalHeight;
}

function setViewPosition(x,y)
{
    pmcBoard.updateViewPosition(x,y);
}

function setData(playerName,score,point){
    let indexOf = verticalHeaderModel.indexOf(playerName);
    var result = dartsDataModel.insertData(indexOf,point,score);
    updateWidths(indexOf);
    if(!result)
        print("Couldn't add data to model");
}

function takeData(playerName){
    var indexOf = verticalHeaderModel.indexOf(playerName);
    updateWidths(indexOf);
    var result = dartsDataModel.removeLastItem(indexOf);
    if(!result)
        print("Couldn't take data");
}

function updateWidths(indexOfPlayer)
{
    var column = dartsDataModel.lastDecoratedColumn(indexOfPlayer);
    var data = dartsDataModel.columnData(column);
    var gw = fontsMetric.width(data,tableFonts.pointFontFamily,tableFonts.pointFontSize,
                               tableFonts.scoreFontFamily,tableFonts.scoreFontSize);
    tableColumnWidths.updateColumnWidth(column,gw);
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

function columnWidthAt(column)
{
    var w = tableColumnWidths.columnWidthAt(column);
    setHorizontalHeaderWidthAt(column,w);
    return w;
}
function rowHeightAt(row)
{
    var h = tableHeightProvider.rowHeightAt(row);
    setVerticalHeaderHeightAt(row,h);
    return h;
}
