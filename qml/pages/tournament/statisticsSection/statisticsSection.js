function updateStatistics(statisticsArr) {
        for (var i = 0; i < statisticsArr.length; i++) {
                const statistics = statisticsArr[i]
                const rect = statisticsRects.children[i]
                rect.updateStatistics(statistics)
        }
}
