function isLandscape() {
  return width > height || width >= 800;
}

function initializeController() {
  let item = null;
  const models = []

  for(let i = 0; i < playerListModel.count;i++)
    models.push(playerListModel.get(i))

  const selectedNames = models.filter(m => m.selected)
                       .sort((a,b) => a.placeIndex - b.placeIndex)
                       .map(m => m.name)

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
  dartsInitializer.init(JSON.stringify(values))
  return true
}

function handlePlayerClicked(index){
  const model = playerListModel.get(index)
  if(model.selected)
    unSelectPlayer(model)
  else
    selectPlayer(model)
  firstIndex.text = `Next place: ${selectedInfo.placeIndexes[0]}`
}

function selectPlayer(model){
  model.selected = true
  const modelIndex = model.placeIndex
  model.placeIndex = selectedInfo.placeIndexes.shift()
  selectedInfo.countIndex++
}

function unSelectPlayer(model){
  selectedInfo.placeIndexes.unshift(model.placeIndex)
  model.selected = false
  model.placeIndex = -1
  selectedInfo.countIndex--
  selectedInfo.placeIndexes = selectedInfo.placeIndexes.sort((a,b) => a - b)
}

function unSelectAll(){
  let model
  let modelIndex
  for(let index = 0;index < playerListModel.count;index++){
    model = playerListModel.get(index)
    if(!model.selected)
      continue
    modelIndex = model.placeIndex
    model.placeIndex = -1
    selectedInfo.placeIndexes.unshift(modelIndex)
    model.selected = false
  }
  selectedInfo.placeIndexes = selectedInfo.placeIndexes.sort((a,b) => a - b)
  firstIndex.text = `Next place: ${selectedInfo.placeIndexes[0]}`
  selectedInfo.countIndex = 0
}

function init(){
  const playerNames = ["Bulder Max","Jes","Simone Lazare",
    "Rasmus Clemmesen","Hjalte Grønnegård","Bjarke Grønnegård",
    "Ewelina Januszanis","Laila Kjærbo suhr","Lars Skousen",
    "Benjamin Weiss Juhler","Storm","Louise Juhler","Peter C. Block",
    "Eric Molinares","Kent KillerHertz","Per Blindbæk","Kasper Hansen",
    "Muraat Kaan","Thomas Mante","Thomas Gerald","Sune Nørlem",
    "Jesper Ulvedal","Nicolai Hansen","Per Hansen"];

  playerNames.forEach(playerName => {
    playerListModel.append({
                             "name": playerName,
                             "selected": false,
                             "placeIndex" : -1})
  })

  for(let i = 1;i <= playerNames.length;i++)
    selectedInfo.placeIndexes.push(i)

  firstIndex.text = `Next place: ${selectedInfo.placeIndexes[0]}`
}
