import QtQuick 2.12
import QtQuick.Layouts 1.3
import CustomItems 1.0

import "scoreBoardScripts.js" as ScoreScripts

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
    id: scoreBoardBody
    color: "transparent"
    property int headerOrientation: Qt.Vertical
    onHeaderOrientationChanged: myModel.setHeaderOrientation(headerOrientation)
    property int pointFontSize: 10
    onPointFontSizeChanged: {
        myModel.pointFontPointSize = pointFontSize;
        cellDelegate.pointFontSize = pointFontSize;
    }
    property int scoreFontSize: 20
    onScoreFontSizeChanged: {
        myModel.scoreFontPointSize = scoreFontSize;
        cellDelegate.scoreFontSize = scoreFontSize;
    }
    property bool displayPoints: false
    onDisplayPointsChanged:  cellDelegate.pointDisplayVisible = displayPoints
    property int pointDisplayWidth: 20
    onPointDisplayWidthChanged: cellDelegate.pointDisplayWidth = pointDisplayWidth
    property int pointDisplayHeight: 20
    property int horizontalHeaderHeight: 20
    onHorizontalHeaderHeightChanged: horizontalHeader.height = horizontalHeaderHeight
    property bool staticVerticalHeaderWidth: false
    property int verticalHeaderWidth: 25
    onVerticalHeaderWidthChanged: verticalHeader.width = verticalHeaderWidth
    property int verticalHeaderFillMode: 0x2
    onVerticalHeaderFillModeChanged: myModel.verticalFillMode = verticalHeaderFillMode
    property int horizontalHeaderFillMode: 0x1
    onHorizontalHeaderFillModeChanged: myModel.horizontalFillMode = horizontalHeaderFillMode
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: cellDelegate.borderWidth = cellBorderWidth
    property int throwsPerRound: 3
    onThrowsPerRoundChanged: myModel.throwCount = throwsPerRound;
    onMinimumColumnCount: myModel.setMinimumColumnCount(count);
    onMinimumRowCount: myModel.setMinimumRowCount(count);
    onAppendHeader: {
        myModel.appendHeaderItem(header,headerOrientation);
        var preferedWidth = myModel.preferedCellWidth()*1.05;
        verticalHeader.width = preferedWidth;
        flickableVHeader.Layout.minimumWidth = preferedWidth;
    }
    onSetData: {
        var result = myModel.insertData(playerName,point,score);
        if(!result)
            print("Couldn't add data to model");
    }
    function takeData(playerName)
    {
        var result = myModel.removeLastItem(playerName);
        if(!result)
            print("Couldn't take data");
    }
    function editData(row,column,point,score)
    {
        var result = myModel.editData(row,column,point,score);
        if(!result)
            print("Couldn't edit data");
    }
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
                columnWidthProvider: function(column)
                {
                    return myModel.columnWidthAt(column);
                }

                rowHeightProvider: function(row)
                {
                    return myModel.rowHeightAt(row);
                }

                model: FTPDataModel {
                    id: myModel
                    onDataChanged: ScoreScripts.updateScoreBoard();
                    throwCount : scoreBoardBody.throwsPerRound
                    headerOrientation: scoreBoardBody.headerOrientation
                    pointFontPointSize: scoreBoardBody.pointFontSize
                    scoreFontPointSize: scoreBoardBody.scoreFontSize

                    horizontalFillMode: 0x1
                    verticalFillMode: 0x2
                    scale: 2
                }

                delegate: CellDelegate {
                    id: cellDelegate
                    cellBorderWidth: scoreBoardBody.cellBorderWidth
                    cellColor: "purple"
                    scoreFontSize: scoreBoardBody.scoreFontSize
                    pointFontSize: scoreBoardBody.pointFontSize
                    pointDisplayVisible: scoreBoardBody.displayPoints
                    pointDisplayWidth: scoreBoardBody.pointDisplayWidth
                    onNotifyLocation: ScoreScripts.setViewPosition(x,y)
                    text: display
                }
            }
        }
    }
}
