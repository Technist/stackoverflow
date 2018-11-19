A good habit is to [check the documentation](http://doc.qt.io/qt-5/qml-qtquick-text.html). Browsing through it, you could see a property called [`lineHeight`](http://doc.qt.io/qt-5/qml-qtquick-text.html#lineHeight-prop). I believe this is what you're looking for. From the documentation:

> ## `lineHeight : real`

> Sets the line height for the text. The value can be in pixels or a multiplier depending on `lineHeightMode`.

They also tell you how to use it

> The default value is a multiplier of 1.0. The line height must be a positive value.

Using `lineHeight` as a multiplier allows you to mimic the following line-spacing enumerations in MSWord.

    Single
    1.5 lines
    Double
    Multiple

Here's an example:

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

    		//	lineHeight: 1.0  // single-spacing (default)
    		lineHeight: 1.5  // 1.5 line-spacing
    		//	lineHeight: 2.0  // double-spacing
    		//	lineHeight: 3.0  // triple-spacing
    		
    	}
    }

Here are the results of using different values of `lineHeight` (on a typical MacOS)

**Single-spacing**

[![1x Line Spacing][1]][1]

**1.5x, Double (2x), Triple (3x)**

[![1.5x Line Spacing][2]][2]
[![2x Line Spacing][3]][3]
[![3x Line Spacing][4]][4]

----

However, if you want to mimic the other line-spacing enumerations:

    At least
    Exactly

you'll need to modify the pixel height. You can do this by setting [`lineHeightMode`](http://doc.qt.io/qt-5/qml-qtquick-text.html#lineHeightMode-prop) to `Text.FixedHeight`. Like so

    Window {
    	visible: true
    	width: 200
    	height: 300
    	
    	Text {
    		id: text
    		width: 175
    		anchors.centerIn: parent
    		
    		text: "Cat ipsum dolor sit amet, sleep nap. You call this cat food. Push your water glass on the floor."
    		
    		font.family: "Monaco"    // Monaco ❤️
    		wrapMode: Text.WordWrap  // Make the text multi-line
    		
    		
    		lineHeightMode: Text.FixedHeight
    		lineHeight: 6            // exaggerated, text will be scrunched up
    		
    	}
    }

**Exactly 6**

[![Exactly 6][5]][5]


  [1]: https://i.stack.imgur.com/BvpkV.png
  [2]: https://i.stack.imgur.com/tWjyJ.png
  [3]: https://i.stack.imgur.com/G7THs.png
  [4]: https://i.stack.imgur.com/3gNME.png
  [5]: https://i.stack.imgur.com/Sz8Me.png

----

See also: [_Original StackOverflow Answer_](https://stackoverflow.com/questions/53365707/how-to-set-the-line-spacing-for-qml-text-item/53367156#53367156).
