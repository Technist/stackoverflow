#include <QApplication>
#include <QQmlApplicationEngine>

#include <QDebug>

int main(int argc, char *argv[])
{

	QApplication app(argc, argv);

	QQmlApplicationEngine engine;
	engine.load(QStringLiteral(":/qml/Main.qml"));
	
	return app.exec();
}
