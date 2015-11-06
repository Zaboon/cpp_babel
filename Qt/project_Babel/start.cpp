#include "start.h"
#include "connect.h"
#include "ui_start.h"

Start::Start(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon("./images/logo.png"));
    connect(ui->startButton, SIGNAL(clicked(bool)), this, SLOT(openConnexion()));
}

Start::~Start()
{
    delete ui;
}

// METHODS

void            Start::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == 16777220 || event->key() == 16777221)
        openConnexion();
}

// SLOTS

void    Start::openConnexion()
{
    this->_connexion = new Connect;
    this->_connexion->show();
    this->close();
}

