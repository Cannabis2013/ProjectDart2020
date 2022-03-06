function viewContentWidth(){
    return flickableTable.contentWidth;
}

function viewContentHeight(){
    return flickableTable.contentHeight;
}

function updateWidths(indexOfPlayer){
    var data = dataModel.columnData(0);
    var gw = fontsMetric.width(data,tableFonts.pointFontFamily,tableFonts.pointFontSize,
                               tableFonts.scoreFontFamily,tableFonts.scoreFontSize);
    tableWidthProvider.updateColumnWidth(0,gw);
}

function calculateTotalHeight(){
    var count = dataModel.rowCount();
    var total = 0;
    for(var i = 0;i < count;i++)
        total += 64;
    return total;
}

function scaleWidth(w){
    return w*1.25;
}

function setViewPosition(x,y){
    dpcScoreBoard.updateViewPosition(x,y);
}

function updateContentHeight()
{
    var h = calculateTotalHeight();
    scoreBoardBody.updateContentHeight(h);
}
