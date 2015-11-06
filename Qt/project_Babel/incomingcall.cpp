#include <QMouseEvent>
#include <iostream>
#include <QFileInfo>
#include "incomingcall.h"
#include "ui_incomingcall.h"

incomingCall::incomingCall(QString &str, QString &usr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::incomingCall)
{
    this->name = str;
    ui->setupUi(this);
    this->home = Home::getHome(usr);
    this->player = new QMediaPlayer;
    this->playlist = new QMediaPlaylist(this->player);
    if ((this->fileName = this->home->getRingtone()).isEmpty())
    {
        std::cout << "mpm" << std::endl;
        this->fileName = "./sounds/ringing.mp3";
    }
    this->playlist->addMedia(QUrl::fromLocalFile(this->fileName));
    this->playlist->setPlaybackMode(QMediaPlaylist::Loop);
    this->player->setPlaylist(this->playlist);
    this->player->setVolume(100);
    this->player->play();
    std::cout << this->fileName.toStdString() << std::endl;
    ui->name->setText("Incoming call from " + this->name);
    ui->answerButton->setIcon(QIcon("./images/answer.png"));
    ui->hangupButton->setIcon(QIcon("./images/hang_up.png"));
    ui->answerButton->setIconSize(QSize(64, 64));
    ui->hangupButton->setIconSize(QSize(91, 91));
    this->isRaise = false;
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->activateWindow();
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(QString::fromUtf8("./images/logo.png")));

    connect(ui->raiseButton, SIGNAL(clicked(bool)), this, SLOT(raiseWindow()));
    connect(ui->hangupButton, SIGNAL(clicked(bool)), this, SLOT(hangUp()));
    connect(ui->answerButton, SIGNAL(clicked(bool)), this, SLOT(answering()));
    connect(ui->quitButton, SIGNAL(clicked(bool)), this, SLOT(hangUp()));
}

incomingCall::~incomingCall()
{
    delete ui;
}

// METHODS
void    incomingCall::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}


void    incomingCall::mouseMoveEvent(QMouseEvent *event)
{
    if (isRaise == false)
        move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

// SLOTS
void    incomingCall::raiseWindow()
{
    if (this->isRaise == false)
    {
        this->showMaximized();
        this->isRaise = true;
        return;
    }
    else
        this->showNormal();
    this->isRaise = false;
}

void    incomingCall::hangUp()
{
    this->close();
    this->player->stop();
    if (this->home->getRaise())
    {
        this->home->showMaximized();
        return;
    }
    this->home->showNormal();
}

void    incomingCall::answering()
{
    this->ui->buttonLayout->removeWidget(this->ui->answerButton);
    this->player->stop();
    this->ui->answerButton->close();
}
