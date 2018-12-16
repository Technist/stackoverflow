import QtQuick 2.0
import QtQml.Models 2.1

GridView {
    id: root
    width: 320; height: 480
    cellWidth: 80; cellHeight: 80

    displaced: Transition {
        NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }//Animação anima a transicao dos tiles
    }

    model: DelegateModel {
        id: visualModel
        model: ListModel {
            id: colorModel
            ListElement { color: "lightsteelblue" ; text: "1" }
            ListElement { color: "lightsteelblue" ; text: "2" }
            ListElement { color: "lightsteelblue" ; text: "3" }
            ListElement { color: "lightsteelblue" ; text: "4" }
            ListElement { color: "lightsteelblue" ; text: "5" }
            ListElement { color: "lightsteelblue" ; text: "6" }
            ListElement { color: "lightsteelblue" ; text: "7" }
            ListElement { color: "lightsteelblue" ; text: "8" }
            ListElement { color: "lightsteelblue" ; text: "9" }
            ListElement { color: "lightsteelblue" ; text: "10" }
            ListElement { color: "lightsteelblue" ; text: "11" }
            ListElement { color: "lightsteelblue" ; text: "12" }
            ListElement { color: "lightsteelblue" ; text: "13" }
            ListElement { color: "lightsteelblue" ; text: "14" }
            ListElement { color: "lightsteelblue" ; text: "15" }
			ListElement { color: "transparent"	  ; text: "n/a" }
        }

        delegate: MouseArea {
            id: delegateRoot

            property int visualIndex: DelegateModel.itemsIndex

            width: 80; height: 80
            drag.target: icon

            Rectangle {
                id: icon
                Text {
                   text: model.text
                   font.pointSize: 30
                   anchors.centerIn: parent
                }
                width: 72; height: 72
                anchors {
                    horizontalCenter: parent.horizontalCenter;
                    verticalCenter: parent.verticalCenter
                }
                color: model.color
                radius: 3

                Drag.active: delegateRoot.drag.active
                Drag.source: delegateRoot
                Drag.hotSpot.x: 36
                Drag.hotSpot.y: 36
				
                states: [
                    State {
                        when: icon.Drag.active
                        ParentChange {
                            target: icon
                            parent: root
                        }

                        AnchorChanges {
                            target: icon;
                            anchors.horizontalCenter: undefined;
                            anchors.verticalCenter: undefined
                        }
                    }
                ]	//	states
            }	//	Rectangle

			DropArea {
				id: dropArea
				
				anchors { fill: parent; margins: 15 }
				onEntered: {
					//	store as local variables
					var from = drag.source.visualIndex;
					var to = delegateRoot.visualIndex;
					
					console.log(from, "-->", to);
					
					//	`isAdjacent` is a function implemented below
					if (isAdjacent(from, to))
						console.warn("Yes, adjacent.");
					else {
						console.warn("No, not adjacent.");
						
						//	jump the gun, we don't care if they're not adjacent
						return;
					}
					
					//	normal move
					visualModel.items.move(from, to);
					// visualModel.items.move(drag.source.visualIndex, delegateRoot.visualIndex);	//	this is the same as the line above
					
					
					//	if `from`/`to` are horizontally adjacent (left/right)
					//	then the move is already valid
					
					if (from % 4 < 3 && from + 1 === to)	//	check `to` is right of `from`
						return;
					if (from % 4 > 0 && from - 1 === to)	//	check `to` is left of `from`
						return;
					
					
					//	move for vertically adjacent
					if (from < 12 && from + 4 === to)	//	check `to` is below `from`
						visualModel.items.move(to - 1, from);
					
					if (from >= 4 && from - 4 === to)	//	check `to` is above `from`
						visualModel.items.move(to + 1, from);
				}
				
				function isAdjacent(from, to) {
					if (from % 4 < 3 && from + 1 === to)	//	check `to` is right of `from`
						return true;
					if (from % 4 > 0 && from - 1 === to)	//	check `to` is left of `from`
						return true;
					if (from < 12 && from + 4 === to)	//	check `to` is below `from`
						return true;
					if (from >= 4 && from - 4 === to)	//	check `to` is above from
						return true;
					
					return false;
				}
			}	//	DropArea
        }	//	MouseArea
    }	//	DelegateModel
}	//	GridView
