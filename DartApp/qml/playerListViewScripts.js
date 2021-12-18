function currentIndexes()
{
    var cIndexes = [];
    var j = 0;
    for(var i = 0;i < listView.count;i++)
    {
        var item = listView.itemAtIndex(i);
        var itemState = item.state;
        if(itemState === "checked")
            cIndexes[j++] = i;
    }
    return cIndexes;
}
function unSelectAll()
{
    for(var i = 0;i < listView.count;i++)
    {
        var item = listView.itemAtIndex(i);
        var itemState = item.state;
        if(itemState === "checked")
            item.state = "";
    }
}
function addItemModel(itemModel)
{
    listModel.append(itemModel);
}
function removeItemModels(indexes)
{
    var length = indexes.length;
    for(var i = 0;i < length;i++){
        var index = indexes[i];
        listModel.remove(index);
    }
}
