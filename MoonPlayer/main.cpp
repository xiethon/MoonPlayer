#include <QApplication>
#include "PlayerWidget.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    PlayerWidget p;

    p.show();

    return app.exec();
}