import QtQuick 2.15
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.3
import "playerListViewScripts.js" as PLVScripts
Transition {
    NumberAnimation {
        property: "scale"
        from: 0
        to: 1
        duration: 200
    }
}
