#ifndef CALLING_H
#define CALLING_H

#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMainWindow>
#include "home.h"

namespace Ui {
class calling;
}

class Home;

class calling : public QMainWindow
{
    Q_OBJECT

public:
    explicit calling(QString &name, QString &usr, QWidget *parent = 0);
    ~calling();

public slots:
    void raiseWindow();
    void hangUp();

private:
    Ui::calling     *ui;
    QString         name;
    int                 m_nMouseClick_X_Coordinate;
    int                 m_nMouseClick_Y_Coordinate;
    bool              isRaise;
    Home           *home;
    QMediaPlayer      *player;
    QMediaPlaylist    *playlist;


    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // CALLING_H
