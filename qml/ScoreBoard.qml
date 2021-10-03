import QtQuick 2.12
import QtQuick.Layouts 1.3

import "scoreboardscripts.js" as ScoreBoardScripts

ScoreBoardInterface{
    id: scoreBoardBody
    color: "transparent"
    signal requestUpdateCells()
    onRequestUpdateCells: scoreBoardTableView.forceLayout()
    signal notifyCellPosition(int x, int y)
    // Row/column related
    property int minimumColumnCount: 1
    // Horizontal header properties and signals
    signal setVerticalHeaderHeightAt(int i,int h)
    onSetVerticalHeaderHeightAt: scoreBoardVHeader.setRowHeight(i,h)
    signal setHorizontalHeaderWidthAt(int j, int w)
    onSetHorizontalHeaderWidthAt: scoreBoardHHeader.setColumnWidth(j,w)
    onSetHorizontalHeaderDataAt: scoreBoardHHeader.setData(j,val)
    onSetHorizontalHeaderModel: scoreBoardHHeader.model = m
    onHorizontalHeaderVisibleChanged: scoreBoardHHeader.visible = horizontalHeaderVisible
    readonly property int horizontalHeaderHeight: scoreBoardHHeader.height
    readonly property int verticalHeaderWidth: scoreBoardVHeader.width
    readonly property int horizontalHeaderCount: scoreBoardHHeader.dataCount
    property int horizontalHeaderModel: scoreBoardHHeader.model
    onHorizontalHeaderModelChanged: scoreBoardHHeader.model = horizontalHeaderModel
    // Vertical header properties and signals
    onSetVerticalHeaderModel: scoreBoardVHeader.model = m
    onSetVerticalHeaderDataAt: scoreBoardVHeader.setData(i,val)
    onVerticalHeaderVisibleChanged: scoreBoardVHeader.visible = verticalHeaderVisible
    onVerticalHeaderWidthChanged: scoreBoardVHeader.width = verticalHeaderWidth
    property int verticalHeaderModel: scoreBoardVHeader.model
    onVerticalHeaderModelChanged: scoreBoardVHeader.model = verticalHeaderModel
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

    GridLayout
    {
        id: mainLayout
        anchors.fill: parent
        rows: 2
        columns: 2
        rowSpacing: 0
        columnSpacing: 0
        ScoreBoardVHeader {
            id: scoreBoardVHeader
            Layout.column: 0
            Layout.fillHeight: true
            Layout.row: 1
        }
        ScoreBoardHHeader {
            id: scoreBoardHHeader
            Layout.column: 1
            Layout.fillWidth: true
            Layout.minimumHeight: 45
            Layout.row: 0
        }
        ScoreBoardTableView {
            id: scoreBoardTableView
            Layout.row: 1
            Layout.column: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            onContentXChanged: scoreBoardHHeader.contentX = contentX
            onContentYChanged: scoreBoardVHeader.contentY = contentY
        }
    }
}
