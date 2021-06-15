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
    datamodel.setInitialValue(value);
}

function clearTable(){
    datamodel.clearData();
}

function getHeaderItem(index, orientation)
{
    var item = datamodel.getHeaderData(index);
    return item;
}

function updateScoreBoard()
{
    refreshHeaders();
}

function refreshHeaders()
{
    // Refresh horizontal headers
    let verticalHeaderCount = datamodel.verticalHeaderCount();
    singleColumnPointBoard.verticalHeaderModel = verticalHeaderCount;
    for(var j = 0;j < verticalHeaderCount;j++)
    {
        let h = datamodel.rowHeightAt(j);
        let value = datamodel.getHeaderData(j);
        singleColumnPointBoard.setRowHeight(j,h);
        singleColumnPointBoard.setVerticalHeaderDataAt(j,value);
    }
}

function setViewPosition(x,y)
{
    singleColumnPointBoard.updateViewPosition(x,y);
}

function appendHeader(header)
{
    datamodel.appendHeaderItem(header);
    var preferedWidth = datamodel.preferedHeaderItemWidth();
    singleColumnPointBoard.updateVerticalHeaderWidth(preferedWidth);
}

function setData(playerName,point ,score){
    var result = datamodel.insertData(playerName,point,score);
    if(!result)
        print("Couldn't add data to model");
}

function takeData(row,column,playerName){
    var result = datamodel.removeLastItem(playerName,headerOrientation);
    if(!result)
        print("Couldn't take data");
}

function editData(row,column,point,score){
    var result = datamodel.editData(row,column,point,score);
    if(!result)
        print("Couldn't edit data");
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

