function getHeaderItemCount(orientation){
    var myModel = tableView.getModel();
    var count = myModel.headerItemCount(orientation);
    return count;
}

function getHeaderItem(index, orientation)
{
    var myModel = tableView.getModel();
    var item = myModel.headerData(index,orientation);
    return item;
}

function appendHeader(string, orientation)
{
    var myModel = tableView.getModel();

    myModel.appendHeaderItem(string,orientation);

    var preferedWidth = myModel.preferedCellWidth();

    verticalHeader.width = preferedWidth*1.05;
    flickableVHeader.Layout.minimumWidth = preferedWidth*1.05;
}

function appendData(playerName, data, orientation){
    var myModel = tableView.getModel();

    var result = myModel.appendData(playerName,data, orientation);

    if(!result)
    {
        print("Couldn't add data to model");
        Qt.quit();
    }

    verticalHeader.model = myModel.rowCount();
    horizontalHeader.model = myModel.columnCount();

    for(var i = 0;i < verticalHeader.dataCount();i++)
    {
        var vHeaderValue = myModel.headerData(i,2);
        verticalHeader.setData(i,vHeaderValue);
    }

    for(var j = 0;j < horizontalHeader.dataCount();j++)
    {
        var hHeaderValue = myModel.headerData(j,1);

        horizontalHeader.setData(j,hHeaderValue);

        var columnWidth = myModel.columnWidthAt(j);

        horizontalHeader.setColumnWidth(j,columnWidth);
    }

    flickableTable.contentWidth = totalColumnsWidth();
    flickableHHeader.contentWidth = totalColumnsWidth();
}

function addData(row, column, data)
{
    var myModel = tableView.getModel();

    var result = myModel.addData(row,column,data);

    if(!result)
    {
        print("Couldn't add data to model");
        Qt.quit();
    }

    verticalHeader.model = myModel.rowCount();
    horizontalHeader.model = myModel.columnCount();

    for(var i = 0;i < verticalHeader.dataCount();i++)
    {
        var vHeaderValue = myModel.headerData(i,2);
        verticalHeader.setData(i,vHeaderValue);
    }

    for(var j = 0;j < horizontalHeader.dataCount();j++)
    {
        var hHeaderValue = myModel.headerData(j,1);

        horizontalHeader.setData(j,hHeaderValue);

        var columnWidth = myModel.columnWidthAt(j);

        horizontalHeader.setColumnWidth(j,columnWidth);
    }

    flickableTable.contentWidth = totalColumnsWidth();
    flickableHHeader.contentWidth = totalColumnsWidth();
}

function totalColumnsWidth()
{
    var myModel = tableView.getModel();
    var columnCount = myModel.columnCount();
    var result = 0;

    for(var c = 0;c < columnCount;c++){
        var w = myModel.columnWidthAt(c);
        result += w;
    }

    return result;
}

function totalHeaderHeight()
{
    var myModel = tableView.getModel();
    var rowCount = myModel.rowCount();

    var totalHeight = 0;

    for(var r = 0;r < rowCount;r++)
    {
        var h = myModel.rowHeightAt(r);
        totalHeight += h;
    }

    return totalHeight;
}

