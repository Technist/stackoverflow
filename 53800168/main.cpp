#include <QtCore>
#include <QtWidgets>

class DyTextEdit : public QTextEdit
{
	Q_OBJECT
public:
	DyTextEdit(QWidget *parent = nullptr) :
		QTextEdit(parent)
	{
		QTextDocument *doc = document();
		currentSize = doc->size();
		
		qDebug() << "[Init] Size:" << currentSize;
		
		//	listen to text/content changes
		connect(this, &QTextEdit::textChanged, this, &DyTextEdit::on_textChanged);
		
		//	connect <> 💡
		connect(this, &DyTextEdit::sizeChanged, this, &DyTextEdit::resizeParent);
		
		emit sizeChanged(currentSize);	//	init
	}
	
signals:
	//	emitted when document size changes
	void sizeChanged(QSizeF size);
	
public slots:
	void on_textChanged()
	{
		QSizeF newSize = document()->size();
		
		qDebug() << "[TextChanged] Size:" << newSize;
		
		//	detect changes in the document size
		if (newSize != currentSize)
			emit sizeChanged(newSize);  //  emit signal💡
		
		//	update size
		currentSize = newSize;
	}
	
	void resizeParent(QSizeF size)
	{
		//	resize the parent's height, don't bother with the width
		parentWidget()->setFixedHeight(size.height());
	}
	
private:
	QSizeF currentSize;	//	keeps track of current document size
	
};

class Cell : public QWidget
{
	Q_OBJECT
public:
	Cell(QWidget *parent = nullptr) :
		QWidget(parent)
	{
		//	create widget to contain dyTextEdit
		QWidget *dyEditContainer = new QWidget;
		textEdit = new DyTextEdit(dyEditContainer);	//	create the textedit
		QVBoxLayout *dyEditLayout = new QVBoxLayout(dyEditContainer);
		dyEditLayout->setMargin(0);
		dyEditLayout->addWidget(textEdit);
		
		//	create new buttons, these do nothing right now
		QPushButton *pb1 = new QPushButton("Push this.", this);
		QPushButton *pb2 = new QPushButton("No, push this!", this);
		
		//	add buttons to buttons layout
		buttons = new QHBoxLayout;
		buttons->addWidget(pb1);
		buttons->addWidget(pb2);
		
		//	set overall cell layout
		QVBoxLayout *cellLayout = new QVBoxLayout(this);
		cellLayout->setMargin(0);
		cellLayout->addWidget(dyEditContainer);
		cellLayout->addLayout(buttons);
		cellLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
		
	}
	
private:
	//	modify member variables as needed
	DyTextEdit *textEdit;
	QHBoxLayout *buttons;	//	buttons layout
	
};

class CellBased : public QWidget
{
	Q_OBJECT
public:
	CellBased(int numCells = 1, QWidget *parent = nullptr) :
		QWidget(parent)
	{
		//	if (numCells < 0) { /* handle error */ }
		
		QVBoxLayout *cbLayout = new QVBoxLayout(this);
		cbLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
		for (int i = 0; i < numCells; i++)
		{
			Cell *c = new Cell(this);
			cbLayout->addWidget(c);
			
			cells.append(c);
		}
	}
	
private:
	//	modify member variables as needed
	QList<Cell*> cells;
	
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	CellBased cb(3);
	cb.show();
	
	return a.exec();
}

#include "main.moc"	//	include as there are QObject classes in main.cpp


