import QtQuick 2.12
import QtQuick.Layouts 1.3
import DartsTableUtils 1.0
import CustomItems 1.0
import "scoreboardGeometry.js" as ScoreBoardGeometry
import "scoreboardscripts.js" as ScoreBoardScripts
import "scoreboardHeader.js" as ScoreBoardHeader

Rectangle {
        id: scoreBoardBody

        signal requestUpdateCells
        signal setVerticalHeaderHeightAt(int i, int h)
        signal notifyCellPosition(int x, int y)
        signal clearData
        signal minimumRowCount(int count)
        signal appendHeader(var data)
        signal appendHeaderData(var data, int defaultVal)
        signal sizeScale(double s)
        property bool verticalHeaderVisible: true
        signal setVerticalHeaderModel(int m)
        signal setVerticalHeaderDataAt(int i, var val)
        signal updateViewPosition(int x, int y)
        signal updateContentDimensions(int h, int w)
        signal updateContentHeight(int h)
        signal updateVerticalHeaderWidth(int w)

        property int minimumColumnCount: 1

        color: "transparent"
        height: ScoreBoardScripts.calculateHeight()
        onRequestUpdateCells: scoreBoardTableView.forceLayout()
        onUpdateViewPosition: ScoreBoardScripts.updateViewPosition(x, y)
        onUpdateContentDimensions: ScoreBoardScripts.updateContentDimensions(h, w)
        onUpdateContentHeight: scoreBoardTableView.contentHeight = h

        onUpdateVerticalHeaderWidth: ScoreBoardScripts.updateVerticalHeaderWidth(w)

        property double fontScale: 1
        readonly property int tableDisplayWidth: scoreBoardTableView.width

        ScoreBoardTableView {
                id: scoreBoardTableView
                anchors.fill: parent
                Layout.row: 1
                Layout.column: 1
                Layout.fillWidth: true
                Layout.fillHeight: true
                model: DPCTableModel {
                        id: dataModel
                        onDataChanged: ScoreBoardGeometry.updateContentHeight()
                        minimumColumnCount: 1
                }
                columnWidthProvider: function (column) {
                        return tableDisplayWidth
                }

                rowHeightProvider: function (row) {
                        return 64
                }
                cellDelegate: BoardDelegateContentRect {
                        id: delegate
                        playerName: playerDataModel.playerName(row)
                        score: DelegateScripts.updateDelegate(display, this, row)
                }
        }

        onWidthChanged: ScoreBoardGeometry.updateContentHeight()

        signal itemsEnabled(bool enabled)
        signal setData(string playerName, int score, int min, double mid, int max, bool inGame)
        signal takeData(int row, int column, string playerName)

        onSetData: DataScripts.setData(playerName, score, min, mid, max, inGame)
        onTakeData: DataScripts.takeData(row, column, playerName)
        onClearData: DataScripts.clearTable()
        onAppendHeaderData: ScoreBoardHeader.setHeaderData(data, defaultVal)
        onAppendHeader: ScoreBoardHeader.appendHeader(data)
        onNotifyCellPosition: ScoreBoardGeometry.setViewPosition(x, y)

        TableSectionMetrics {
                id: fontsMetric
        }

        DartsTableWidths {
                id: tableWidthProvider
                minimumColumnWidth: 64
                scale: 1.25
        }

        DartsTableHeights {
                id: tableHeightProvider
                minimumRowHeight: 72
                scale: 1.05
        }

        PlayerDataModel {
                id: playerDataModel
        }
}
