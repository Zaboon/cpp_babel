#include "home.h"
#include "ui_home.h"

Home::Home(QString &str, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
    this->username = str;

    this->isRaise = false;
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    this->activateWindow();
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon("./images/logo.png"));
    this->ui->username->setText("Welcome "+this->username);
    ui->chooseButton->setIcon(QIcon("./images/music.png"));
    ui->chooseButton->setIconSize(QSize(91, 91));
    this->ui->label_2->setStyleSheet("background-image: url(\"./images/logo1.png\");  border-radius:0px;  max-width:100px; max-height:100px; min-width:100px; min-height:100px;");

    connect(this->ui->listFriends, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(openDiscussion(QListWidgetItem*)));
    connect(ui->raiseButton, SIGNAL(clicked(bool)), this, SLOT(raiseWindow()));
    connect(ui->lol, SIGNAL(clicked(bool)), this, SLOT(incoming_Call()));
    connect(ui->chooseButton, SIGNAL(clicked(bool)), this, SLOT(setRingtone()));
}

Home::~Home()
{
    delete this->in_call;
    delete this->call;
    delete ui;
}

//METHODS
void    Home::mousePressEvent(QMouseEvent *event)
{
    m_nMouseClick_X_Coordinate = event->x();
    m_nMouseClick_Y_Coordinate = event->y();
}


void    Home::mouseMoveEvent(QMouseEvent *event)
{
    if (isRaise == false)
        move(event->globalX()-m_nMouseClick_X_Coordinate,event->globalY()-m_nMouseClick_Y_Coordinate);
}

Home    *Home::getHome(QString usr)
{
    static Home    *m_home;

    if (m_home == NULL)
        m_home = new Home(usr);
    return m_home;
}

QString     Home::getUsername() const
{
    return this->username;
}

QString     Home::getRingtone() const
{
    return this->fileName;
}

bool            Home::getRaise() const
{
    return this->isRaise;
}

void             Home::addContact(std::string& username)
{
    this->ui->listFriends->addItem(QString::fromStdString(username));
}

void             Home::removeContact(const std::string& username)
{
    for (int i = 0; i < this->ui->listFriends->count(); i++)
    {
        QListWidgetItem *elem = this->ui->listFriends->item(i);
        if (elem->text().toStdString() == username)
        {
            this->ui->listFriends->removeItemWidget(elem);
            return;
        }
    }
}

//SLOTS
void    Home::raiseWindow()
{
    if (this->isRaise == false)
    {
        this->showMaximized();
        this->ui->listFriends->setFixedSize(400, 800);
        this->isRaise = true;
        return;
    }
    else
    {
        this->ui->listFriends->setFixedSize(254, 484);
        this->showNormal();
    }
    this->isRaise = false;
}

void    Home::openDiscussion(QListWidgetItem *elem)
{
    QString ncall = elem->text();
    this->hide();
    this->call = new calling(ncall, this->username);
    this->call->show();
}

void    Home::incoming_Call()
{
    QString ncall = "Timur";
    this->hide();
    this->in_call = new incomingCall(ncall, this->username);
    this->in_call->show();
}

void    Home::setRingtone()
{
    this->fileName = QFileDialog::getOpenFileName(this, tr("Choose ringtone"), QDir::homePath(), tr("Sounds (*.mp3 *.wav *.mp4)"));
}
