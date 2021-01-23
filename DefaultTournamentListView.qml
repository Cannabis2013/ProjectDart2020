import QtQuick 2.0
import QtQuick.Layouts 1.3

ListViewComponent {
    id: tournamentListView
    radius: 15
    componentTitle: "| Tournaments"
    titleBackground: "white"
    titleBackgroundOpacity: 0.3
    itemBackgroundColor: "gray"
    itemBackgroundOpacity: 0.3

    itemImageUrl: "qrc:/pictures/Ressources/darttournamentmod.png"
    itemSelectedBackgroundColor: "gray"
    itemSelectedtextColor: "black"
    itemHoveredColor: "transparent"
    itemTitleFontSize: 12
    itemTitleTextColor: "white"
    itemDescriptionFontSize: 8
    itemHeight: 64
    allowCheckState: true
    allowMultipleSelections: true
    instantSelectEnabled: true
}
