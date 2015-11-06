/********************************************************************************
** Form generated from reading UI file 'calling.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALLING_H
#define UI_CALLING_H

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

class Ui_calling
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
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *hangupButton;
    QSpacerItem *horizontalSpacer_8;

    void setupUi(QMainWindow *calling)
    {
        if (calling->objectName().isEmpty())
            calling->setObjectName(QStringLiteral("calling"));
        calling->resize(800, 600);
        calling->setStyleSheet(QLatin1String("border-width:2px;\n"
"border-radius:50px;\n"
"max-width:2000px;\n"
"max-height:2000px;\n"
"min-width:100px;\n"
"min-height:100px;"));
        centralwidget = new QWidget(calling);
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

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        hangupButton = new QPushButton(centralwidget);
        hangupButton->setObjectName(QStringLiteral("hangupButton"));

        horizontalLayout_2->addWidget(hangupButton);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);


        gridLayout->addLayout(horizontalLayout_2, 4, 0, 1, 3);

        calling->setCentralWidget(centralwidget);

        retranslateUi(calling);
        QObject::connect(hideButton, SIGNAL(clicked()), calling, SLOT(showMinimized()));

        QMetaObject::connectSlotsByName(calling);
    } // setupUi

    void retranslateUi(QMainWindow *calling)
    {
        calling->setWindowTitle(QApplication::translate("calling", "MainWindow", 0));
        hideButton->setText(QApplication::translate("calling", "-", 0));
        raiseButton->setText(QApplication::translate("calling", "A", 0));
        quitButton->setText(QApplication::translate("calling", "X", 0));
        name->setText(QString());
        hangupButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class calling: public Ui_calling {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALLING_H
