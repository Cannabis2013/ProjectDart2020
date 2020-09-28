import QtQuick 2.0
import QtQuick.Layouts 1.3

import "componentFactory.js" as ComponentFactory

UserInputComponent{
    id: titleEdit
    height: 32
    fontSize: 12
    labelText: "Title"
    labelFontColor: "darkblue"
    labelBackgroundColor: "lightblue"
    labelLeftMargin: 10
    content: MyTextEdit{}
}
