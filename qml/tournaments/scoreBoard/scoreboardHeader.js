.import "scoreboardGeometry.js" as GeometryScripts

function setHeaderData(data, defaultVal) {
        for (var i = 0; i < data.length; i++) {
                let assignedPlayerName = data[i]
                dpcScoreBoard.appendHeader(assignedPlayerName)
                dpcScoreBoard.setData(assignedPlayerName, defaultVal, 0, 0, 0, false)
        }
}

function appendHeader(header) {
        playerDataModel.addPlayer(header)
        var headerWidth = fontsMetric.width(header, tableFonts.headerFontFamily, tableFonts.headerFontSize)
        var headerHeight = fontsMetric.height(header, tableFonts.headerFontFamily, tableFonts.headerFontSize)
        var i = playerDataModel.indexOf(header)
        tableHeightProvider.updateRowHeight(i, headerHeight)
        var scaledWidth = GeometryScripts.scaleWidth(headerWidth)
        updateVerticalHeaderWidth(scaledWidth)
}

function updateVerticalHeaderWidth(w) {
        if (w > scoreBoardBody.verticalHeaderWidth)
                scoreBoardBody.updateVerticalHeaderWidth(w)
}
