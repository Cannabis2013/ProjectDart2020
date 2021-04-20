import QtQuick 2.15
import CustomItems 1.0

import "fTPMultiScripts.js" as ScoreScripts

ScoreBoard {
    id: fTPBody
    // Data related
    onSetData: ScoreScripts.setData(playerName,point,score)
    onTakeData: ScoreScripts.takeData(playerName)
    onEditData: ScoreScripts.editData(row,column,point,score)
    onClearData: fTPModel.clearData();

    // Row/column related
    onMinimumColumnCountChanged: fTPModel.minimumColumnCount = fTPBody.minimumColumnCount
    // Score related
    property int scoreFontSize: 24
    onScoreFontSizeChanged: {
        fTPModel.scoreFontPointSize = fTPBody.scoreFontSize;
        delegate.scoreFontSize = fTPBody.scoreFontSize;
    }

    onSizeScale: fTPModel.scale = s
    // Notify datamodel about the number of attemps
    property int attempts: 3
    onAttemptsChanged: fTPModel.attempts = attempts;

    onMinimumRowCount: fTPModel.setMinimumRowCount(count);

    // Header related
    horizontalHeaderFontSize: 24
    verticalHeaderVisible: true
    onAppendHeaderData: {
        for(var i = 0; i < data.length;i++)
        {
            var assignedPlayerName = data[i];
            scoreBoardItemSlot.item.appendHeader(assignedPlayerName,Qt.Horizontal);
            scoreBoardItemSlot.item.setData(assignedPlayerName,0,defaultVal,undefined);
        }
    }

    property int headerFontSize: 24
    onHeaderFontSizeChanged: fTPModel.headerFontSize = fTPBody.headerFontSize
    headerOrientation: Qt.Vertical
    onHeaderOrientationChanged: fTPModel.setHeaderOrientation(headerOrientation)
    verticalHeaderFillMode: DataModelContext.fixedFill
    horizontalHeaderFillMode: DataModelContext.numericFill
    onVerticalHeaderFillModeChanged: fTPModel.verticalFillMode = verticalHeaderFillMode
    onHorizontalHeaderFillModeChanged: fTPModel.horizontalFillMode = horizontalHeaderFillMode
    onAppendHeader: ScoreScripts.appendHeader(header,orientation)

    // Cell related
    property color scoreCellColor: "transparent"
    onScoreCellColorChanged: delegate.cellColor = fTPBody.scoreCellColor
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: delegate.borderWidth = cellBorderWidth
    // Point related
    property int pointFontSize: 10
    onPointFontSizeChanged: {
        delegate.pointFontSize = fTPBody.pointFontSize;
        fTPModel.pointFontPointSize = fTPBody.pointFontSize;
    }
    property bool displayPoints: true
    onDisplayPointsChanged: delegate.pointDisplayVisible = displayPoints

    property int pointDisplayWidth: 20
    onPointDisplayWidthChanged: delegate.pointDisplayWidth = pointDisplayWidth
    property int pointDisplayHeight: 20

    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)

    modelScale: 1.5
    onModelScaleChanged: fTPModel.scale = modelScale

    QtObject{
        id: cellPositionHolder

        property int px: -1
        property int py: -1

        property int cx: -1
        property int cy: -1
    }

    columnWidthProvider: function(column){
        return fTPModel.columnWidthAt(column);
    }

    rowHeightProvider: function(row)
    {
        return fTPModel.rowHeightAt(row);
    }

    model: FtpDataModel {
        id: fTPModel
        onDataChanged: ScoreScripts.updateScoreBoard();
        attempts: fTPBody.attempts
        headerOrientation: fTPBody.headerOrientation
        pointFontPointSize: fTPBody.pointFontSize
        scoreFontPointSize: fTPBody.scoreFontSize
        horizontalFillMode: fTPBody.horizontalHeaderFillMode
        verticalFillMode: fTPBody.verticalHeaderFillMode
        appendMode: DataModelContext.multiAttempt
        minimumColumnCount: fTPBody.minimumColumnCount
        scale: fTPBody.modelScale
    }

    cellDelegate: CellDelegate {
        id: delegate
        cellBorderWidth: fTPBody.cellBorderWidth
        cellColor: fTPBody.scoreCellColor
        scoreFontSize: fTPBody.scoreFontSize
        pointFontSize: fTPBody.pointFontSize
        pointDisplayVisible: fTPBody.displayPoints
        pointDisplayWidth: fTPBody.pointDisplayWidth
        onTextChanged: notifyCellPosition(delegate.x,delegate.y);
        text: display
    }
}
