function addHeaderData(data,defaultVal)
{
    for(var i = 0; i < data.length;i++)
    {
        var assignedPlayerName = data[i];
        appendHeader(assignedPlayerName);
        pmcBoard.setData(assignedPlayerName,0,defaultVal);
    }
}
function appendHeader(header)
{
    verticalHeaderModel.appendItem(header);
    var preferedWidth = fontsMetric.width(header,tableFonts.headerFontFamily,tableFonts.headerFontSize);
    var preferedHeight = fontsMetric.height(header,tableFonts.headerFontFamily,tableFonts.headerFontSize);
    var i = verticalHeaderModel.indexOf(header);
    tableHeightProvider.updateRowHeight(i,preferedHeight);
    updateSections(preferedWidth);
}

function updateSections(hWidth)
{
    var w = pmcBoard.verticalHeaderWidth;
    if(hWidth > w)
        pmcBoard.updateVerticalHeaderWidth(hWidth);
}
