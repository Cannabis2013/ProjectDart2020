import QtQuick 2.15
import CustomItems 1.0

import "dartsmultiscorescripts.js" as ScoreScripts

ScoreBoard {
    id: fTPBody
    // Data related
    signal setData(string playerName, int point, int score, int keyCode)
    signal takeData(int row, int column,string playerName)
    signal editData(int row, int column,int point,int score)
    onSetData: ScoreScripts.setData(playerName,point,score)
    onTakeData: ScoreScripts.takeData(playerName)
    onEditData: ScoreScripts.editData(row,column,point,score)
    onClearData: dartsDataModel.clearData();

    // Row/column related
    onMinimumColumnCountChanged: dartsDataModel.minimumColumnCount = fTPBody.minimumColumnCount
    // Score related
    property int scoreFontSize: 24
    onScoreFontSizeChanged: {
        dartsDataModel.scoreFontPointSize = fTPBody.scoreFontSize;
        delegate.scoreFontSize = fTPBody.scoreFontSize;
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
    onHeaderFontSizeChanged: dartsDataModel.headerFontSize = fTPBody.headerFontSize
    headerOrientation: Qt.Vertical
    onHeaderOrientationChanged: dartsDataModel.setHeaderOrientation(headerOrientation)
    verticalHeaderFillMode: DataModelContext.fixedFill
    horizontalHeaderFillMode: DataModelContext.numericFill
    onVerticalHeaderFillModeChanged: dartsDataModel.verticalFillMode = verticalHeaderFillMode
    onHorizontalHeaderFillModeChanged: dartsDataModel.horizontalFillMode = horizontalHeaderFillMode
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
        dartsDataModel.pointFontPointSize = fTPBody.pointFontSize;
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

    cellDelegate: MultiPointDelegate {
        id: delegate
        text: display
        cellBorderWidth: fTPBody.cellBorderWidth
        cellColor: fTPBody.scoreCellColor
        scoreFontSize: fTPBody.scoreFontSize
        pointFontSize: fTPBody.pointFontSize
    }
}
