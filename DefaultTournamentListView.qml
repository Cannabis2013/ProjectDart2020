import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory

ListComponent {
    id: tournamentListView
    color: "white"
    radius: 15
    componentTitle: "Tournaments"
    titleBackground: "steelblue"
    itemTitleBackgroundColor: "blue"
    itemBackgroundColor: "transparent"
    itemTitleTextColor: "white"
    itemDescriptionFontColor: "white"
    itemDescriptionBackgroundColor: "steelblue"
    itemImageUrl: "qrc:/pictures/Ressources/darttournamentmod.png"
    itemImageBackgroundColor: "darkblue"
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
