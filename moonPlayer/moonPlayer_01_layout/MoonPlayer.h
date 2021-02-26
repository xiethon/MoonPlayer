#ifndef MOONPLAYERMAINWIDGET_H
#define MOONPLAYERMAINWIDGET_H

#include <QWidget>
#include "ui_MoonPlayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MoonPlayerMainWidget; }
QT_END_NAMESPACE

class MoonPlayer : public QWidget
{
    Q_OBJECT

public:
    MoonPlayer(QWidget *parent = nullptr);
    ~MoonPlayer();
private:
    void initUi();
    void initConnect();
private:
    Ui::MoonPlayer *ui;
};
#endif // MOONPLAYERMAINWIDGET_H
