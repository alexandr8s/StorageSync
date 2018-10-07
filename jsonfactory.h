#ifndef JSONFACTORY_H
#define JSONFACTORY_H

#include <QTreeWidget>
#include <QJsonValue>
#include <QLabel>

typedef QPair<QString, QJsonValue> QJson;

class JsonFactory: public QObject
{
private:
    QTreeWidgetItem * jsonItems(QString name, QJsonValue jval);
    QJson treeItems(QTreeWidgetItem * item);

public:
    explicit JsonFactory(QObject *parent = nullptr);
    QString openJson(QTreeWidget * refWidget);
    void saveJson(QTreeWidget * refWidget);
};

#endif // JSONFACTORY_H
