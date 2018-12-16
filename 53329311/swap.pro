TEMPLATE += app

qmlFolder.source = qml
DEPLOYMENTFOLDERS += qmlFolder # comment for publishing

QT += widgets quick
RESOURCES += qml.qrc
SOURCES += main.cpp
