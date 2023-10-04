import QtQuick 2.0
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.15

Rectangle {
        id: buttonRect
        clip: true

        radius: 3

        signal clicked

        property string text: ""
        onTextChanged: buttonText.text = qsTr(text)
        property color backgroundColor: "grey"
        onBackgroundColorChanged: buttonRect.color = backgroundColor
        property color fontColor: "black"
        onFontColorChanged: buttonText.color = fontColor

        MouseArea {
                anchors.fill: parent
                onClicked: buttonRect.clicked()
        }

        Text {
                id: buttonText
                anchors.fill: parent
                text: qsTr(buttonRect.text)
                color: fontColor
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
        }
}
