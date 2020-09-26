import QtQuick 2.0

Rectangle {
    id: body
    color: "transparent"
    clip: true
    property string sourceText: "Loading data..."
    MyLabel{
        anchors.fill: parent
        property int index: 0
        horizontalTextAlignment: Text.AlignRight
        verticalTextAlignment: Text.AlignVCenter
        text: body.sourceText.slice(0,index)
        fontSize: 48

        NumberAnimation on index{
            from: 0
            to: body.sourceText.length *2
            duration: 3500
            loops: NumberAnimation.Infinite
        }

    }
}
