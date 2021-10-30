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
    itemsEnabled(false);
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
    singleColumnPointBoard.updateViewPosition(x,y);
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

function setData(playerName,score,min,mid,max,inGame){
    let index = playerDataModel.indexOf(playerName);
    updatePlayerDataModel(playerName,min,mid,max,inGame);
    var result = dataModel.insertData(index,score);
    if(!result)
        print("Couldn't add data to model");
    else
        updateWidths(index);
}

function updatePlayerDataModel(playerName,min,mid,max,inGame)
{
    if(!isNaN(mid))
        playerDataModel.setMid(playerName,mid);
    playerDataModel.setMin(playerName,min);
    playerDataModel.setMax(playerName,max);
    playerDataModel.setInGame(playerName,inGame);
}

function takeData(row,column,playerName){
    var result = dataModel.removeLastItem(playerName,headerOrientation);
    if(!result)
        print("Couldn't take data");
}

function updateWidths(indexOfPlayer)
{
    var data = dataModel.columnData(0);
    var gw = fontsMetric.width(data,tableFonts.pointFontFamily,tableFonts.pointFontSize,
                               tableFonts.scoreFontFamily,tableFonts.scoreFontSize);
    tableWidthProvider.updateColumnWidth(0,gw);
}

function setHeaderData(data,defaultVal)
{
    for(var i = 0; i < data.length;i++)
    {
        let assignedPlayerName = data[i];
        singleColumnPointBoard.appendHeader(assignedPlayerName);
        singleColumnPointBoard.setData(assignedPlayerName,defaultVal,0,0,0,false);
    }
}

function setDelegateText(text,ref)
{
    var j = JSON.parse(text);
    ref.score = j["score"];
}

function updateDelegate(text,ref,row)
{
    ref.minValue = playerDataModel.min(row);
    ref.midValue = playerDataModel.mid(row);
    ref.maxValue = playerDataModel.max(row);
    ref.itemEnabled = playerDataModel.in(row);
    if(text === undefined)
        return "text";
    return text;
}
