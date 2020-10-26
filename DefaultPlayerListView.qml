import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory

ListComponent {
    id: playersListView
    componentTitle: "Assign players"
    titleBackground: "transparent"
    itemBackgroundColor: "gray"
    itemBackgroundOpacity: 0.3
    itemDescriptionFontColor: "white"
    itemHoveredColor: "lightblue"
    itemImageUrl: "qrc:/pictures/Ressources/skull.png"
    radius: 15
    itemTitleFontSize: 12
    itemTitleTextColor: "white"
    itemDescriptionFontSize: 8
    itemWidth: playersListView.width*0.95
    itemHeight: 60
    allowCheckState: true
    allowMultipleSelections: true
    instantSelectEnabled: true
}
