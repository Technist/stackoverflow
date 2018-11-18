// Main.qml
import QtQuick 2.0
import QtQuick.Controls 2.0		//	for `ApplicationWindow`

// import "file/path/to/progressbar"  // use this if MyProgressBar.qml is not in the same folder as Main.qml

ApplicationWindow {
	visible: true
    width: 480
    height: 320

    MyProgressBar {
         id: progressbar_id
		 anchors.centerIn: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: progressbar_id.value += 5;
    }
}
