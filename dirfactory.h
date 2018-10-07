#ifndef DIRFACTORY_H
#define DIRFACTORY_H

#include <QTreeWidget>
#include <QFileInfo>

class DirFactory: public QObject
{
private:
    QTreeWidgetItem * dirItems(QFileInfo *fileInfo);
    QString stringSize(float num);

public:
    explicit DirFactory(QObject *parent = nullptr);
    QString openPath(QTreeWidget * refWidget);
};

#endif // DIRFACTORY_H
