import QtQuick 2.15
import QtQuick.Layouts 1.3

Pad {
        id: numberPadRect

        property int padValue: -1

        signal padClicked(int value)
        onPressed: scaleDownAnimation.start()

        ScaleAnimator on scale {
                id: scaleDownAnimation
                from: 1
                to: 0.9
                duration: 50
                running: false
        }

        ScaleAnimator on scale {
                id: scaleUpAnimation
                from: 0.9
                to: 1
                duration: 25
                running: false
        }

        onReleased: {
                numberPadRect.padClicked(numberPadRect.padValue)
                scaleUpAnimation.start()
        }
}
