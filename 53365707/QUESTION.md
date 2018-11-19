I can't figure this one out. I mean the vertical spacing between lines of text in a Qml Text Item. I can't use Rich Text, and GridLayout seems to destroy my wrapping, horizontal alignment and the ability to check for truncated. This is inside a rectangle.

    Text{   
            width:10
            wrapMode: Text.Text.Wrap
            text:"This will be broken into multiple lines. How could I set the vertical spacing between them?"
         }

I mean:

[![enter image description here][1]][1]

Vs

[![enter image description here][2]][2]
        


  [1]: https://i.stack.imgur.com/BhJr7.png
  [2]: https://i.stack.imgur.com/hYJVs.png
  
----
  
Tags:
[`qt`](https://stackoverflow.com/tags/qt/info)
[`widget`](https://stackoverflow.com/tags/widget/info)
[`qml`](https://stackoverflow.com/tags/qml/info)
[`kde`](https://stackoverflow.com/tags/kde/info)
[`plasmoid`](https://stackoverflow.com/tags/plasmoid/info)

See also: [_Original StackOverflow Question_](https://stackoverflow.com/questions/53365707/how-to-set-the-line-spacing-for-qml-text-item/).
