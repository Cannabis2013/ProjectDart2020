import QtQuick 2.0

Rectangle {
    clip: true
    signal setData(string playerName, int point, int score, int keyCode)
    signal minimumColumnCount(int count)
    signal minimumRowCount(int count)
    signal appendHeader(string header)
}
