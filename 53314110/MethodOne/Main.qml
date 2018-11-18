// Main.qml
import QtQuick 2.0             // for `Item`
import QtQuick.Window 2.0      // for `ApplicationWindow`
import QtQuick.Controls 2.0    // as QQC20 // no need to label a namespace unless disambiguation is necessary

ApplicationWindow {
	visible: true
    width: 480   // set the dimensions of the application window
    height: 320

    // here's your item
    Item {
        anchors.centerIn: parent   // place in centre of window

        ProgressBar {
            id: progressbar_id

            anchors.horizontalCenter: parent.horizontalCenter // horizontally align the progress bar

            from: 0    // don't know what editorScene is
            to: 100    // so I'm using raw values
            value: 5

            onValueChanged: {
                console.log("Progressbar value changed: ", progressbar_id.value)
            }
            onVisibleChanged: {
                // side note: I'm not getting any output from this handler
                console.log("Progressbar visibility chanaged: ", progressbar_id.visible)
            }
        }
    }

    // provide user-interaction for changing progress bar's value
    MouseArea {
        anchors.fill: parent            // clicking anywhere on the background
        onClicked: progressbar_id.value += 5;   // increments the progress bar
                                                // and triggers onValueChanged
    }
}
