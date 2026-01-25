import QtQuick 6.0
import QtQuick.Controls 6.0
import "../components"

Item{
  id: imageCaroussel

  property var sources: []
  onSourcesChanged: carouselRepeater.model = sources
  property int interval: 5000

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
              const index = carouselSwipeView.currentIndex
              if(index < imageCarousel.sources.length - 1)
                  carouselSwipeView.currentIndex += 1
              else
                  carouselSwipeView.currentIndex = 0
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
