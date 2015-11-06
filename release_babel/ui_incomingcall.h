/********************************************************************************
** Form generated from reading UI file 'incomingcall.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INCOMINGCALL_H
#define UI_INCOMINGCALL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_incomingCall
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *hideButton;
    QPushButton *raiseButton;
    QPushButton *quitButton;
    QSpacerItem *horizontalSpacer_4;
    QLabel *name;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *buttonLayout;
    QPushButton *hangupButton;
    QPushButton *answerButton;

    void setupUi(QMainWindow *incomingCall)
    {
        if (incomingCall->objectName().isEmpty())
            incomingCall->setObjectName(QStringLiteral("incomingCall"));
        incomingCall->resize(800, 600);
        incomingCall->setStyleSheet(QLatin1String("border-width:2px;\n"
"border-radius:50px;\n"
"max-width:2000px;\n"
"max-height:2000px;\n"
"min-width:100px;\n"
"min-height:100px;"));
        centralwidget = new QWidget(incomingCall);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setStyleSheet(QStringLiteral("background-color : black;"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(500, -1, -1, -1);
        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        hideButton = new QPushButton(centralwidget);
        hideButton->setObjectName(QStringLiteral("hideButton"));
        QFont font;
        font.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font.setPointSize(18);
        hideButton->setFont(font);
        hideButton->setStyleSheet(QLatin1String("border-radius:15px;\n"
"background-color: red;\n"
"max-width:30px;\n"
"max-height:30px;\n"
"min-width:30px;\n"
"min-height:30px;"));

        horizontalLayout->addWidget(hideButton);

        raiseButton = new QPushButton(centralwidget);
        raiseButton->setObjectName(QStringLiteral("raiseButton"));
        QFont font1;
        font1.setFamily(QStringLiteral("Square Things"));
        font1.setPointSize(12);
        raiseButton->setFont(font1);
        raiseButton->setStyleSheet(QLatin1String("border-radius:15px;\n"
"background-color: red;\n"
"max-width:30px;\n"
"max-height:30px;\n"
"min-width:30px;\n"
"min-height:30px;"));

        horizontalLayout->addWidget(raiseButton);

        quitButton = new QPushButton(centralwidget);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setFont(font);
        quitButton->setStyleSheet(QLatin1String("border-radius:15px;\n"
"background-color: red;\n"
"max-width:30px;\n"
"max-height:30px;\n"
"min-width:30px;\n"
"min-height:30px;"));

        horizontalLayout->addWidget(quitButton);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 3);

        name = new QLabel(centralwidget);
        name->setObjectName(QStringLiteral("name"));
        QFont font2;
        font2.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font2.setPointSize(16);
        name->setFont(font2);
        name->setStyleSheet(QStringLiteral("color: white;"));

        gridLayout->addWidget(name, 2, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 2, 1, 1);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setObjectName(QStringLiteral("buttonLayout"));
        hangupButton = new QPushButton(centralwidget);
        hangupButton->setObjectName(QStringLiteral("hangupButton"));

        buttonLayout->addWidget(hangupButton);

        answerButton = new QPushButton(centralwidget);
        answerButton->setObjectName(QStringLiteral("answerButton"));

        buttonLayout->addWidget(answerButton);


        gridLayout->addLayout(buttonLayout, 4, 0, 1, 3);

        incomingCall->setCentralWidget(centralwidget);

        retranslateUi(incomingCall);
        QObject::connect(hideButton, SIGNAL(clicked()), incomingCall, SLOT(showMinimized()));

        QMetaObject::connectSlotsByName(incomingCall);
    } // setupUi

    void retranslateUi(QMainWindow *incomingCall)
    {
        incomingCall->setWindowTitle(QApplication::translate("incomingCall", "MainWindow", 0));
        hideButton->setText(QApplication::translate("incomingCall", "-", 0));
        raiseButton->setText(QApplication::translate("incomingCall", "A", 0));
        quitButton->setText(QApplication::translate("incomingCall", "X", 0));
        name->setText(QString());
        hangupButton->setText(QString());
        answerButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class incomingCall: public Ui_incomingCall {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCOMINGCALL_H
