import QtQuick 2.4
import QtQuick.Layouts 1.3

import "tournamentPageScripts.js" as Scripts

DefaultTournamentListView {
    id: tournamentListView
    allowMultipleSelections: false
    allowCheckState: false
    instantSelectEnabled: true
    itemTitleTextColor: ThemeContext.tournamentListViewTextColor
    itemDescriptionFontColor: ThemeContext.tournamentListViewTextColor
    titleTextColor: ThemeContext.tournamentListViewTextColor
}
