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
    playerNamesModel.clear();
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
    playerNamesModel.appendItem(header);
    appendStatsItems();
    var headerWidth = fontsMetric.width(header,tableFonts.headerFontFamily,tableFonts.headerFontSize);
    var headerHeight = fontsMetric.height(header,tableFonts.headerFontFamily,tableFonts.headerFontSize);
    var i = playerNamesModel.indexOf(header);
    tableHeightProvider.updateRowHeight(i,headerHeight);
    var scaledWidth = scaleWidth(headerWidth);
    updateVerticalHeaderWidth(scaledWidth);
}

function appendStatsItems()
{
    middleValues.appendItem(0.0);
    minimumValues.appendItem(0);
    maximumValues.appendItem(0);
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

function setData(playerName,score,average, lowerVal, upperVal){
    let index = playerNamesModel.indexOf(playerName);
    updateStatistics(index,average,lowerVal,upperVal);
    var result = dataModel.insertData(index,score);
    if(!result)
        print("Couldn't add data to model");
    else
        updateWidths(index);
}

function updateStatistics(index,average,lowerVal,upperVal)
{
    if(!isNaN(average))
        middleValues.setItem(average,index);
    minimumValues.setItem(lowerVal,index);
    maximumValues.setItem(upperVal,index);
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
        singleColumnPointBoard.setData(assignedPlayerName,defaultVal,0,0,0);
    }
}

function setDelegateText(text,ref)
{
    var j = JSON.parse(text);
    ref.score = j["score"];
}

function updateDelegate(text,ref,row)
{
    ref.averageValue = middleValues.item(row);
    ref.lowerValue = minimumValues.item(row);
    ref.upperValue = maximumValues.item(row);
    if(text === undefined)
        return "text";
    return text;
}
