/********************************************************************************
** Form generated from reading UI file 'start.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_H
#define UI_START_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Start
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *startButton;
    QSpacerItem *spacer;
    QSpacerItem *verticalSpacer;
    QPushButton *quit;

    void setupUi(QMainWindow *Start)
    {
        if (Start->objectName().isEmpty())
            Start->setObjectName(QStringLiteral("Start"));
        Start->resize(1007, 643);
        QFont font;
        font.setFamily(QStringLiteral("BatmanForeverAlternate"));
        Start->setFont(font);
        Start->setStyleSheet(QLatin1String("border-width:2px;\n"
"border-radius:50px;\n"
"max-width:2000px;\n"
"max-height:2000px;\n"
"min-width:100px;\n"
"min-height:100px;"));
        centralWidget = new QWidget(Start);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral("background-color: grey;"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font1.setPointSize(72);
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        QFont font2;
        font2.setFamily(QStringLiteral("BatmanForeverAlternate"));
        font2.setPointSize(12);
        startButton->setFont(font2);
        startButton->setStyleSheet(QLatin1String("border-style: outset;\n"
"border-width:2px;\n"
"border-radius:50px;\n"
"border-color: red;\n"
"max-width:100px;\n"
"max-height:100px;\n"
"min-width:100px;\n"
"min-height:100px;"));

        horizontalLayout_2->addWidget(startButton);


        verticalLayout->addLayout(horizontalLayout_2);

        spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(spacer);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        quit = new QPushButton(centralWidget);
        quit->setObjectName(QStringLiteral("quit"));
        quit->setFont(font);

        verticalLayout->addWidget(quit);

        Start->setCentralWidget(centralWidget);

        retranslateUi(Start);
        QObject::connect(quit, SIGNAL(clicked()), Start, SLOT(close()));

        QMetaObject::connectSlotsByName(Start);
    } // setupUi

    void retranslateUi(QMainWindow *Start)
    {
        Start->setWindowTitle(QApplication::translate("Start", "Babel", 0));
        label->setText(QApplication::translate("Start", "BABEL", 0));
        startButton->setText(QApplication::translate("Start", "START", 0));
        quit->setText(QApplication::translate("Start", "QUIT", 0));
    } // retranslateUi

};

namespace Ui {
    class Start: public Ui_Start {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_H
