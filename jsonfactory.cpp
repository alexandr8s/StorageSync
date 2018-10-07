#include "jsonfactory.h"

#include <QDir>
#include <QFileDialog>
#include <QFileIconProvider>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

JsonFactory::JsonFactory(QObject *parent) : QObject(parent)
{
}

QString JsonFactory::openJson(QTreeWidget * refWidget)
{
    QString path = QFileDialog::getOpenFileName(refWidget->parentWidget(), "Open JSON", "/", "JSON file (*.json)");
    refWidget->clear();

    QFile jsonFile(path);
    jsonFile.open(QFile::ReadOnly);
    QByteArray rawData = jsonFile.readAll();
    jsonFile.close();
    QJsonDocument jdoc(QJsonDocument::fromJson(rawData));
    jdoc.fromJson(jsonFile.readAll());
    QJsonObject json = jdoc.object();

    foreach(const QString & key, json.keys())
        refWidget->addTopLevelItem(jsonItems(key, json.value(key)));

    return path;
}

void JsonFactory::saveJson(QTreeWidget * refWidget)
{
    QString path = QFileDialog::getSaveFileName(refWidget->parentWidget(), "Save JSON", "/", "JSON file (*.json)");

    QJsonObject json;
    for(int i = 0; i < refWidget->topLevelItemCount(); ++i)
    {
        QJson j = treeItems(refWidget->topLevelItem(i));
        json.insert(j.first , j.second);
    }

    QFile jsonFile(path);
    jsonFile.open(QFile::WriteOnly);
    QJsonDocument jdoc;
    jdoc.setObject(json);
    jsonFile.write(jdoc.toJson());
    jsonFile.close();
}

QTreeWidgetItem * JsonFactory::jsonItems(QString name, QJsonValue jval)
{
    QTreeWidgetItem * item = new QTreeWidgetItem();
    item->setText(0, name);

    if (jval.isArray())
    {
        QJsonArray file = jval.toArray();
        item->setText(1, file.at(0).toString());
        item->setText(2, file.at(1).toString());
        item->setIcon(0, QFileIconProvider().icon(QFileIconProvider::File));
    }

    if (jval.isObject())
    {
        QJsonObject json = jval.toObject();
        foreach(const QString & name, json.keys())
        {
            item->addChild(jsonItems(name, json.value(name)));
            QCoreApplication::processEvents();
        }
        item->setIcon(0, QFileIconProvider().icon(QFileIconProvider::Folder));
    }

    return item;
}

QJson JsonFactory::treeItems(QTreeWidgetItem * item)
{
    if (item->text(1) == "")
    {
        QJsonObject file;
        for(int i = 0; i < item->childCount(); ++i)
        {
            QJson j = treeItems(item->child(i));
            file.insert(j.first , j.second);
        }
        return QJson(item->text(0), file);
    }
    else
    {
        QJsonArray dir = {item->text(1), item->text(2)};
        return QJson(item->text(0), dir);
    }
}
