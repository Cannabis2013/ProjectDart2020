import QtQuick 2.12
import QtQuick.Layouts 1.3

import "scoreboardscripts.js" as ScoreBoardScripts

ScoreBoardInterface{
    id: scoreBoardBody
    color: "transparent"
    signal refreshHeaders()
    signal setHorizontalHeaderWidthAt(int j, int w)
    onSetHorizontalHeaderWidthAt: horizontalHeader.setColumnWidth(j,w)
    signal setRowHeight(int i,int h)
    onSetRowHeight: verticalHeader.setRowHeight(i,h)
    signal requestUpdateCells()
    onRequestUpdateCells: tableView.forceLayout()
    signal notifyCellPosition(int x, int y)
    // Row/column related
    property int minimumColumnCount: 1
    // Horizontal header properties and signals
    signal setHorizontalHeaderDataAt(int j, var val)
    onSetHorizontalHeaderDataAt: horizontalHeader.setData(j,val)
    signal setHorizontalHeaderModel(int m)
    onSetHorizontalHeaderModel: horizontalHeader.model = m
    onSetVerticalHeaderModel: verticalHeader.model = m
    property color horizontalHeaderFontColor: "white"
    onHorizontalHeaderFontColorChanged: horizontalHeader.fontColor = horizontalHeaderFontColor
    property color horizontalHeaderBackgroundColor: "transparent"
    onHorizontalHeaderBackgroundColorChanged: horizontalHeader.backgroundColor = horizontalHeaderBackgroundColor
    property bool horizontalHeaderVisible: true
    onHorizontalHeaderVisibleChanged: flickableHHeader.visible = horizontalHeaderVisible
    property int horizontalHeaderHeight: 20
    onHorizontalHeaderHeightChanged: horizontalHeader.height = horizontalHeaderHeight
    property int horizontalHeaderFontSize: 12
    onHorizontalHeaderFontSizeChanged: horizontalHeader.fontSize = horizontalHeaderFontSize
    property int horizontalHeaderFillMode: 0x1
    readonly property int horizontalHeaderCount: horizontalHeader.dataCount()
    property int horizontalHeaderModel: horizontalHeader.model
    onHorizontalHeaderModelChanged: horizontalHeader.model = horizontalHeaderModel
    // Vertical header properties and signals
    signal setVerticalHeaderDataAt(int i, var val)
    onSetVerticalHeaderDataAt: verticalHeader.setData(i,val)
    signal setVerticalHeaderModel(int m)
    property color verticalHeaderFontColor: "white"
    onVerticalHeaderFontColorChanged: verticalHeader.fontColor = verticalHeaderFontColor
    property color verticalHeaderBackgroundColor: "transparent"
    onVerticalHeaderBackgroundColorChanged: verticalHeader.backgroundColor = verticalHeaderBackgroundColor
    property bool verticalHeaderVisible: true
    onVerticalHeaderVisibleChanged: flickableVHeader.visible = verticalHeaderVisible
    property bool staticVerticalHeaderWidth: false
    property int verticalHeaderWidth: 25
    onVerticalHeaderWidthChanged: verticalHeader.width = verticalHeaderWidth
    property int verticalHeaderFillMode: 0x2
    property int verticalHeaderFontSize: 12
    onVerticalHeaderFontSizeChanged: verticalHeader.fontSize = verticalHeaderFontSize
    property int verticalHeaderModel: verticalHeader.model
    onVerticalHeaderModelChanged: verticalHeader.model = verticalHeaderModel
    // Table view related
    signal updateViewPosition(int x,int y)
    onUpdateViewPosition: ScoreBoardScripts.updateViewPosition(x,y)
    // Move focus to last updated cell when data has changed
    signal updateContentDimensions(int h, int w)
    onUpdateContentDimensions: ScoreBoardScripts.updateContentDimensions(h,w)
    // Model property
    property QtObject model: tableView.model
    onModelChanged: tableView.model = model
    // Cell delegate
    property Component cellDelegate: Rectangle{}
    onCellDelegateChanged: tableView.delegate = cellDelegate
    // Update vertical header width
    signal updateVerticalHeaderWidth(int w)
    onUpdateVerticalHeaderWidth: ScoreBoardScripts.updateVerticalHeaderWidth(w)
    // Update column widths from datamodel
    property var columnWidthProvider: function(){}
    onColumnWidthProviderChanged: tableView.columnWidthProvider = columnWidthProvider
    // Update row height from datamodel
    property var rowHeightProvider: function(){}
    onRowHeightProviderChanged: tableView.rowHeightProvider = rowHeightProvider
    // Data model visualization related
    property double modelScale: 1
    GridLayout
    {
        id: mainLayout
        anchors.fill: parent
        rows: 2
        columns: 2
        rowSpacing: 0
        columnSpacing: 0
        Flickable{
            id: flickableVHeader
            clip: true
            Layout.fillHeight: true
            Layout.row: 1
            Layout.column: 0
            interactive: false
            VerticalHeader {
                id: verticalHeader
                anchors.fill: parent
                backgroundColor: scoreBoardBody.verticalHeaderBackgroundColor
                fontColor: scoreBoardBody.verticalHeaderFontColor
                borderWidth: 1
                Layout.alignment: Qt.AlignTop
                visible: scoreBoardBody.verticalHeaderVisible
            }
        }

        Flickable{
            id: flickableHHeader
            clip: true
            Layout.fillWidth: true
            Layout.minimumHeight: 45
            contentHeight: 45
            Layout.row: 0
            Layout.column: 1
            interactive: false
            HorizontalHeader {
                id: horizontalHeader
                anchors.fill: flickableHHeader.contentItem
                backgroundColor: scoreBoardBody.horizontalHeaderBackgroundColor
                fontColor: scoreBoardBody.horizontalHeaderFontColor
                borderWidth: 1
            }
        }
        Flickable{
            id: flickableTable
            clip: true
            Layout.row: 1
            Layout.column: 1
            Layout.fillWidth: true
            Layout.fillHeight: true
            boundsMovement: Flickable.StopAtBounds
            onContentXChanged: flickableHHeader.contentX = contentX
            onContentYChanged: flickableVHeader.contentY = contentY

            TableView {
                id: tableView
                interactive: false
                clip: true
                anchors.fill: parent
            }
        }
    }
}
