#ifndef MOONPLAYER_H
#define MOONPLAYER_H

#include <QWidget>
#include "PlayerControlWidget.h"
#include "ui_PlayerWidget.h"


namespace Ui {
class PlayerWidget;
}

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    ~PlayerWidget();

protected:
    void resizeEvent(QResizeEvent* event);

public slots:
    void start();
private:
    void initUi();
    void initConnect();

private:
    
    Ui::PlayerWidget *ui = nullptr;
    PlayerControlWidget* pPlayerControlWidget = nullptr;
};

#endif // MOONPLAYER_H
