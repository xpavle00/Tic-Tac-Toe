/********************************************************************************
** Form generated from reading UI file 'launcher.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAUNCHER_H
#define UI_LAUNCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTestClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QSpinBox *gameSize;
    QGroupBox *groupBox;
    QRadioButton *firstPlayer;
    QRadioButton *firstCPU;
    QRadioButton *pvp;
    QLabel *label;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTestClass)
    {
        if (QTestClass->objectName().isEmpty())
            QTestClass->setObjectName(QStringLiteral("QTestClass"));
        QTestClass->resize(242, 200);
        centralWidget = new QWidget(QTestClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 3, 0, 1, 1);

        gameSize = new QSpinBox(centralWidget);
        gameSize->setObjectName(QStringLiteral("gameSize"));
        gameSize->setMinimum(3);
        gameSize->setMaximum(50);

        gridLayout->addWidget(gameSize, 1, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        firstPlayer = new QRadioButton(groupBox);
        firstPlayer->setObjectName(QStringLiteral("firstPlayer"));
        firstPlayer->setGeometry(QRect(10, 20, 222, 17));
        firstPlayer->setChecked(true);
        firstCPU = new QRadioButton(groupBox);
        firstCPU->setObjectName(QStringLiteral("firstCPU"));
        firstCPU->setGeometry(QRect(10, 40, 222, 17));
        pvp = new QRadioButton(groupBox);
        pvp->setObjectName(QStringLiteral("pvp"));
        pvp->setGeometry(QRect(10, 60, 222, 17));

        gridLayout->addWidget(groupBox, 2, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(16777215, 10));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        QTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QTestClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QTestClass->setStatusBar(statusBar);

        retranslateUi(QTestClass);

        QMetaObject::connectSlotsByName(QTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTestClass)
    {
        QTestClass->setWindowTitle(QApplication::translate("QTestClass", "Tic Tac Toe", 0));
        pushButton->setText(QApplication::translate("QTestClass", "Play!", 0));
        groupBox->setTitle(QApplication::translate("QTestClass", "Mode:", 0));
        firstPlayer->setText(QApplication::translate("QTestClass", "Player first", 0));
        firstCPU->setText(QApplication::translate("QTestClass", "CPU first", 0));
        pvp->setText(QApplication::translate("QTestClass", "Player vs Player", 0));
        label->setText(QApplication::translate("QTestClass", "Game Size:", 0));
    } // retranslateUi

};

namespace Ui {
    class QTestClass: public Ui_QTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAUNCHER_H
