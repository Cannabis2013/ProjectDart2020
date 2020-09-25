import QtQuick 2.0

Rectangle {
    clip: true
    signal appendData(string playerName, int point, int score, int keyCode)
}
