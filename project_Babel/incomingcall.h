#ifndef INCOMINGCALL_H
#define INCOMINGCALL_H

#include <QMainWindow>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include "home.h"

namespace Ui {
class incomingCall;
}

class Home;

class incomingCall : public QMainWindow
{
    Q_OBJECT

public:
    explicit incomingCall(QString &str, QString &usr, QWidget *parent = 0);
    ~incomingCall();

public slots:
    void raiseWindow();
    void hangUp();
    void answering();

protected:
    Ui::incomingCall   *ui;
    QString                 name;
    int                         m_nMouseClick_X_Coordinate;
    int                         m_nMouseClick_Y_Coordinate;
    bool                      isRaise;
    Home                   *home;
    QMediaPlayer      *player;
    QMediaPlaylist    *playlist;
    QString                 fileName;

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // INCOMINGCALL_H
