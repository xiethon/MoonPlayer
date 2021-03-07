#include "PlayerWidget.h"
#include "MoonPlayer/format/MoonAVFormat.h"
#include "MoonPlayer/format/MoonAVPacket.h"
#include "PlayerGLWidget.h"
#include "MoonPlayer/video/MoonVideo.h"
#include "MoonPlayer/audio/MoonAudio.h"

#include <QCoreApplication>
#include <qDebug>


PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerWidget)
{
    initUi();
    initConnect();

	QString url = QCoreApplication::applicationDirPath() + "/test.mp4";
//	open(url);
//	ui->openGLWidget->Init(player.getVideoWidth(), player.getVideoHeight());
	

    
}

PlayerWidget::~PlayerWidget()
{
    delete ui;
}


void PlayerWidget::repaint(MoonAVFrame* frame)
{
    ui->openGLWidget->repaint(frame);
}

void PlayerWidget::start()
{
    //player.start();
}

void PlayerWidget::open(QString url)
{
    int ret = player.open(url.toStdString());
    if (ret != 0)
    {
        qDebug() << "Player Open Failed";
    }
    else 
    {
        qDebug() << "Player Open success";
    }
}

void PlayerWidget::initUi()
{
    ui->setupUi(this);
    show();

    pPlayerControlWidget = new PlayerControlWidget(ui->openGLWidget);
    QRect playerControlRect = QRect(0, 0, 100, 40);
    pPlayerControlWidget->setGeometry(playerControlRect);
    pPlayerControlWidget->show();
}

void PlayerWidget::initConnect()
{
    connect(pPlayerControlWidget, &PlayerControlWidget::start, this, &PlayerWidget::start);
}

void PlayerWidget::resizeEvent(QResizeEvent* event)
{
    /*if (pPlayerControlWidget != nullptr)
    {
        QRect playerControlRect = QRect(0, ui->openGLWidget->height() - 40, ui->openGLWidget->width(), 40);
        pPlayerControlWidget->setGeometry(playerControlRect);
        pPlayerControlWidget->show();
    }*/
}