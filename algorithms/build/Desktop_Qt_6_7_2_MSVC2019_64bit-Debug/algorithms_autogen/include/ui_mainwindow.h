/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *startBtn;
    QLabel *label;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QSpinBox *sb_01;
    QLabel *label_3;
    QSpinBox *sb_02;
    QLabel *label_2;
    QSpinBox *sb_14;
    QLabel *label_5;
    QSpinBox *sb_15;
    QPushButton *addWeightsBtn;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QSpinBox *sb_23;
    QLabel *label_7;
    QSpinBox *sb_24;
    QLabel *label_8;
    QSpinBox *sb_35;
    QLabel *label_9;
    QSpinBox *sb_45;
    QPushButton *stopBtn;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(755, 609);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(260, 100, 481, 365));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QGraphicsView(verticalLayoutWidget);
        graphicsView->setObjectName("graphicsView");

        verticalLayout->addWidget(graphicsView);

        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(260, 50, 481, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        startBtn = new QPushButton(centralwidget);
        startBtn->setObjectName("startBtn");
        startBtn->setGeometry(QRect(340, 490, 141, 61));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(40, 80, 191, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Myanmar Text")});
        font.setBold(true);
        font.setItalic(true);
        label->setFont(font);
        label->setFrameShape(QFrame::Shape::NoFrame);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label->setWordWrap(false);
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(40, 130, 91, 351));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName("label_4");
        QFont font1;
        font1.setPointSize(11);
        label_4->setFont(font1);
        label_4->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_4->setFrameShape(QFrame::Shape::NoFrame);
        label_4->setTextFormat(Qt::TextFormat::PlainText);
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_4->setMargin(4);

        verticalLayout_2->addWidget(label_4);

        sb_01 = new QSpinBox(verticalLayoutWidget_2);
        sb_01->setObjectName("sb_01");

        verticalLayout_2->addWidget(sb_01);

        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);
        label_3->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_3->setFrameShape(QFrame::Shape::NoFrame);
        label_3->setTextFormat(Qt::TextFormat::PlainText);
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_3->setMargin(4);

        verticalLayout_2->addWidget(label_3);

        sb_02 = new QSpinBox(verticalLayoutWidget_2);
        sb_02->setObjectName("sb_02");

        verticalLayout_2->addWidget(sb_02);

        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName("label_2");
        label_2->setFont(font1);
        label_2->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_2->setFrameShape(QFrame::Shape::NoFrame);
        label_2->setTextFormat(Qt::TextFormat::PlainText);
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2->setMargin(4);

        verticalLayout_2->addWidget(label_2);

        sb_14 = new QSpinBox(verticalLayoutWidget_2);
        sb_14->setObjectName("sb_14");

        verticalLayout_2->addWidget(sb_14);

        label_5 = new QLabel(verticalLayoutWidget_2);
        label_5->setObjectName("label_5");
        label_5->setFont(font1);
        label_5->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_5->setFrameShape(QFrame::Shape::NoFrame);
        label_5->setTextFormat(Qt::TextFormat::PlainText);
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_5->setMargin(4);

        verticalLayout_2->addWidget(label_5);

        sb_15 = new QSpinBox(verticalLayoutWidget_2);
        sb_15->setObjectName("sb_15");

        verticalLayout_2->addWidget(sb_15);

        addWeightsBtn = new QPushButton(centralwidget);
        addWeightsBtn->setObjectName("addWeightsBtn");
        addWeightsBtn->setGeometry(QRect(80, 500, 121, 29));
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(140, 130, 91, 351));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(verticalLayoutWidget_3);
        label_6->setObjectName("label_6");
        label_6->setFont(font1);
        label_6->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_6->setFrameShape(QFrame::Shape::NoFrame);
        label_6->setTextFormat(Qt::TextFormat::PlainText);
        label_6->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_6->setMargin(4);

        verticalLayout_3->addWidget(label_6);

        sb_23 = new QSpinBox(verticalLayoutWidget_3);
        sb_23->setObjectName("sb_23");

        verticalLayout_3->addWidget(sb_23);

        label_7 = new QLabel(verticalLayoutWidget_3);
        label_7->setObjectName("label_7");
        label_7->setFont(font1);
        label_7->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_7->setFrameShape(QFrame::Shape::NoFrame);
        label_7->setTextFormat(Qt::TextFormat::PlainText);
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_7->setMargin(4);

        verticalLayout_3->addWidget(label_7);

        sb_24 = new QSpinBox(verticalLayoutWidget_3);
        sb_24->setObjectName("sb_24");

        verticalLayout_3->addWidget(sb_24);

        label_8 = new QLabel(verticalLayoutWidget_3);
        label_8->setObjectName("label_8");
        label_8->setFont(font1);
        label_8->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_8->setFrameShape(QFrame::Shape::NoFrame);
        label_8->setTextFormat(Qt::TextFormat::PlainText);
        label_8->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_8->setMargin(4);

        verticalLayout_3->addWidget(label_8);

        sb_35 = new QSpinBox(verticalLayoutWidget_3);
        sb_35->setObjectName("sb_35");

        verticalLayout_3->addWidget(sb_35);

        label_9 = new QLabel(verticalLayoutWidget_3);
        label_9->setObjectName("label_9");
        label_9->setFont(font1);
        label_9->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label_9->setFrameShape(QFrame::Shape::NoFrame);
        label_9->setTextFormat(Qt::TextFormat::PlainText);
        label_9->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_9->setMargin(4);

        verticalLayout_3->addWidget(label_9);

        sb_45 = new QSpinBox(verticalLayoutWidget_3);
        sb_45->setObjectName("sb_45");

        verticalLayout_3->addWidget(sb_45);

        stopBtn = new QPushButton(centralwidget);
        stopBtn->setObjectName("stopBtn");
        stopBtn->setGeometry(QRect(500, 490, 141, 61));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 755, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Algorithms", nullptr));
        startBtn->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\200\321\202", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\262\320\265\321\201\320\260", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "0->1", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "0->2", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "1->4", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "1->5", nullptr));
        addWeightsBtn->setText(QCoreApplication::translate("MainWindow", "\320\223\320\276\321\202\320\276\320\262\320\276", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "2->3", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "2->4", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "3->5", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "4->5", nullptr));
        stopBtn->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\276\320\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
