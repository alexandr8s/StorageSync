#include "dirfactory.h"

#include <cmath>
#include <QDir>
#include <QFileDialog>
#include <QFileIconProvider>
#include <QCoreApplication>
#include <QDateTime>


DirFactory::DirFactory(QObject *parent) : QObject(parent)
{
}

QString DirFactory::openPath(QTreeWidget * refWidget)
{
    QString path = QFileDialog::getExistingDirectory(refWidget->parentWidget(), "Open Path", "/", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    QFileInfo workDir(path);
    refWidget->clear();

    foreach(QFileInfo mob, QDir(workDir.absoluteFilePath()).entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot))
        refWidget->addTopLevelItem(dirItems(&mob));

    return path;
}

QTreeWidgetItem * DirFactory::dirItems(QFileInfo *fileInfo)
{
    QTreeWidgetItem * item = new QTreeWidgetItem();
    item->setText(0, fileInfo->fileName());

    if (fileInfo->isFile())
    {
        item->setText(1, (stringSize(fileInfo->size())));
        item->setText(2, fileInfo->created().toString("dd/MM/yyyy hh:mm:ss"));
        item->setIcon(0, QFileIconProvider().icon(QFileIconProvider::File));
        return item;
    }
    item->setIcon(0, QFileIconProvider().icon(QFileIconProvider::Folder));

    foreach(QFileInfo mob, QDir(fileInfo->absoluteFilePath()).entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot))
    {
        item->addChild(dirItems(&mob));
        QCoreApplication::processEvents();
    }

    return item;
}

QString DirFactory::stringSize(float num)
{
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";
    QStringListIterator i(list);
    QString unit("B");
    while(num >= 1024.0 && i.hasNext())
    {
        unit = i.next();
        num /= 1024.0;
    }

    int decimal = int(std::fmod(num, 1) *100);
    int tail;
    if (decimal % 100 == 0)
        tail = 0;
    else if (decimal % 10 == 0)
        tail = 1;
    else
        tail = 2;

    return QString().setNum(num, 'f', tail) +" " + unit;
}
