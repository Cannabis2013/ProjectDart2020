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
    multiAttemptScoreDataModel.setInitialValue(value);
}

function clearTable(){
    multiAttemptScoreDataModel.clearData();
}

function getHeaderItem(index, orientation)
{
    var item = multiAttemptScoreDataModel.getHeaderData(index);
    return item;
}

function updateScoreBoard()
{
    refreshHeaders();
}

function refreshHeaders()
{
    // Refresh horizontal headers
    let verticalHeaderCount = multiAttemptScoreDataModel.verticalHeaderCount();
    multiAttemptScoreBoardBody.verticalHeaderModel = verticalHeaderCount;
    for(var j = 0;j < verticalHeaderCount;j++)
    {
        let h = multiAttemptScoreDataModel.rowHeightAt(j);
        let value = multiAttemptScoreDataModel.getHeaderData(j);
        multiAttemptScoreBoardBody.setRowHeight(j,h);
        multiAttemptScoreBoardBody.setVerticalHeaderDataAt(j,value);
    }
}

function setViewPosition(x,y)
{
    multiAttemptScoreBoardBody.updateViewPosition(x,y);
}

function appendHeader(header)
{
    multiAttemptScoreDataModel.appendHeaderItem(header);
    var preferedWidth = multiAttemptScoreDataModel.preferedHeaderItemWidth();
    multiAttemptScoreBoardBody.updateVerticalHeaderWidth(preferedWidth);
}

function setData(playerName,score){
    var result = multiAttemptScoreDataModel.insertData(playerName,score);
    if(!result)
        print("Couldn't add data to model");
}

function takeData(row,column,playerName){
    var result = multiAttemptScoreDataModel.removeLastItem(playerName,headerOrientation);
    if(!result)
        print("Couldn't take data");
}

function editData(row,column,point,score){
    var result = multiAttemptScoreDataModel.editData(row,column,point,score);
    if(!result)
        print("Couldn't edit data");
}

function setHeaderData(data,defaultVal)
{
    for(var i = 0; i < data.length;i++)
    {
        var assignedPlayerName = data[i];
        multiAttemptScoreBoardBody.appendHeader(assignedPlayerName,Qt.Vertical);
        multiAttemptScoreBoardBody.setData(assignedPlayerName,defaultVal);
    }
}
