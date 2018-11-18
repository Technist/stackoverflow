<s>Note that this answer hasn't yet covered

> I would like to have graphics or widgets for custom autocompletion lists.

but I'm looking into it.</s>

**Edit:**

For autocompletion follow the [`Custom Completer Example`](http://doc.qt.io/qt-5/qtwidgets-tools-customcompleter-example.html) or the [`Completer Example`](http://doc.qt.io/qt-5/qtwidgets-tools-completer-example.html).

The code below follows the first one, which I blatantly, unashamedly copied and integrated into the `BackgroundHighlighter` class and `main.cpp`.

----

## Implementation

This answer will contain five files within a project along with a Qt Resource File.

 1. `highlighter.h`  (Highlighter Class for Syntax)
 2. `highlighter.cpp`
 3. `backgroundhighlighter.h` (BackgroundHighlighter Class)
 4. `backgroundhighlighter.cpp`
 5. `main.cpp`
 6. `res.qrc` (optional, not needed, you can hardcode your text)
 7. `res` (directory) (optional)
 8. `|- symbols.txt` (optional, you can set your own default text)
 9. `|- wordlist.txt` (optional, copied from [example](http://doc.qt.io/qt-5/qtwidgets-tools-customcompleter-example.html) but you could use your own line-delimited word list and set this in `main.cpp` with a [`QStringListModel`](http://doc.qt.io/qt-5/qstringlistmodel.html))

Note that the implementation of the `Highlighter` class for (1) and (2) can be found in the _[Qt Syntax Highlighter Example](https://doc.qt.io/qt-5/qtwidgets-richtext-syntaxhighlighter-example.html)_. I will leave its implementation as an exercise for the reader.

In calling the `BackgroundHighlighter` class, one can pass it a file name to load text from a file. (This wasn't in the OP's specification, but was convenient to implement due to the large amount of text I wanted to test.)

Also note that I integrated the [`Custom Completer Example`](http://doc.qt.io/qt-5/qtwidgets-tools-customcompleter-example.html) into the `BackgroundHighlighter` class.

Here's `backgroundhighlighter.h` (3) (~45 lines, ~60 lines with completer):

[`backgroundhighlighter.h`](./53318233/backgroundhighlighter.h)

And here's `backgroundhighlighter.cpp` (4) (~160 lines, ~250 lines with completer):

[`backgroundhighlighter.cpp`](./53318233/backgroundhighlighter.cpp)

Finally, here's `main.cpp` (5) (~10 lines, ~45 lines with completer)

[`main.cpp`](./53318233/main.cpp)

In `res.qrc` add a `/` prefix and add files (`res/symbols.txt`, `res/wordlist.txt`) from the `res/` subdirectory.

----

I have tried my best to

1. provide sufficient **explanation** within the comments.
2. **test** my solution in the context of all test cases.
3. **optimise** the code (not really) for better runtime performance.

## What Qt classes are used?

The code above makes use of the [Qt Core Module](http://doc.qt.io/qt-5/qtcore-module.html), [Qt Widgets Module](http://doc.qt.io/qt-5/qtwidgets-module.html), and the [Qt Gui Module](http://doc.qt.io/qt-5/qtgui-module.html).

Among these, the main ones I used were

* [`QTextEdit`](http://doc.qt.io/qt-5/qtextedit.html) for subclassing the `BackgroundHighlighter` class. This is a widget. The signal `cursorPositionChanged` comes from `QTextEdit`.

* [`QCharTextFormat`](https://doc.qt.io/qt-5/qtextcharformat.html) for formatting blocks of text. Especially with the `setBackground()` inherited from `QTextFormat`.
* [`QTextCursor`](http://doc.qt.io/qt-5/qtextcursor.htmlhttp://doc.qt.io/qt-5/qtextcursor.html) for manipulating the cursor (no visual changes), selecting words, and higlighting them.

Some other minor ones were

* [`QRegularExpression`](doc.qt.io/qt-5/qregularexpression.html) for symbol matching.

* [`QTextDocument`](https://doc.qt.io/qt-5/qtextdocument.html) for initialising the syntax highlighter.
* [`QFile`](http://doc.qt.io/qt-5/qfile.html) for loading files.
* and [`QString`](http://doc.qt.io/qt-5/qstring.html) (obviously).

Other classes may have been used by the `Highlighter` and the `Custom Completer`. These include QSyntaxHighlighter, QCompleter, and a couple event class.

## Were there any previous attempts you tried that I should look out for so that I don't fall into the same manhole?
I spent a while trying to find how I might be able to implement it with [`QTextBlock`](https://doc.qt.io/qt-5/qtextblock.html#setUserState) and [`QTextBlockFormat`](https://doc.qt.io/qt-5/qtextblockformat.html). **Apparently**, `QTextBlock` only recognises one block as a line. I tried using several blocks per line to handle symbols and even [tried using `QTextTable`](https://stackoverflow.com/questions/12041341/qt-several-qtextblock-inline) to solve the issue. I failed miserably.

## How "optimised" is this code?

Note that I didn't go all serious and write test/edge cases, profile it, or time it (I might time it).

When I said "optimise", I was alluding to the fact that I had slower, worse implementations before (using `QList` and whatnot).

I have tested with a `symbols.txt` file resembling

    symbol1 symbol2 symbol3 symbol4 symbol5
    symbol1 symbol2 symbol3 symbol4 symbol5
    symbol1 symbol2 symbol3 symbol4 symbol5
    // ... 500 lines

and I'm happy to say that I find the time reasonable (approx. 1 second for me?).

However, you might want to watch over for the line count as it grows. With the same text file at 1000 lines, the program will start to take approx. 3 seconds for highlighting.

Note that... I haven't optimised it **entirely**. There could possibly be a better implementation which **formats _only_ when the symbol scrolls into the user's view**. This is just a suggestion. How to implement it I don't know. (But I might try 🤔.)

## Are there any _"side effects"_ I should be wary of?
Yes, at around line 133, under the `BackgroundHighlighter::clearHighlights()` method, I warn how the code might clear away any background highlights originally added as it sets the ENTIRE document's character background to the default format. This may be an unintended consequence of the result.

## How does the completer work?
The words are loaded from a model in `main.cpp`. Once the user starts typing, with a word of at least 3 characters, the autocompleter shows up. If the completer isn't showing up for you, try to first implement [the example](http://doc.qt.io/qt-5/qtwidgets-tools-customcompleter-example.html) on a standalone/separate app.

## How can I change the background colour of the formats?
Go to lines 27 to 29 of `backgroundhighlighter.cpp`. There, you can see that I centralised the formatting. `mainFmt` refers to the formatting block directly under the cursor. `subsidiaryFmt` refers to the formatting blocks on congruent symbols. `defaultFmt` refers to the default format of the **entire** document which will be used in resetting the format.

## Where can I get `symbols.txt` and `wordlist.txt`?
I've attached these on [my github stackoverflow repository](https://github.com/Technist/stackoverflow/tree/master/53318233/res). You can download and copy them from there.

----

If anything is amiss, please comment below.

----

See also: [_Original StackOverflow Answer_](https://stackoverflow.com/questions/53318233/how-to-display-graphics-objects-behind-or-foreground-of-text-inside-qtextedit-in/53351512#53351512).
