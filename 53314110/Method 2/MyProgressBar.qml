// MyProgressBar.qml
import QtQuick 2.0              // for `Item`
import QtQuick.Controls 2.0     // for `ProgressBar`

// here is your item, it has grown up to be a file of its own 🚼
Item {
    property alias value: progressbar_id.value  // for user-interaction

    ProgressBar {
        id: progressbar_id

        anchors.horizontalCenter: parent.horizontalCenter  // centre horizontally

        from: 0
        to: 100
        value: 5

        onValueChanged: {
            console.log("Progressbar value changed: ", progressbar_id.value)
        }
        onVisibleChanged: {
            console.log("Progressbar visibility chanaged: ", progressbar_id.visible)
        }
    }
}
