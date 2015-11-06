#ifndef START_H
#define START_H

#include <QMainWindow>
#include <QKeyEvent>
#include "connect.h"

class connexion;

namespace Ui {
class Start;
}

class Start : public QMainWindow
{
    Q_OBJECT

public:
    explicit Start(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    ~Start();

public slots:
    void openConnexion();

private:
    Ui::Start *ui;
    Connect    *_connexion;
};

#endif // START_H
