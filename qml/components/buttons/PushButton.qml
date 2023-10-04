import QtQuick 2.15

import "pushbuttonScripts.js" as PBScripts

PushButtonInterface {
        id: body
        clip: true
        onTextChanged: buttonText.text = qsTr(text)
        onBackgroundTransparencyChanged: buttonRect.opacity = backgroundTransparency
        onFontSizeChanged: buttonText.font.pointSize = fontSize
        onBackgroundColorChanged: buttonRect.color = backgroundColor
        onTextColorChanged: buttonText.color = textColor
        onHoverEnabledChanged: body.enableHoverEvent = hoverEnabled
        onEnablePressAndHoldChanged: body.enablePressAndHoldEvent = enablePressAndHold
        onButtonRadiusChanged: buttonRect.radius = buttonRadius
        onImageChanged: imageDecorator.source = image
        onImageMarginsChanged: imageDecorator.anchors.margins = imageMargins
        onImageRotationChanged: imageDecorator.rotation = imageRotation
        onClickEvent: PBScripts.onClicked(text)
        onPressedEvent: PBScripts.onPressed(sustained)
        onPressAndHoldEvent: body.pressAndHoldClicked()
        onHoverEvent: PBScripts.onHover(sustained)
        onClicked: PBScripts.handleClick()
        Rectangle {
                id: buttonRect
                anchors.fill: body
                radius: body.buttonRadius
                color: backgroundColor
        }
        Image {
                id: imageDecorator
                anchors.fill: parent
                anchors.margins: body.imageMargins
                rotation: body.imageRotation
        }
        Text {
                id: buttonText
                font.pointSize: fontSize
                color: body.textColor
                text: qsTr(body.text)
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.centerIn: parent
        }
        states: [
                State {
                        name: "hovered"
                        PropertyChanges {
                                target: buttonRect
                                color: hoveredColor
                                opacity: 1
                        }
                        PropertyChanges {
                                target: buttonText
                                color: hoveredTextColor
                        }
                        PropertyChanges {
                                target: body
                                checked: body.checked
                        }
                },
                State {
                        name: "hoveredPressed"
                        PropertyChanges {
                                target: buttonText
                                color: hoveredTextColor
                        }
                        PropertyChanges {
                                target: buttonRect
                                color: hoveredColor
                        }
                        PropertyChanges {
                                target: body
                                checked: body.checked
                        }
                },
                State {
                        name: "checked"
                        PropertyChanges {
                                target: buttonRect
                                color: checkedBackgroundColor
                        }
                        PropertyChanges {
                                target: buttonText
                                color: checkedTextColor
                        }
                        PropertyChanges {
                                target: body
                                checked: true
                        }
                },
                State {
                        name: "pressed"
                        PropertyChanges {
                                target: buttonRect
                                scale: body.pressedScale
                                color: body.pressedColor
                        }
                        PropertyChanges {
                                target: body
                                checked: body.checked
                        }
                }
        ]
}
