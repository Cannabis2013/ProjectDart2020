import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory

ListComponent {
    id: tournamentListView
    color: Qt.rgba(0,0,0,0.1)
    radius: 15
    componentTitle: "Tournaments"
    titleBackground: "transparent"
    itemTitleBackgroundColor: Qt.rgba(0.6,0.33,0.24,0.8)
    itemBackgroundColor: "transparent"
    itemTitleTextColor: "black"
    itemDescriptionFontColor: "black"
    itemDescriptionBackgroundColor: Qt.rgba(0.6,0.33,0.24,0.8)
    itemImageUrl: "qrc:/pictures/Ressources/darttournamentmod.png"
    itemImageBackgroundColor: Qt.rgba(0.6,0.33,0.24,0.8)
    itemSelectedBackgroundColor: "lightblue"
    itemSelectedtextColor: "black"
    itemHoveredColor: "lightblue"
    itemTitleFontSize: 24
    itemDescriptionFontSize: 16
    itemWidth: tournamentListView.width *0.95
    itemHeight: 64
    allowCheckState: true
    allowMultipleSelections: true
    instantSelectEnabled: false
}
