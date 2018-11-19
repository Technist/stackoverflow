#include "backgroundhighlighter.h"

#include <QDebug>

//  constructor
BackgroundHighlighter::BackgroundHighlighter(const QString &fileName, QWidget *parent) :
    QTextEdit(parent)
{
    //  I like Monaco
    setFont(QFont("Monaco"));
    setMinimumSize(QSize(500, 200));

    //  load initial text from a file OR from a hardcoded default
    if (!fileName.isEmpty())
        loadFile(fileName);
    else
    {
        QString defaultText = "// This is a textedit implemented by "
                              "a stackoverflow user.\r\n// Please upvote his answer "
                              "at https://stackoverflow.com/a/53351512/10239789.";

        setPlainText(defaultText);
    }

    //  set the highlighter here
    QTextDocument *doc = document();
    syntaxHighlighter = new Highlighter(doc);

    //  TODO change brush/colours to match theme
    mainFmt.setBackground(Qt::yellow);
    subsidiaryFmt.setBackground(Qt::lightGray);
    defaultFmt.setBackground(Qt::white);

    //  connect the signal to our handler
    connect(this, &QTextEdit::cursorPositionChanged, this, &BackgroundHighlighter::onCursorPositionChanged);
}

//  convenience function for reading a file
void BackgroundHighlighter::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
        return;

    //  the file could be in Plain Text OR Html
    setText(file.readAll());
}

void BackgroundHighlighter::setCompleter(QCompleter *completer)
{
    if (c)
        QObject::disconnect(c, 0, this, 0);

    c = completer;

    if (!c)
        return;

    c->setWidget(this);
    c->setCompletionMode(QCompleter::PopupCompletion);
    c->setCaseSensitivity(Qt::CaseInsensitive);
    QObject::connect(c, SIGNAL(activated(QString)),
                     this, SLOT(insertCompletion(QString)));
}

QCompleter *BackgroundHighlighter::completer() const
{
    return c;
}

void BackgroundHighlighter::keyPressEvent(QKeyEvent *e)
{
    if (c && c->popup()->isVisible()) {
        // The following keys are forwarded by the completer to the widget
       switch (e->key()) {
       case Qt::Key_Enter:
       case Qt::Key_Return:
       case Qt::Key_Escape:
       case Qt::Key_Tab:
       case Qt::Key_Backtab:
            e->ignore();
            return; // let the completer do default behavior
       default:
           break;
       }
    }

    bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_E); // CTRL+E
    if (!c || !isShortcut) // do not process the shortcut when we have a completer
        QTextEdit::keyPressEvent(e);

    const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
   if (!c || (ctrlOrShift && e->text().isEmpty()))
       return;

   static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
   bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
   QString completionPrefix = textUnderCursor();

   if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 3
                     || eow.contains(e->text().right(1)))) {
       c->popup()->hide();
       return;
   }

   if (completionPrefix != c->completionPrefix()) {
       c->setCompletionPrefix(completionPrefix);
       c->popup()->setCurrentIndex(c->completionModel()->index(0, 0));
   }
   QRect cr = cursorRect();
   cr.setWidth(c->popup()->sizeHintForColumn(0)
               + c->popup()->verticalScrollBar()->sizeHint().width());
   c->complete(cr); // pop it up!
}

void BackgroundHighlighter::focusInEvent(QFocusEvent *e)
{
    if (c)
        c->setWidget(this);
    QTextEdit::focusInEvent(e);
}

//  convenience function for setting a `charFmt` at a `position`
void BackgroundHighlighter::setWordFormat(const int &position, const QTextCharFormat &charFmt)
{
    QTextCursor cursor = textCursor();
    cursor.setPosition(position);
    cursor.select(QTextCursor::WordUnderCursor);
    cursor.setCharFormat(charFmt);
}

//  this will handle the `QTextEdit::cursorPositionChanged()` signal
void BackgroundHighlighter::onCursorPositionChanged()
{
    //  if cursor landed on different format, the `currentCharFormat` will be changed
    //  we need to change it back to white
    setCurrentCharFormat(defaultFmt);

    //  this is the function you're looking for
    runHighlight(); 
}

void BackgroundHighlighter::insertCompletion(const QString &completion)
{
    if (c->widget() != this)
        return;
    QTextCursor tc = textCursor();
    int extra = completion.length() - c->completionPrefix().length();
    tc.movePosition(QTextCursor::Left);
    tc.movePosition(QTextCursor::EndOfWord);
    tc.insertText(completion.right(extra));
    setTextCursor(tc);
}

QString BackgroundHighlighter::textUnderCursor() const
{
    QTextCursor tc = textCursor();
    tc.select(QTextCursor::WordUnderCursor);
    return tc.selectedText();
}

/**
 * BRIEF
 * Check if new highlighting is needed
 * Clear previous highlights
 * Check if the word under the cursor is a symbol (i.e. matches ^[A-Za-z0-9_]+$)
 * Highlight all relevant symbols
 */
void BackgroundHighlighter::runHighlight()
{
    //  retrieve cursor
    QTextCursor cursor = textCursor();

    //  retrieve word under cursor
    cursor.select(QTextCursor::WordUnderCursor);
    QString wordUnder = cursor.selectedText();
    qDebug() << "Word Under Cursor:" << wordUnder;

    //  get front of cursor, used later for storing in `highlightPositions` or `mainHighlightPosition`
    int cursorFront = cursor.selectionStart();

    //  if the word under cursor is the same, then save time
    //  by skipping the process
    if (wordUnder == highlightSymbol)
    {
        //  switch formats
        setWordFormat(mainHighlightPosition, subsidiaryFmt);    //  change previous main to subsidiary
        setWordFormat(cursorFront, mainFmt);                  //  change position under cursor to main

        //  update main position
        mainHighlightPosition = cursorFront;

        //  jump the gun
        return;
    }

    //  clear previous highlights
    if (mainHighlightPosition != -1)
        clearHighlights();

    //  check if selected word is a symbol
    if (!wordUnder.contains(QRegularExpression("^[A-Za-z0-9_]+$")))
    {
        qDebug() << wordUnder << "is not a symbol!";
        return;
    }

    //  set the highlight symbol
    highlightSymbol = wordUnder;

    //  store the cursor position to check later
    mainHighlightPosition = cursorFront;

    //  highlight all relevant symbols
    highlightMatchingSymbols(wordUnder);

    qDebug() << "Highlight done\n\n";
}

//  clear previously highlights
void BackgroundHighlighter::clearHighlights()
{
    QTextCursor cursor = textCursor();

    //  wipe the ENTIRE document with the default background, this should be REALLY fast
    //  WARNING: this may have unintended consequences if you have other backgrounds you want to keep
    cursor.select(QTextCursor::Document);
    cursor.setCharFormat(defaultFmt);

    //  reset variables
    mainHighlightPosition = -1;
    highlightSymbol.clear();
}

//  highlight all matching symbols
void BackgroundHighlighter::highlightMatchingSymbols(const QString &symbol)
{
    //  highlight background of congruent symbols
    QString docText = toPlainText();

    //  use a regex with \\b to look for standalone symbols
    QRegularExpression regexp("\\b" + symbol + "\\b");

    //  loop through all matches in the text
    int matchPosition = docText.indexOf(regexp);
    while (matchPosition != -1)
    {
        //  if the position 
        setWordFormat(matchPosition, matchPosition == mainHighlightPosition ? mainFmt : subsidiaryFmt);

        //  find next match
        matchPosition = docText.indexOf(regexp, matchPosition + 1);
    }
}
