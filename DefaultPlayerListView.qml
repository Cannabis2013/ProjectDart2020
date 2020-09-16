import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory

ListComponent {
    id: playersListView
    componentTitle: "Assign players"
    titleBackground: "transparent"
    itemBackgroundColor: "transparent"
    itemTitleBackgroundColor: Qt.rgba(0.6,0.33,0.24,0.8)
    itemTitleTextColor: "black"
    itemDescriptionFontColor: "black"
    itemDescriptionBackgroundColor: Qt.rgba(0.6,0.33,0.24,0.8)
    itemHoveredColor: "lightblue"
    itemImageUrl: "qrc:/pictures/Ressources/skull.png"
    itemImageBackgroundColor: Qt.rgba(0.6,0.33,0.24,0.8)
    color: Qt.rgba(0,0,0,0.1)
    radius: 15
    itemTitleFontSize: 24
    itemDescriptionFontSize: 16
    itemWidth: playersListView.width*0.95
    itemHeight: 50
    allowCheckState: true
    allowMultipleSelections: true
    instantSelectEnabled: true
    onItemSelected: evaluateItemSelectedChanged()
}
