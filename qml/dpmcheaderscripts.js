function addHeaderData(data,defaultVal)
{
    for(var i = 0; i < data.length;i++)
    {
        var assignedPlayerName = data[i];
        appendHeader(assignedPlayerName);
        dpmcBoard.setData(assignedPlayerName,0,defaultVal);
    }
}
function appendHeader(header)
{
    verticalHeaderModel.appendItem(header);
    var preferedWidth = fontsMetric.width(header,dpmcTableFonts.headerFontFamily,dpmcTableFonts.headerFontSize);
    var preferedHeight = fontsMetric.height(header,dpmcTableFonts.headerFontFamily,dpmcTableFonts.headerFontSize);
    var i = verticalHeaderModel.indexOf(header);
    tableHeightProvider.updateRowHeight(i,preferedHeight);
    updateSections(preferedWidth);
}

function updateSections(hWidth)
{
    var w = dpmcBoard.verticalHeaderWidth;
    if(hWidth > w)
        dpmcBoard.updateVerticalHeaderWidth(hWidth);
}
