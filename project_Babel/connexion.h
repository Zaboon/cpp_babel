#ifndef CONNEXION_H
#define CONNEXION_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QShortcut>
#include <string>

namespace Ui {
class Connexion;
}

class Connexion : public QMainWindow
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = 0);
    ~Connexion();
    std::string getUsername();
    std::string getIP();
    int         setUsername();
    int         setIP();

public slots:
    void    raiseWindow();
    void    getInfos();

private:
    Ui::Connexion    *ui;
    bool        isRaise;
    QString     username;
    QString     ipAddress;
    QMessageBox *box;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    int m_nMouseClick_X_Coordinate;
    int m_nMouseClick_Y_Coordinate;
};

#endif // CONNEXION_H
