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
    dataModel.setInitialValue(value);
}

function clearTable(){
    dataModel.clearData();
    playerDataModel.clear();
}

function updateScoreBoard()
{
    updateContentHeight();
}

function updateContentHeight()
{
    var h = calculateTotalHeight();
    scoreBoardBody.updateContentHeight(h);
}

function calculateTotalHeight()
{
    var count = dataModel.rowCount();
    var total = 0;
    for(var i = 0;i < count;i++)
        total += 64;
    return total;
}

function setViewPosition(x,y)
{
    scoreBoardBody.updateViewPosition(x,y);
}

function appendHeader(header)
{
    playerDataModel.addPlayer(header);
    var headerWidth = fontsMetric.width(header,tableFonts.headerFontFamily,tableFonts.headerFontSize);
    var headerHeight = fontsMetric.height(header,tableFonts.headerFontFamily,tableFonts.headerFontSize);
    var i = playerDataModel.indexOf(header);
    tableHeightProvider.updateRowHeight(i,headerHeight);
    var scaledWidth = scaleWidth(headerWidth);
    updateVerticalHeaderWidth(scaledWidth);
}

function scaleWidth(w)
{
    return w*1.25;
}

function updateVerticalHeaderWidth(w)
{
    if(w > scoreBoardBody.verticalHeaderWidth)
        scoreBoardBody.updateVerticalHeaderWidth(w);
}

function setData(playerName,score,min,mid,max){
    let index = playerDataModel.indexOf(playerName);
    updatePlayerDataModel(playerName,min,mid,max);
    var result = dataModel.insertData(index,score);
    if(result)
        updateWidths(index);
}

function updatePlayerDataModel(playerName,min,mid,max)
{
    if(!isNaN(mid))
        playerDataModel.setMid(playerName,mid);
    playerDataModel.setMin(playerName,min);
    playerDataModel.setMax(playerName,max);
}

function takeData(row,column,playerName){
    let indexOf = playerNamesModel.indexOf(playerName);
    var result = dataModel.removeLastItem(indexOf,headerOrientation);
    if(result)
        updateWidths(indexOf);
}

function updateWidths(indexOfPlayer)
{
    var data = dataModel.columnData(0);
    var gw = fontsMetric.width(data,tableFonts.scoreFontFamily,tableFonts.scoreFontSize);
    tableWidthProvider.updateColumnWidth(0,gw);
}

function setHeaderData(data,defaultVal)
{
    for(var i = 0; i < data.length;i++)
    {
        var assignedPlayerName = data[i];
        scoreBoardBody.appendHeader(assignedPlayerName,Qt.Vertical);
        scoreBoardBody.setData(assignedPlayerName,defaultVal,0.0,0,0);
    }
}

function setDelegateText(text,ref)
{
    var j = JSON.parse(text);
    ref.score = j["score"];
}

function updateDelegate(text,ref,row)
{
    ref.lowerValue = playerDataModel.min(row);
    ref.averageValue = playerDataModel.mid(row);
    ref.upperValue = playerDataModel.max(row);
    if(text === undefined)
        return "text";
    return text;
}
