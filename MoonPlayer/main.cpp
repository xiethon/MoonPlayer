#include <QApplication>
#include "PlayerWidget.h"
#include "MoonPlayer/MoonPlayer.h"

PlayerWidget* g_player;
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    PlayerWidget p;
    g_player = &p;
    p.show();

    return app.exec();
}