import QtQuick 2.0
import QtQuick.Window 2.0

Window {
	visible: true
	width: 200
	height: 300
	
	Text {
		id: text
		width: 175
		anchors.centerIn: parent
		
		//	text: "HELLO HELLO HELLO HELLO HELLO HELLO HELLO HELLO HELLO HELLO HELLO HELLO HELLO HELLO"
		text: "Cat ipsum dolor sit amet, sleep nap. You call this cat food. Push your water glass on the floor."
		
		font.family: "Monaco"    // Monaco ❤️
		wrapMode: Text.WordWrap  // Make the text multi-line
		horizontalAlignment: Text.AlignHCenter
		
		//	lineHeightMode: Text.FixedHeight
		//	lineHeight: 6
		
		//	lineHeight: 1.0  // single-spacing (default)
		lineHeight: 1.5  // 1.5 line-spacing
		//	lineHeight: 2.0  // double-spacing
		//	lineHeight: 3.0  // triple-spacing
		
	}
}
