#ifndef MOONPLAYER_H
#define MOONPLAYER_H

#include <QWidget>
#include "PlayerControlWidget.h"
#include "ui_PlayerWidget.h"
#include "MoonPlayer/MoonPlayer.h"
class MoonAVFrame;
namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    ~PlayerWidget();
    MoonPlayer player;
    void repaint(MoonAVFrame* frame);
public slots:
    void start();
    void open(QString url);

protected:
    void resizeEvent(QResizeEvent* event);

private:
    void initUi();
    void initConnect();

private:
    
    Ui::PlayerWidget *ui = nullptr;
    PlayerControlWidget* pPlayerControlWidget = nullptr;
};

#endif // MOONPLAYER_H
