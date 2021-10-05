import QtQuick 2.12
import QtQuick.Layouts 1.3

import "scoreboardscripts.js" as ScoreBoardScripts

ScoreBoardInterface{
    id: scoreBoardBody
    color: "transparent"
    height: ScoreBoardScripts.calculateHeight()
    signal requestUpdateCells()
    onRequestUpdateCells: scoreBoardTableView.forceLayout()
    signal notifyCellPosition(int x, int y)
    // Row/column related
    property int minimumColumnCount: 1
    // Horizontal header properties and signals
    signal setHorizontalHeaderWidthAt(int j, int w)
    // Table view related
    // Move focus to last updated cell when data has changed
    signal updateViewPosition(int x,int y)
    onUpdateViewPosition: ScoreBoardScripts.updateViewPosition(x,y)
    signal updateContentDimensions(int h, int w)
    onUpdateContentDimensions: ScoreBoardScripts.updateContentDimensions(h,w)
    signal updateContentHeight(int h)
    onUpdateContentHeight: scoreBoardTableView.contentHeight = h
    // Model property
    property QtObject model: scoreBoardTableView.model
    onModelChanged: scoreBoardTableView.model = model
    // Cell delegate
    property Component cellDelegate: Rectangle{}
    onCellDelegateChanged: scoreBoardTableView.cellDelegate = cellDelegate
    // Update vertical header width
    signal updateVerticalHeaderWidth(int w)
    onUpdateVerticalHeaderWidth: ScoreBoardScripts.updateVerticalHeaderWidth(w)
    // Update column widths from datamodel
    property var columnWidthProvider: function(){}
    onColumnWidthProviderChanged: scoreBoardTableView.columnWidthProvider = columnWidthProvider
    // Update row height from datamodel
    property var rowHeightProvider: function(){}
    onRowHeightProviderChanged: scoreBoardTableView.rowHeightProvider = rowHeightProvider
    // Data model visualization related
    property double fontScale: 1
    readonly property int tableDisplayWidth: scoreBoardTableView.width
    ScoreBoardTableView {
        id: scoreBoardTableView
        anchors.fill: parent
        Layout.row: 1
        Layout.column: 1
        Layout.fillWidth: true
        Layout.fillHeight: true
    }
}
