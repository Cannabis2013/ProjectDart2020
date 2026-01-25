function createRect(){
  return {
    x: 0,
    y: 0,
    w: 0,
    h: 0
  }
}

function carouselRect(){
  const isPortrait = startPage.height > startPage.width
  const rect = createRect()

  if(isPortrait){
    rect.h = 160
    rect.w = rect.h
    rect.x = (startPage.width - rect.h) / 2
    rect.y = 8
    return rect
  }

  let carouselSideLength = startPage.width - 512 <= 208 ? parent.width - 208 :
                                                          parent.height *0.75

  rect.h = carouselSideLength
  rect.w = carouselSideLength
  rect.y = startPage.height - carouselSideLength
  return rect
}

function carouselSources(){
  if(startPage.height <= startPage.width || startPage.height >= 700)
    return [
        "qrc:/pictures/Ressources/Pictures/lukelittler.png",
        "qrc:/pictures/Ressources/Pictures/vanGerwen.png",
        "qrc:/pictures/Ressources/Pictures/bunting.png"
      ]
  return []
}

function buttonsLayoutRect(){
  const rect = createRect()
  const isPortrait = startPage.height > startPage.width

  rect.w = 200
  rect.h = 288
  rect.y = startPage.height > 640 ? (startPage.height - rect.h) / 2 : 8
  rect.x = isPortrait ? (startPage.width - rect.w) / 2 : startPage.width - rect.w - 8

  return rect
}
