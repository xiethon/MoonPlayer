#ifndef MOONPLAYERCONTROL_H
#define MOONPLAYERCONTROL_H

#include <QWidget>
#include "ui_PlayerControlWidget.h"

namespace Ui {
class PlayerControlWidget;
}

class PlayerControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerControlWidget(QWidget *parent = nullptr);
    ~PlayerControlWidget();

private:
    void initUi();
    void initConnect();

signals:
    void start();
    //void pause();
    //void seek();

private:
    Ui::PlayerControlWidget*ui;
};

#endif // PLAYERCONTROL_H
