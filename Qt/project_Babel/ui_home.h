/********************************************************************************
** Form generated from reading UI file 'home.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_H
#define UI_HOME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Home
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QListWidget *listFriends;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_12;
    QLabel *username;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *lol;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer;
    QPushButton *hideButton;
    QPushButton *raiseButton;
    QPushButton *quitButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *chooseButton;

    void setupUi(QMainWindow *Home)
    {
        if (Home->objectName().isEmpty())
            Home->setObjectName(QStringLiteral("Home"));
        Home->resize(1007, 644);
        Home->setStyleSheet(QLatin1String("border-width:2px;\n"
"border-radius:50px;\n"
"max-width:2000px;\n"
"max-height:2000px;\n"
"min-width:100px;\n"
"min-height:100px;"));
        centralwidget = new QWidget(Home);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setStyleSheet(QStringLiteral("background-color: grey;"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font.setPointSize(14);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        listFriends = new QListWidget(centralwidget);
        listFriends->setObjectName(QStringLiteral("listFriends"));
        QFont font1;
        font1.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font1.setPointSize(11);
        listFriends->setFont(font1);
        listFriends->setStyleSheet(QLatin1String("background-color : #AEAFAF;\n"
"border-style: outset;\n"
"border-radius: 0px;\n"
"min-height : 480px;\n"
"min-width : 250px;\n"
"max-height : 480px;\n"
"max-width : 250px;\n"
"\n"
""));
        listFriends->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listFriends->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listFriends->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);

        gridLayout->addWidget(listFriends, 1, 0, 4, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 6, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(label_2, 0, 4, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_12);

        username = new QLabel(centralwidget);
        username->setObjectName(QStringLiteral("username"));
        QFont font2;
        font2.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font2.setPointSize(16);
        username->setFont(font2);

        horizontalLayout_2->addWidget(username);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_13);


        gridLayout->addLayout(horizontalLayout_2, 2, 1, 1, 6);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 5, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_14, 0, 3, 1, 1);

        lol = new QPushButton(centralwidget);
        lol->setObjectName(QStringLiteral("lol"));

        gridLayout->addWidget(lol, 4, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, -1, -1, 75);
        horizontalSpacer_10 = new QSpacerItem(50, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_10);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        hideButton = new QPushButton(centralwidget);
        hideButton->setObjectName(QStringLiteral("hideButton"));
        QFont font3;
        font3.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font3.setPointSize(18);
        hideButton->setFont(font3);
        hideButton->setStyleSheet(QLatin1String("border-radius:15px;\n"
"background-color: red;\n"
"max-width:30px;\n"
"max-height:30px;\n"
"min-width:30px;\n"
"min-height:30px;"));

        horizontalLayout->addWidget(hideButton);

        raiseButton = new QPushButton(centralwidget);
        raiseButton->setObjectName(QStringLiteral("raiseButton"));
        QFont font4;
        font4.setFamily(QStringLiteral("Square Things"));
        font4.setPointSize(12);
        raiseButton->setFont(font4);
        raiseButton->setStyleSheet(QLatin1String("border-radius:15px;\n"
"background-color: red;\n"
"max-width:30px;\n"
"max-height:30px;\n"
"min-width:30px;\n"
"min-height:30px;"));

        horizontalLayout->addWidget(raiseButton);

        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setFont(font3);
        quitButton->setStyleSheet(QLatin1String("border-radius:15px;\n"
"background-color: red;\n"
"max-width:30px;\n"
"max-height:30px;\n"
"min-width:30px;\n"
"min-height:30px;"));

        horizontalLayout->addWidget(quitButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 0, 6, 2, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 0, 1, 1, 1);

        chooseButton = new QPushButton(centralwidget);
        chooseButton->setObjectName(QStringLiteral("chooseButton"));
        QFont font5;
        font5.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font5.setPointSize(10);
        chooseButton->setFont(font5);
        chooseButton->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(chooseButton, 6, 6, 1, 1);

        Home->setCentralWidget(centralwidget);

        retranslateUi(Home);
        QObject::connect(quitButton, SIGNAL(clicked()), Home, SLOT(close()));
        QObject::connect(hideButton, SIGNAL(clicked()), Home, SLOT(showMinimized()));

        QMetaObject::connectSlotsByName(Home);
    } // setupUi

    void retranslateUi(QMainWindow *Home)
    {
        Home->setWindowTitle(QApplication::translate("Home", "MainWindow", 0));
        label->setText(QApplication::translate("Home", "Connected Friends", 0));
        label_2->setText(QString());
        username->setText(QString());
        lol->setText(QApplication::translate("Home", "LOL", 0));
        hideButton->setText(QApplication::translate("Home", "-", 0));
        raiseButton->setText(QApplication::translate("Home", "A", 0));
        quitButton->setText(QApplication::translate("Home", "X", 0));
        chooseButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Home: public Ui_Home {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_H
