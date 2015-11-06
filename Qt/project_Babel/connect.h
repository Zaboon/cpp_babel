#ifndef CONNECT_H
#define CONNECT_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QShortcut>
#include <QKeyEvent>
#include <string>
#include "home.h"

namespace Ui {
class Connect;
}

class Home;

class Connect : public QMainWindow
{
    Q_OBJECT

public:
    explicit Connect(QWidget *parent = 0);
    ~Connect();
    std::string getUsername();
    std::string getIP();
    int         setUsername();
    int         setIP();
    void       keyPressEvent(QKeyEvent *event);

public slots:
    void    raiseWindow();
    void    getInfos();

private:
    Ui::Connect    *ui;
    bool        isRaise;
    QString     username;
    QString     ipAddress;
    QMessageBox *box;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    Home    *_home;

};


#endif // CONNECT_H
