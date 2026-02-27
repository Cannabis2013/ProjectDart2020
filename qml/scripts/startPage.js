function createRect(){
  return {
    x: 0,
    y: 0,
    w: 0,
    h: 0
  }
}

function isPortrait(){
  return startPage.height > startPage.width
}

function titleRect(){
  const rect = createRect()
  const padding = 32

  rect.x = padding
  rect.h = padding

  if(isPortrait()){
    rect.w = startPage.width - 2*padding
  }
  return rect
}

function carouselRect(){
  const rect = createRect()

  if(isPortrait()){
    rect.h = 160
    rect.w = rect.h
    return rect
  }

  let carouselSideLength = startPage.width - 512 <= 232 ? parent.width - 232 :
                                                          parent.height *0.5

  rect.h = carouselSideLength
  rect.w = carouselSideLength
  return rect
}

function carouselSources(){
  return [
      "qrc:/qml/Ressources/lukelittler.png",
      "qrc:/qml/Ressources/vanGerwen.png",
      "qrc:/qml/Ressources/bunting.png",
      "qrc:/qml/Ressources/tuborgclassic.png",
      "qrc:/qml/Ressources/tuborggroen.png",
      "qrc:/qml/Ressources/tuborggroenflaske.png"
    ]
}

function buttonsLayoutRect(){
  const rect = createRect()

  rect.y = startPage.height > 640 ? (startPage.height - rect.h) / 2 : 8
  rect.x = isPortrait() ? (startPage.width - rect.w) / 2 : startPage.width - rect.w - 32

  return rect
}
