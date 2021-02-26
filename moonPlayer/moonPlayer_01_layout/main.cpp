#include "MoonPlayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MoonPlayer w;
    w.show();
    return a.exec();
}
