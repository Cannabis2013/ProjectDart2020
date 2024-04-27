import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

Button {
        id: buttonControl

        signal buttonClicked

        property url iconSource: ""
        onIconSourceChanged: buttonIcon.source = iconSource

        property int iconWidth: 19
        onIconWidthChanged: buttonIcon.width = iconWidth
        property int iconHeight: 8
        onIconHeightChanged: buttonIcon.height = iconHeight

        opacity: 1

        property bool active: true
        onActiveChanged: {
                opacity = active ? 1 : 0.4
                mouseArea.enabled = active
        }

        Image {
                id: buttonIcon
                anchors.centerIn: parent
                width: buttonControl.iconWidth
                height: buttonControl.iconHeight
                source: buttonControl.iconSource
                fillMode: Image.PreserveAspectFit
        }

        MouseArea {
                id: mouseArea
                anchors.fill: parent
                enabled: buttonControl.active
                onClicked: buttonClicked()
        }
}
