#include "connexion.h"
#include "ui_connexion.h"
#include <iostream>
#include <QMouseEvent>
#include <QStyle>
#include <QDesktopWidget>

Connexion::Connexion(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Connexion)
{
    ui->setupUi(this);
    this->isRaise = false;
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->activateWindow();
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(QString::fromUtf8("C:/Users/nicolas/Documents/Babel/logo.png")));
    connect(ui->raiseButton, SIGNAL(clicked(bool)), this, SLOT(raiseWindow()));
    connect(ui->ok, SIGNAL(clicked(bool)), this, SLOT(getInfos()));
}

Connexion::~Connexion()
{
    delete ui;
}

// METHODS
void    Connexion::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}


void    Connexion::mouseMoveEvent(QMouseEvent *event)
{
    if (isRaise == false)
        move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

int    Connexion::setUsername()
{
    if (this->ui->Username->text().isEmpty())
        return -1;
    this->username = this->ui->Username->text();
    return 0;
}

int    Connexion::setIP()
{
    if (this->ui->ipAddress->text().isEmpty())
        return -1;
    this->ipAddress = this->ui->ipAddress->text();
    return 0;
}

std::string Connexion::getUsername()
{
    return this->username.toStdString();
}

std::string Connexion::getIP()
{
    return this->ipAddress.toStdString();
}

// SLOTS
void    Connexion::raiseWindow()
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

void    Connexion::getInfos()
{
    QString     str;

    if (this->setUsername() == -1)
        str = "Missing Username !\n";
    if (this->setIP() == -1)
        str += "Missing IP Address !\n";
    if (!str.isEmpty())
    {
        this->box = new QMessageBox;
        this->box->setStyleSheet("QMessageBox { background-color : #AEAFAF }");
        this->box->setText(str);
        this->box->setWindowFlags(Qt::FramelessWindowHint);
        this->box->setIcon(QMessageBox::Critical);
        this->box->setFixedSize(250, 100);
        this->box->exec();
        this->ui->Username->clear();
        this->ui->ipAddress->clear();
        return;
    }
    std::cout << "Username:" << this->username.toStdString() << "." << std::endl;
    std::cout << "IP Address:" << this->ipAddress.toStdString() << "." << std::endl;
}

