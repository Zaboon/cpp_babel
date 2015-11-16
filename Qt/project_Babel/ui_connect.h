/********************************************************************************
** Form generated from reading UI file 'connect.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECT_H
#define UI_CONNECT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Connect
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_27;
    QPushButton *ok;
    QSpacerItem *horizontalSpacer_28;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_23;
    QLabel *label_2;
    QLineEdit *ipAddress;
    QSpacerItem *horizontalSpacer_24;
    QHBoxLayout *horizontalLayout_9;
    QSpacerItem *horizontalSpacer_19;
    QSpacerItem *horizontalSpacer_22;
    QLabel *label;
    QLineEdit *Username;
    QSpacerItem *horizontalSpacer_21;
    QSpacerItem *horizontalSpacer_20;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_16;
    QSpacerItem *horizontalSpacer_15;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *hideButton;
    QPushButton *raiseButton;
    QPushButton *quitButton;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_17;
    QLabel *connexion;
    QSpacerItem *horizontalSpacer_18;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_25;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_26;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *Connect)
    {
        if (Connect->objectName().isEmpty())
            Connect->setObjectName(QStringLiteral("Connect"));
        Connect->resize(1007, 644);
        Connect->setStyleSheet(QLatin1String("border-width:2px;\n"
"border-radius:50px;\n"
"max-width:2000px;\n"
"max-height:2000px;\n"
"min-width:100px;\n"
"min-height:100px;"));
        centralwidget = new QWidget(Connect);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setStyleSheet(QStringLiteral("background-color : grey;"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QStringLiteral("horizontalLayout_12"));
        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_27);

        ok = new QPushButton(centralwidget);
        ok->setObjectName(QStringLiteral("ok"));
        QFont font;
        font.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font.setPointSize(12);
        ok->setFont(font);
        ok->setStyleSheet(QLatin1String("border-style: outset;\n"
"border-width:2px;\n"
"border-radius:50px;\n"
"border-color: red;\n"
"max-width:100px;\n"
"max-height:100px;\n"
"min-width:100px;\n"
"min-height:100px;"));

        horizontalLayout_12->addWidget(ok);

        horizontalSpacer_28 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_28);


        gridLayout->addLayout(horizontalLayout_12, 5, 1, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_23);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font1.setPointSize(10);
        label_2->setFont(font1);

        horizontalLayout_10->addWidget(label_2);

        ipAddress = new QLineEdit(centralwidget);
        ipAddress->setObjectName(QStringLiteral("ipAddress"));
        ipAddress->setFocusPolicy(Qt::StrongFocus);
        ipAddress->setAcceptDrops(false);
        ipAddress->setStyleSheet(QLatin1String("background-color : #AEAFAF;\n"
"border-style: outset;\n"
"border-radius: 15px;\n"
"min-height : 30px;\n"
"min-width : 150px;\n"
"max-height : 30px;\n"
"max-width : 150px;"));

        horizontalLayout_10->addWidget(ipAddress);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_24);


        gridLayout->addLayout(horizontalLayout_10, 4, 1, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_19);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_22);

        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        horizontalLayout_9->addWidget(label);

        Username = new QLineEdit(centralwidget);
        Username->setObjectName(QStringLiteral("Username"));
        Username->setFocusPolicy(Qt::StrongFocus);
        Username->setStyleSheet(QLatin1String("background-color : #AEAFAF;\n"
"border-style: outset;\n"
"border-radius: 15px;\n"
"min-height : 30px;\n"
"min-width : 150px;\n"
"max-height : 30px;\n"
"max-width : 150px;\n"
""));

        horizontalLayout_9->addWidget(Username);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_21);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_20);


        gridLayout->addLayout(horizontalLayout_9, 3, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_16);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_15);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_14);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_13);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_12);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_11);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_10);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_8);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        hideButton = new QPushButton(centralwidget);
        hideButton->setObjectName(QStringLiteral("hideButton"));
        QFont font2;
        font2.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font2.setPointSize(18);
        hideButton->setFont(font2);
        hideButton->setStyleSheet(QLatin1String("border-radius:15px;\n"
"background-color: red;\n"
"max-width:30px;\n"
"max-height:30px;\n"
"min-width:30px;\n"
"min-height:30px;"));

        horizontalLayout->addWidget(hideButton);

        raiseButton = new QPushButton(centralwidget);
        raiseButton->setObjectName(QStringLiteral("raiseButton"));
        QFont font3;
        font3.setFamily(QStringLiteral("Square Things"));
        font3.setPointSize(12);
        raiseButton->setFont(font3);
        raiseButton->setStyleSheet(QLatin1String("border-radius:15px;\n"
"background-color: red;\n"
"max-width:30px;\n"
"max-height:30px;\n"
"min-width:30px;\n"
"min-height:30px;"));

        horizontalLayout->addWidget(raiseButton);

        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setFont(font2);
        quitButton->setStyleSheet(QLatin1String("border-radius:15px;\n"
"background-color: red;\n"
"max-width:30px;\n"
"max-height:30px;\n"
"min-width:30px;\n"
"min-height:30px;"));

        horizontalLayout->addWidget(quitButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_17);

        connexion = new QLabel(centralwidget);
        connexion->setObjectName(QStringLiteral("connexion"));
        QFont font4;
        font4.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font4.setPointSize(28);
        connexion->setFont(font4);

        horizontalLayout_2->addWidget(connexion);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_18);


        gridLayout->addLayout(horizontalLayout_2, 2, 1, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_25);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setStyleSheet(QStringLiteral(""));

        horizontalLayout_11->addWidget(label_3);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_26);


        gridLayout->addLayout(horizontalLayout_11, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 1, 1, 1);

        Connect->setCentralWidget(centralwidget);

        retranslateUi(Connect);
        QObject::connect(quitButton, SIGNAL(clicked()), Connect, SLOT(close()));
        QObject::connect(hideButton, SIGNAL(clicked()), Connect, SLOT(showMinimized()));

        QMetaObject::connectSlotsByName(Connect);
    } // setupUi

    void retranslateUi(QMainWindow *Connect)
    {
        Connect->setWindowTitle(QApplication::translate("Connect", "Babel", 0));
        ok->setText(QApplication::translate("Connect", "OK", 0));
        label_2->setText(QApplication::translate("Connect", "IP Address:", 0));
        label->setText(QApplication::translate("Connect", "Username:", 0));
        Username->setInputMask(QString());
        hideButton->setText(QApplication::translate("Connect", "-", 0));
        raiseButton->setText(QApplication::translate("Connect", "A", 0));
        quitButton->setText(QApplication::translate("Connect", "X", 0));
        connexion->setText(QApplication::translate("Connect", "CONNEXION", 0));
        label_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Connect: public Ui_Connect {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECT_H
