/**
  Licensed under the MIT License.
  For a full description, see https://stackoverflow.com/a/53351512/10239789 
  
  Qt Examples Used:
  Syntax Highlighter Example: https://doc.qt.io/qt-5/qtwidgets-richtext-syntaxhighlighter-example.html
  Custom Completer Example: http://doc.qt.io/qt-5/qtwidgets-tools-customcompleter-example.html
  **/

#include <QApplication>
#include <backgroundhighlighter.h>

QAbstractItemModel *modelFromFile(const QString& fileName, QCompleter *completer)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;

    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        if (!line.isEmpty())
            words << line.trimmed();
    }
	
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
	
    return new QStringListModel(words, completer);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
	
	//	loads text from file
	//	BackgroundHighlighter bh(":/res/symbols.txt");
	
	//	uses default text
	BackgroundHighlighter bh;
	
	QCompleter *completer = new QCompleter();
	
	completer->setModel(modelFromFile(":/res/wordlist.txt", completer));
	
	//	test implementation
	//	QStringListModel *model = new QStringListModel(QStringList() << "aaaaaaa" << "aaaaab" << "aaaabb" << "aaacccc",
	//												   completer);
	//	completer->setModel(model);
	
	completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	completer->setWrapAround(false);
	bh.setCompleter(completer);
	
	bh.show();

	return a.exec();
}
