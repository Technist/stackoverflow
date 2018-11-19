#ifndef BACKGROUNDHIGHLIGHTER_H
#define BACKGROUNDHIGHLIGHTER_H

#include <QtWidgets>
#include <QtGui>

//	this is the file to your highlighter
#include "highlighter.h"

class BackgroundHighlighter : public QTextEdit
{
	Q_OBJECT
public:
	BackgroundHighlighter(const QString &fileName = QString(), QWidget *parent = nullptr);
	
	void loadFile(const QString &fileName);
	
	void setCompleter(QCompleter *completer);
	QCompleter *completer() const;
	
protected:
	void keyPressEvent(QKeyEvent *e) override;
	void focusInEvent(QFocusEvent *e) override;

public slots:
	void onCursorPositionChanged();
	
private slots:
    void insertCompletion(const QString &completion);
	
private:
	//	this is your syntax highlighter
	Highlighter *syntaxHighlighter;
	
	//	stores the symbol being highlighted
	QString highlightSymbol;
	
	//	stores the position (front of selection) where the cursor was originally placed
	int mainHighlightPosition;
	
	//	stores character formats to be used
	QTextCharFormat mainFmt;
	QTextCharFormat subsidiaryFmt;
	QTextCharFormat defaultFmt;
	
	void setWordFormat(const int &position, const QTextCharFormat &format);
	void runHighlight();
	void clearHighlights();
	void highlightMatchingSymbols(const QString &symbol);
	
	//	completer
	QString textUnderCursor() const;
    QCompleter *c;
	
};

#endif // BACKGROUNDHIGHLIGHTER_H
