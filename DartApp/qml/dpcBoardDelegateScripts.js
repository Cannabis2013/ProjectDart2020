function updateDelegate(text,ref,row){
    ref.minValue = playerDataModel.min(row);
    ref.midValue = playerDataModel.mid(row);
    ref.maxValue = playerDataModel.max(row);
    ref.itemEnabled = true;
    if(text === undefined)
        return "text";
    return text;
}
