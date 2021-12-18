import QtQuick 2.0
import QtQuick.Layouts 1.3

UserInputComponent{
    id: throwSpinBox
    height: 32
    labelBackgroundColor: "lightblue"
    labelText: "Number of throws"
    labelLeftMargin: 10
    labelFontColor: "darkblue"
    content: SpinBoxInputContent{
        borderRadius: 0
    }
}
