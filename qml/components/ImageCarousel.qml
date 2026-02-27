import QtQuick 6.0
import QtQuick.Controls 6.0
import "../components"

Item{
  id: imageCaroussel

  property var sources: []
  onSourcesChanged: carouselRepeater.model = sources

  QtObject{
    id: carousselData
    property int interval: 2500
  }

  SwipeView{
      id: carouselSwipeView
      interactive: false
      anchors.fill: parent
      orientation: Qt.Vertical
      clip: true
      Timer{
          id: carrouselTime
          interval: carousselData.interval
          running: true
          repeat: true
          onTriggered: {
            const number = Math.random() * 100000
            const max = sources.length
            carouselSwipeView.currentIndex = Math.floor(number % max)
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
