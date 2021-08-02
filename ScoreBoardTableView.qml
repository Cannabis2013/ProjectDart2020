import QtQuick 2.12
import QtQuick.Layouts 1.3

import "scoreboardscripts.js" as ScoreBoardScripts

Flickable{
    id: flickableTable
    clip: true
    boundsMovement: Flickable.StopAtBounds
    property QtObject model: tableView.model
    onModelChanged: tableView.model = model
    property Component cellDelegate: Rectangle{}
    onCellDelegateChanged: tableView.delegate = cellDelegate
    property var columnWidthProvider: function(){}
    onColumnWidthProviderChanged: tableView.columnWidthProvider = columnWidthProvider
    property var rowHeightProvider: function(){}
    onRowHeightProviderChanged: tableView.rowHeightProvider = rowHeightProvider
    signal forceLayout()
    onForceLayout: tableView.forceLayout()
    TableView {
        id: tableView
        interactive: false
        clip: true
        anchors.fill: parent
    }
}
