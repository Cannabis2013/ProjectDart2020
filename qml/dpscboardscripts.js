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
    averageValuesModel.appendItem(0.0);
    var headerWidth = fontsMetric.width(header,tableFonts.headerFontFamily,tableFonts.headerFontSize);
    var headerHeight = fontsMetric.height(header,tableFonts.headerFontFamily,tableFonts.headerFontSize);
    var i = playerNamesModel.indexOf(header);
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

function setData(playerName,point ,score, average){
    let indexOf = playerNamesModel.indexOf(playerName);
    if(!isNaN(average))
        averageValuesModel.setItem(average,indexOf);
    var result = dataModel.insertData(indexOf,point,score);
    if(!result)
        print("Couldn't add data to model");
    else
        updateWidths(indexOf);
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
        var assignedPlayerName = data[i];
        singleColumnPointBoard.appendHeader(assignedPlayerName,Qt.Vertical);
        singleColumnPointBoard.setData(assignedPlayerName,0,defaultVal,0.0);
    }
}

function setDelegateText(text,ref)
{
    var j = JSON.parse(text);
    ref.score = j["score"];
}
