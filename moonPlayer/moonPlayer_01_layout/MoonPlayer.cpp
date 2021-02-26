#include "MoonPlayer.h"

MoonPlayer::MoonPlayer(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MoonPlayer)
{
    initUi();
    initConnect();
}

void MoonPlayer::initUi()
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
}

void MoonPlayer::initConnect()
{
    
}

MoonPlayer::~MoonPlayer()
{
    delete ui;
}

