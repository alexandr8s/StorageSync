#ifndef STORAGESYNC_H
#define STORAGESYNC_H

#include <QMainWindow>

#include "dirfactory.h"
#include "jsonfactory.h"

namespace Ui {
class StorageSync;
}

class StorageSync : public QMainWindow
{
    Q_OBJECT

public:
    explicit StorageSync(QWidget *parent = 0);
    ~StorageSync();

private slots:
    void actionOpenPathLeft_clicked();
    void actionOpenJsonLeft_clicked();
    void actionSaveJsonLeft_clicked();
    void actionOpenPathRight_clicked();
    void actionOpenJsonRight_clicked();
    void actionSaveJsonRight_clicked();

private:
    DirFactory dirFactory;
    JsonFactory jsonFactory;
    QLabel statusLeft;
    QLabel statusRight;
    Ui::StorageSync *ui;
};

#endif // STORAGESYNC_H
