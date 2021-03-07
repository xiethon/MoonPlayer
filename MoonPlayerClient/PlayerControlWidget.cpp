#include "PlayerControlWidget.h"

PlayerControlWidget::PlayerControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerControlWidget)
{
    initUi();
    initConnect();
}

PlayerControlWidget::~PlayerControlWidget()
{
    delete ui;
}

void PlayerControlWidget::initUi()
{
    ui->setupUi(this);
}

void PlayerControlWidget::initConnect()
{
    connect(ui->startTBtn, &QToolButton::clicked, [=]()
        {
            emit start();
        });
}
