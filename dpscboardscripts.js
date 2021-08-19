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
    verticalHeaderModel.clear();
}

function getHeaderItem(index, orientation)
{
    var item = dataModel.getHeaderData(index);
    return item;
}

function updateScoreBoard()
{
    refreshVerticalHeader();
}

function refreshVerticalHeader()
{
    let verticalHeaderCount = verticalHeaderModel.count();
    singleColumnPointBoard.verticalHeaderModel = verticalHeaderCount;
    for(var j = 0;j < verticalHeaderCount;j++)
    {
        let h = tableHeightProvider.rowHeightAt(j);
        let value = verticalHeaderModel.item(j);
        scoreBoardBody.setVerticalHeaderHeightAt(j,h);
        scoreBoardBody.setVerticalHeaderDataAt(j,value);
    }
}

function setViewPosition(x,y)
{
    singleColumnPointBoard.updateViewPosition(x,y);
}

function appendHeader(header)
{
    verticalHeaderModel.appendItem(header);
    var preferedWidth = fontsMetric.width(header,tableFonts.headerFontFamily,tableFonts.headerFontSize);
    var preferedHeight = fontsMetric.height(header,tableFonts.headerFontFamily,tableFonts.headerFontSize);
    var i = verticalHeaderModel.indexOf(header);
    tableHeightProvider.updateRowHeight(i,preferedHeight);
    updateVerticalHeaderWidth(preferedWidth);
}

function updateVerticalHeaderWidth(w)
{
    if(w > scoreBoardBody.verticalHeaderWidth)
        scoreBoardBody.updateVerticalHeaderWidth(w);
}

function setData(playerName,point ,score){
    let indexOf = verticalHeaderModel.indexOf(playerName);
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
        singleColumnPointBoard.setData(assignedPlayerName,0,defaultVal);
    }
}

