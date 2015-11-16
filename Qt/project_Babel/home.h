#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <iostream>
#include <QMouseEvent>
#include <QStyle>
#include <QDesktopWidget>
#include <QListView>
#include <QStringList>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QDir>
#include <QScrollBar>
#include "incomingcall.h"
#include "calling.h"

namespace Ui {
class Home;
}

class calling;

class incomingCall;

class Home : public QMainWindow
{
    Q_OBJECT

public slots:
    void    raiseWindow();
    void    openDiscussion(QListWidgetItem*);
    void    incoming_Call();
    void    setRingtone();

public:
    explicit Home(QString &str, QWidget *parent = 0);
    static Home *getHome(QString usr = "");
    QString getUsername() const;
    QString getRingtone() const;
    bool getRaise() const;
    void addContact(std::string&);
    void removeContact(const std::string&);
    ~Home();

private:
    Ui::Home    *ui;
    bool        isRaise;
    QString     username;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
    incomingCall    *in_call;
    calling             *call;
    QString     fileName;
};

#endif // HOME_H
