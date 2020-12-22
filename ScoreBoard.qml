import QtQuick 2.12
import QtQuick.Layouts 1.3

/*
  Controller status table:
    -> GameControllerIdle = 0x9
    -> GamecontrollerBusy = 0xa
    -> GameControllerStopped = 0xb
    -> GameControllerAwaitsInput = 0xc
    -> GameControllerRunning = 0xd
    -> GameControllerWinnerDeclared = 0xe
    -> GameControllerNotInitialized = 0xf
  */

ScoreBoardInterface{
    id: body
    color: "transparent"

    onClearData: {
        verticalHeader.clearData();
        horizontalHeader.clearData();
    }

    signal updateViewPosition(int x,int y)
    onUpdateViewPosition: {
        flickableTable.contentX = x;
        flickableTable.contentY = y;
    }

    signal updateContentDimensions(int h, int w)
    onUpdateContentDimensions: {
        flickableVHeader.contentHeight = h;
        flickableTable.contentHeight = h;
        flickableTable.contentWidth = w;
        flickableHHeader.contentWidth = w;
    }

    signal refreshHeaders()
    signal setColumnWidth(int j, int w)

    onSetColumnWidth: horizontalHeader.setColumnWidth(j,w)
    signal setRowHeight(int i,int h)
    onSetRowHeight: verticalHeader.setRowHeight(i,h)

    signal requestUpdateCells()
    onRequestUpdateCells: tableView.forceLayout()

    signal notifyCellPosition(int x, int y)

    signal setVerticalHeaderDataAt(int i, var val)
    onSetVerticalHeaderDataAt: verticalHeader.setData(i,val)
    signal setHorizontalHeaderDataAt(int j, var val)
    onSetHorizontalHeaderDataAt: horizontalHeader.setData(j,val)

    signal setHorizontalHeaderModel(int m)
    onSetHorizontalHeaderModel: horizontalHeader.model = m
    signal setVerticalHeaderModel(int m)
    onSetVerticalHeaderModel: verticalHeader.model = m

    property int headerOrientation: Qt.Vertical

    // Header related
    property int horizontalHeaderHeight: 20
    onHorizontalHeaderHeightChanged: horizontalHeader.height = horizontalHeaderHeight
    property bool staticVerticalHeaderWidth: false
    property int verticalHeaderWidth: 25
    onVerticalHeaderWidthChanged: verticalHeader.width = verticalHeaderWidth
    property int verticalHeaderFillMode: 0x2

    property int horizontalHeaderFillMode: 0x1

    readonly property int horizontalHeaderCount: horizontalHeader.dataCount()

    property int horizontalHeaderModel: horizontalHeader.model
    onHorizontalHeaderModelChanged: horizontalHeader.model = horizontalHeaderModel

    property int verticalHeaderModel: verticalHeader.model
    onVerticalHeaderModelChanged: verticalHeader.model = verticalHeaderModel

    property QtObject model: tableView.model
    onModelChanged: tableView.model = model

    property Component cellDelegate: Rectangle{}
    onCellDelegateChanged: tableView.delegate = cellDelegate

    signal updateVerticalHeaderWidth(int w)
    onUpdateVerticalHeaderWidth: {
        flickableVHeader.Layout.minimumWidth = w;
        verticalHeader.width = w;
    }

    property var columnWidthProvider: function(){}
    onColumnWidthProviderChanged: tableView.columnWidthProvider = columnWidthProvider

    property var rowHeightProvider: function(){}
    onRowHeightProviderChanged: tableView.rowHeightProvider = rowHeightProvider

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
                backgroundColor: "lightgray"
                color: "black"
                borderWidth: 1
                Layout.alignment: Qt.AlignTop
            }
        }

        Flickable{
            id: flickableHHeader
            clip: true
            Layout.fillWidth: true
            Layout.minimumHeight: 25
            contentHeight: 25
            Layout.row: 0
            Layout.column: 1
            interactive: false
            HorizontalHeader {
                id: horizontalHeader
                anchors.fill: flickableHHeader.contentItem
                backgroundColor: "lightgray"
                color: "black"
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
