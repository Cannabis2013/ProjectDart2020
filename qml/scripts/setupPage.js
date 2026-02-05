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

function selectPlayer(index){
  const model = playerListModel.get(index)
  const currentCount = selectedInfo.count
  selectedInfo.count = model.selected ? currentCount - 1 :
                                        currentCount + 1
  model.selected = !model.selected
  model.placeIndex = selectedInfo.count
}

function init(){
  const playerNames = ["Bulder Max","Jes","Simone Lazare",
    "Rasmus Clemmesen","Hjalte Grønnegård","Bjarke Grønnegård",
    "Ewelina Januszanis","Laila Kjærbo suhr","Lars Skousen",
    "Benjamin Weiss Juhler","Storm","Louise Juhler","Peter C. Block",
    "Eric Molinares","Kent KillerHertz","Per Blindbæk","Kasper Hansen",
    "Muraat Kaan","Thomas Mante","Thomas Gerald","Sune Nørlem",
    "Jesper Ulvedal","Nicolai Hansen","Per Hansen","Team 1","Team 2",
    "Team 3","Team 4"];

  playerNames.forEach(playerName => {
    playerListModel.append({
                             "name": playerName,
                             "selected": false,
                             "placeIndex" : -1})
  })
}
