#include "storagesync.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StorageSync w;
    w.show();

    return a.exec();
}
