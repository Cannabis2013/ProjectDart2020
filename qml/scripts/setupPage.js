function isLandscape() {
  return width > height || width >= 800;
}

function initializeController() {
  let item = null;
  let selectedNames = [];
  for(let i = 0; i < playerListModel.count;i++){
    item = playerListModel.get(i);
    if(item.selected)
      selectedNames.push(item.name);
  }

  if (selectedNames.length <= 0)
    return false;

  const selectedOpenMod = openingSelector.current;
  let openMod = '';
  if (selectedOpenMod === "Number")
    openMod = 'S';
  else if (selectedOpenMod === "Double")
    openMod = 'D';
  else if (selectedOpenMod === "Tripple")
    openMod = 'T';

  const closeningMod = closeningSelector.current;

  let closeMod = '';
  if (closeningMod === "Number")
    closeMod = 'S';
  else if (closeningMod === "Double")
    closeMod = 'D';

  const values = {
    "players": selectedNames,
    "initialScore": parseInt(initialScoreSelector.current),
    "openingMod": openMod,
    "closeningMod": closeMod
  };
  dartsInitializer.init(JSON.stringify(values));
  return true;
}

function selectPlayer(index){
  const model = playerListModel.get(index)
  const currentCount = selectedInfo.count
  selectedInfo.count = model.selected ? currentCount - 1 :
                                        currentCount + 1
  model.selected = !model.selected
}
