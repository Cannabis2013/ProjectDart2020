import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory

ListComponent {
    id: playersListView
    componentTitle: "Assign players"
    titleBackground: "steelblue"
    itemTitleBackgroundColor: "blue"
    itemBackgroundColor: "transparent"
    itemTitleTextColor: "white"
    itemDescriptionFontColor: "white"
    itemDescriptionBackgroundColor: "steelblue"
    itemHoveredColor: "lightblue"
    itemImageUrl: "qrc:/pictures/Ressources/skull.png"
    itemImageBackgroundColor: "darkblue"
    color: "white"
    radius: 15
    itemTitleFontSize: 16
    itemWidth: playersListView.width*0.95
    itemHeight: 50
    allowCheckState: true
    allowMultipleSelections: true
    instantSelectEnabled: true
    onItemSelected: evaluateItemSelectedChanged()
}
