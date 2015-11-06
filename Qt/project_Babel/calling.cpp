#include <QMouseEvent>
#include "calling.h"
#include "ui_calling.h"

calling::calling(QString &str, QString &usr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::calling)
{
    ui->setupUi(this);
    this->name = str;
    this->isRaise = false;
    this->home = Home::getHome(usr);
    this->player = new QMediaPlayer;
    this->playlist = new QMediaPlaylist(this->player);
    this->playlist->addMedia(QUrl::fromLocalFile("./sounds/calling.mp3"));
    this->playlist->setPlaybackMode(QMediaPlaylist::Loop);
    this->player->setPlaylist(this->playlist);
    this->player->setVolume(100);
    this->player->play();
    ui->name->setText("Calling " + this->name);
    ui->hangupButton->setIcon(QIcon("./images/hang_up.png"));
    ui->hangupButton->setIconSize(QSize(91, 91));
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->activateWindow();
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(QString::fromUtf8("./images/logo.png")));

    connect(this->ui->raiseButton, SIGNAL(clicked(bool)), this, SLOT(raiseWindow()));
    connect(ui->hangupButton, SIGNAL(clicked(bool)), this, SLOT(hangUp()));
    connect(ui->quitButton, SIGNAL(clicked(bool)), this, SLOT(hangUp()));
}

calling::~calling()
{
    delete ui;
}

// METHODS
void    calling::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}


void    calling::mouseMoveEvent(QMouseEvent *event)
{
    if (isRaise == false)
        move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

// SLOTS
void    calling::raiseWindow()
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

void    calling::hangUp()
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
