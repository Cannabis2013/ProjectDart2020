import QtQuick 2.15
import CustomItems 1.0

import "dartssingleattemptscoreboardscripts.js" as ScoreScripts

ScoreBoard {
    id: singleAttemptPointScoreBoard
    // Data related
    signal setData(string playerName, int point, int score)
    signal takeData(int row, int column,string playerName)
    signal editData(int row, int column,int point,int score)
    onSetData: ScoreScripts.setData(playerName,score,point)
    onTakeData: ScoreScripts.takeData(playerName)
    onEditData: ScoreScripts.editData(row,column,point,score)
    onClearData: dartsDataModel.clearData();

    // Row/column related
    onMinimumColumnCountChanged: dartsDataModel.minimumColumnCount = singleAttemptPointScoreBoard.minimumColumnCount
    // Score related
    property int scoreFontSize: 24
    onScoreFontSizeChanged: {
        dartsDataModel.scoreFontPointSize = singleAttemptPointScoreBoard.scoreFontSize;
        delegate.scoreFontSize = singleAttemptPointScoreBoard.scoreFontSize;
    }

    onSizeScale: dartsDataModel.scale = s
    // Notify datamodel about the number of attemps
    property int attempts: 3
    onAttemptsChanged: dartsDataModel.attempts = attempts;

    onMinimumRowCount: dartsDataModel.setMinimumRowCount(count);

    // Header related
    horizontalHeaderFontSize: 24
    verticalHeaderVisible: true
    onAppendHeaderData: ScoreScripts.addHeaderData(data,defaultVal)

    property int headerFontSize: 24
    onHeaderFontSizeChanged: dartsDataModel.headerFontSize = singleAttemptPointScoreBoard.headerFontSize
    headerOrientation: Qt.Vertical
    onHeaderOrientationChanged: dartsDataModel.setHeaderOrientation(headerOrientation)
    verticalHeaderFillMode: DataModelContext.fixedFill
    horizontalHeaderFillMode: DataModelContext.numericFill
    onVerticalHeaderFillModeChanged: dartsDataModel.verticalFillMode = verticalHeaderFillMode
    onHorizontalHeaderFillModeChanged: dartsDataModel.horizontalFillMode = horizontalHeaderFillMode
    onAppendHeader: ScoreScripts.appendHeader(header)
    // Cell related
    property color scoreCellColor: "transparent"
    onScoreCellColorChanged: delegate.cellColor = singleAttemptPointScoreBoard.scoreCellColor
    property int cellBorderWidth: 0
    onCellBorderWidthChanged: delegate.borderWidth = cellBorderWidth
    // Point related
    property int pointFontSize: 10
    onPointFontSizeChanged: {
        delegate.pointFontSize = singleAttemptPointScoreBoard.pointFontSize;
        dartsDataModel.pointFontPointSize = singleAttemptPointScoreBoard.pointFontSize;
    }

    onNotifyCellPosition: ScoreScripts.setViewPosition(x,y)

    modelScale: 1.5
    onModelScaleChanged: dartsDataModel.scale = modelScale

    QtObject{
        id: cellPositionHolder

        property int px: -1
        property int py: -1

        property int cx: -1
        property int cy: -1
    }

    columnWidthProvider: function(column){
        return dartsDataModel.columnWidthAt(column);
    }

    rowHeightProvider: function(row)
    {
        return dartsDataModel.rowHeightAt(row);
    }

    model: DartsPointDatamodel {
        id: dartsDataModel
        onDataChanged: ScoreScripts.updateScoreBoard();
        attempts: singleAttemptPointScoreBoard.attempts
        headerOrientation: Qt.Vertical
        pointFontPointSize: singleAttemptPointScoreBoard.pointFontSize
        scoreFontPointSize: singleAttemptPointScoreBoard.scoreFontSize
        horizontalFillMode: singleAttemptPointScoreBoard.horizontalHeaderFillMode
        verticalFillMode: singleAttemptPointScoreBoard.verticalHeaderFillMode
        appendMode: DataModelContext.multiAttempt
        minimumColumnCount: singleAttemptPointScoreBoard.minimumColumnCount
        scale: singleAttemptPointScoreBoard.modelScale
    }

    cellDelegate: MultiPointDelegate {
        id: delegate
        text: display
        cellBorderWidth: singleAttemptPointScoreBoard.cellBorderWidth
        cellColor: singleAttemptPointScoreBoard.scoreCellColor
        scoreFontSize: singleAttemptPointScoreBoard.scoreFontSize
        pointFontSize: singleAttemptPointScoreBoard.pointFontSize
    }
}
