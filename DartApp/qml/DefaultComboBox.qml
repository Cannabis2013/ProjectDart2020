import QtQuick 2.0
import QtQuick.Layouts 1.3

UserInputComponent{
    id: body
    property var model
    height: 32
    labelFontColor: "darkblue"
    labelBackgroundColor: "lightblue"
    labelLeftMargin: 10
    content: ComboBoxComponent{
        id: content
        stringModel: body.model
    }
}
