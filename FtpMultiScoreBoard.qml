import QtQuick 2.15
import CustomItems 1.0

import "fTPMultiPointScripts.js" as ScoreScripts

ScoreBoard {
    id: fTPBody
    // Data related
    signal setData(string playerName, int score)
    signal takeData(int row, int column,string playerName)
    signal editData(int row, int column,int score)
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

    onMinimumRowCount: fTPModel.setMinimumRowCount(count);

    // Header related
    horizontalHeaderFontSize: 24
    verticalHeaderVisible: true
    onAppendHeaderData: ScoreScripts.addHeaderData(data)

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

    model: DartsPointDatamodel {
        id: fTPModel
        onDataChanged: ScoreScripts.updateScoreBoard();
        attempts: 1
        headerOrientation: fTPBody.headerOrientation
        pointFontPointSize: fTPBody.pointFontSize
        scoreFontPointSize: fTPBody.scoreFontSize
        horizontalFillMode: fTPBody.horizontalHeaderFillMode
        verticalFillMode: fTPBody.verticalHeaderFillMode
        appendMode: DataModelContext.multiAttempt
        minimumColumnCount: fTPBody.minimumColumnCount
        scale: fTPBody.modelScale
    }

    cellDelegate: MultiScoreDelegate {
        id: delegate
        text: display
    }
}
