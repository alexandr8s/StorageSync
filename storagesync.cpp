#include "storagesync.h"
#include "ui_storagesync.h"

StorageSync::StorageSync(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StorageSync)
{
    ui->setupUi(this);

    ui->statusBar->addPermanentWidget(&statusLeft, 1);
    ui->statusBar->addPermanentWidget(&statusRight, 1);

    connect(ui->actionOpenPathLeft, SIGNAL(triggered(bool)), this, SLOT(actionOpenPathLeft_clicked()));
    connect(ui->actionOpenJSONLeft, SIGNAL(triggered(bool)), this, SLOT(actionOpenJsonLeft_clicked()));
    connect(ui->actionSaveJSONLeft, SIGNAL(triggered(bool)), this, SLOT(actionSaveJsonLeft_clicked()));

    connect(ui->actionOpenPathRight, SIGNAL(triggered(bool)), this, SLOT(actionOpenPathRight_clicked()));
    connect(ui->actionOpenJSONRight, SIGNAL(triggered(bool)), this, SLOT(actionOpenJsonRight_clicked()));
    connect(ui->actionSaveJSONRight, SIGNAL(triggered(bool)), this, SLOT(actionSaveJsonRight_clicked()));
}

StorageSync::~StorageSync()
{
    delete ui;
}

void StorageSync::actionOpenPathLeft_clicked()
{
    QString path = dirFactory.openPath(ui->treeWidgetLeft);
    statusLeft.setText(path);
}

void StorageSync::actionOpenPathRight_clicked()
{
    QString path = dirFactory.openPath(ui->treeWidgetRight);
    statusRight.setText(path);
}

void StorageSync::actionOpenJsonLeft_clicked()
{
    QString path = jsonFactory.openJson(ui->treeWidgetLeft);
    statusLeft.setText(path);
}

void StorageSync::actionOpenJsonRight_clicked()
{
    QString path = jsonFactory.openJson(ui->treeWidgetRight);
    statusRight.setText(path);
}

void StorageSync::actionSaveJsonLeft_clicked()
{
    jsonFactory.saveJson(ui->treeWidgetLeft);
}

void StorageSync::actionSaveJsonRight_clicked()
{
    jsonFactory.saveJson(ui->treeWidgetRight);
}




