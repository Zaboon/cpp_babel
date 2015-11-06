#include "connect.h"
#include "ui_connect.h"
#include <iostream>
#include <QMouseEvent>
#include <QStyle>
#include <QDesktopWidget>

Connect::Connect(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Connect)
{
    ui->setupUi(this);
    this->isRaise = false;
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->activateWindow();
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(QString::fromUtf8("./images/logo.png")));
    this->setTabOrder(this->ui->Username, this->ui->ipAddress);
    this->ui->Username->setFocus();
    this->ui->label_3->setStyleSheet("background-image: url(\"./images/logo1.png\"); border-radius:0px;");

    connect(ui->raiseButton, SIGNAL(clicked(bool)), this, SLOT(raiseWindow()));
    connect(ui->ok, SIGNAL(clicked(bool)), this, SLOT(getInfos()));
}

Connect::~Connect()
{
    delete ui;
}

// METHODS
void    Connect::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}


void    Connect::mouseMoveEvent(QMouseEvent *event)
{
    if (isRaise == false)
        move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

int    Connect::setUsername()
{
    if (this->ui->Username->text().isEmpty())
        return -1;
    this->username = this->ui->Username->text();
    return 0;
}

int    Connect::setIP()
{
    if (this->ui->ipAddress->text().isEmpty())
        return -1;
    this->ipAddress = this->ui->ipAddress->text();
    return 0;
}

std::string Connect::getUsername()
{
    return this->username.toStdString();
}

std::string Connect::getIP()
{
    return this->ipAddress.toStdString();
}

void            Connect::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == 16777220 || event->key() == 16777221)
        getInfos();
}

// SLOTS
void    Connect::raiseWindow()
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

void    Connect::getInfos()
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
    this->_home = Home::getHome(this->username);
    this->_home->show();
    this->close();
}

