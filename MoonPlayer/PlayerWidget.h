#ifndef MOONPLAYER_H
#define MOONPLAYER_H

#include <QWidget>
#include "PlayerControlWidget.h"
#include "ui_PlayerWidget.h"
#include "MoonPlayer/MoonPlayer.h"

namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    ~PlayerWidget();
   

public slots:
    void start();
    void open(QString url);

protected:
    void resizeEvent(QResizeEvent* event);

private:
    void initUi();
    void initConnect();

private:
    MoonPlayer player;
    Ui::PlayerWidget*ui = nullptr;
    PlayerControlWidget* pPlayerControlWidget = nullptr;
};

#endif // MOONPLAYER_H
