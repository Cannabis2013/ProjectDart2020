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
    multiAttemptDataModel.setInitialValue(value);
}

function clearTable(){
    multiAttemptDataModel.clearData();
}

function getHeaderItem(index, orientation)
{
    var item = multiAttemptDataModel.getHeaderData(index);
    return item;
}

function updateScoreBoard()
{
    refreshHeaders();
}

function refreshHeaders()
{
    // Refresh horizontal headers
    let verticalHeaderCount = multiAttemptDataModel.verticalHeaderCount();
    scoreSingleColumnBody.verticalHeaderModel = verticalHeaderCount;
    for(var j = 0;j < verticalHeaderCount;j++)
    {
        let h = multiAttemptDataModel.rowHeightAt(j);
        let value = multiAttemptDataModel.getHeaderData(j);
        scoreSingleColumnBody.setRowHeight(j,h);
        scoreSingleColumnBody.setVerticalHeaderDataAt(j,value);
    }
}

function setViewPosition(x,y)
{
    scoreSingleColumnBody.updateViewPosition(x,y);
}

function appendHeader(header)
{
    multiAttemptDataModel.appendHeaderItem(header);
    var preferedWidth = multiAttemptDataModel.preferedHeaderItemWidth();
    scoreSingleColumnBody.updateVerticalHeaderWidth(preferedWidth);
}

function setData(playerName,score){
    var result = multiAttemptDataModel.insertData(playerName,score);
    if(!result)
        print("Couldn't add data to model");
}

function takeData(row,column,playerName){
    var result = multiAttemptDataModel.removeLastItem(playerName,headerOrientation);
    if(!result)
        print("Couldn't take data");
}

function editData(row,column,point,score){
    var result = multiAttemptDataModel.editData(row,column,point,score);
    if(!result)
        print("Couldn't edit data");
}

function setHeaderData(data,defaultVal)
{
    for(var i = 0; i < data.length;i++)
    {
        var assignedPlayerName = data[i];
        scoreSingleColumnBody.appendHeader(assignedPlayerName,Qt.Vertical);
        scoreSingleColumnBody.setData(assignedPlayerName,defaultVal);
    }
}
