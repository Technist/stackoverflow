#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	QQmlApplicationEngine engine;
	engine.load(QStringLiteral(":/Main.qml"));
	
	return app.exec();
}
