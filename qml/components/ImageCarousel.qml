import QtQuick 6.0
import QtQuick.Controls 6.0
import "../components"

Item{
  id: imageCaroussel

  property var sources: []
  onSourcesChanged: carouselRepeater.model = sources
  property int interval: 2500

  QtObject{
    id: randomInfo
    readonly property int seed: new Date().getTime()
  }

  SwipeView{
      id: carouselSwipeView
      interactive: false
      anchors.fill: parent
      orientation: Qt.Vertical
      clip: true
      Timer{
          id: carrouselTime
          interval: imageCaroussel.interval
          running: true
          repeat: true
          onTriggered: {
            const max = sources.length
            const r = Math.random() * 1000 + randomInfo.seed
            carouselSwipeView.currentIndex = Math.floor(r % max)
          }
      }
      Repeater{
        id: carouselRepeater
        model: imageCaroussel.sources
        Loader{
          active: SwipeView.isCurrentItem
          sourceComponent: Image {
            id: gerwenImage
            source: imageCaroussel.sources[index]
            fillMode: Image.PreserveAspectFit
          }
        }
      }
    }
    Component.onCompleted: carouselSwipeView.currentIndex = imageCaroussel.sources.length - 1
}
