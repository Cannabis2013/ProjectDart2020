.import "dpcboardgeometry.js" as GeometryScripts

function clearTable(){
    dataModel.clearData();
    playerDataModel.clear();
    itemsEnabled(false);
}

function setInitialValue(value){
    dataModel.setInitialValue(value);
}

function setData(playerName,score,min,mid,max,inGame){
    let index = playerDataModel.indexOf(playerName);
    updatePlayerDataModel(playerName,min,mid,max,inGame);
    var result = dataModel.insertData(index,score);
    if(!result)
        print("Couldn't add data to model");
    else
        GeometryScripts.updateWidths(index);
}

function updatePlayerDataModel(playerName,min,mid,max,inGame)
{
    if(!isNaN(mid))
        playerDataModel.setMid(playerName,mid);
    playerDataModel.setMin(playerName,min);
    playerDataModel.setMax(playerName,max);
    playerDataModel.setInGame(playerName,inGame);
}

function takeData(row,column,playerName){
    var result = dataModel.removeLastItem(playerName,headerOrientation);
    if(!result)
        print("Couldn't take data");
}
