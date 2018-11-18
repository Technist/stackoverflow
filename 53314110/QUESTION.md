I have this QML progress bar:


    import QtQuick.Controls 2.0 as QQC20
    
    Item {
        QQC20.ProgressBar {
            id: progressbar_id
            visible: false // even if "true", the progress bar does NOT show up on UI
            from: editorScene.progressbarMin
            to: editorScene.progressbarMax
            value: editorScene.progressbarVal
            
            onValueChanged: {
                console.log("Progressbar value changed: ", progressbar_id.value)
            }
            onVisibleChanged: {
                console.log("Progressbar visibility chanaged: ", progressbar_id.visible)
            }
        }
    }

I can confirm that the progress bar value and visibility are changed by the methods `onValueChanged` and `onVisibleChanged`. 

However, the problem is that the progress bar does NOT show up on the UI! How can I actually show the progress bar on the UI? Can anybody give me a hint?

Tags:
[`qt`](https://stackoverflow.com/tags/qt/info)
[`qml`](https://stackoverflow.com/tags/qml/info)
[`progress-bar`](https://stackoverflow.com/tags/progress-bar/info)
[`qtquickcontrols`](https://stackoverflow.com/tags/qtquickcontrols/info)

See also: [_Original StackOverflow Question_](https://stackoverflow.com/questions/53314110/qml-progress-bar-is-not-showing-up-on-ui/).
