import QtQuick 2.0
import QtQuick.Layouts 1.3

ListComponent {
    id: playersListView
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
    itemHeight: 60
    allowCheckState: true
    allowMultipleSelections: true
    instantSelectEnabled: true
}
