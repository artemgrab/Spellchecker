/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QLabel *label_2;
    QPlainTextEdit *TextEdit;
    QPushButton *clearButton;
    QLabel *charCountLabel;
    QLabel *label;
    QLabel *label_3;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *LoadFileButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(887, 520);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"font-family: Inter;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(21, 106, 845, 251));
        frame->setStyleSheet(QString::fromUtf8("border-radius: 20px;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(37, 19, 221, 41));
        label_2->setStyleSheet(QString::fromUtf8("color: black;\n"
"font-size: 18px;\n"
"\n"
"font-weight: bold;"));
        TextEdit = new QPlainTextEdit(frame);
        TextEdit->setObjectName("TextEdit");
        TextEdit->setGeometry(QRect(33, 70, 781, 131));
        TextEdit->setStyleSheet(QString::fromUtf8("QPlainTextEdit {\n"
"    font-size: 16px;\n"
"	color: #black;\n"
"}\n"
"\n"
"\n"
"QScrollBar:vertical {\n"
"    border: none;\n"
"    background: transparent;\n"
"    width: 10px;\n"
"    margin: 0px 0px 0px 0px;\n"
"}\n"
"QScrollBar::handle:vertical {\n"
"    background: #BDBDBD;\n"
"    min-height: 30px;\n"
"    border-radius: 5px;\n"
"}\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #9E9E9E;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:pressed {\n"
"    background: #4C75FF; \n"
"}\n"
"\n"
"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"    background: none;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"    background: none;\n"
"}"));
        clearButton = new QPushButton(frame);
        clearButton->setObjectName("clearButton");
        clearButton->setGeometry(QRect(786, 20, 41, 41));
        clearButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        clearButton->setStyleSheet(QString::fromUtf8("QPushButton#clearButton {\n"
"    background-color: transparent; \n"
"    border-radius: 15px;        \n"
"    color: #888888;              \n"
"    font-size: 18px;\n"
"    border: none;\n"
"}\n"
"QPushButton#clearButton:hover {\n"
"    background-color: #f0f0f0;       \n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/img/Replay.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        clearButton->setIcon(icon);
        clearButton->setIconSize(QSize(500, 500));
        charCountLabel = new QLabel(frame);
        charCountLabel->setObjectName("charCountLabel");
        charCountLabel->setGeometry(QRect(723, 215, 101, 20));
        charCountLabel->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        charCountLabel->setStyleSheet(QString::fromUtf8("color: gray; font-size: 11px;"));
        charCountLabel->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        label_2->raise();
        TextEdit->raise();
        charCountLabel->raise();
        clearButton->raise();
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(21, 35, 221, 41));
        label->setStyleSheet(QString::fromUtf8("color: black;\n"
"font-size: 30px;\n"
"font-weight: bold;"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(96, 377, 41, 41));
        label_3->setStyleSheet(QString::fromUtf8("color: black;\n"
"font-size: 15px;\n"
"\n"
"font-weight: bold;"));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(148, 384, 261, 31));
        comboBox->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"    border: 1px solid #cccccc;\n"
"    border-radius: 10px;\n"
"    padding: 5px 15px;\n"
"    background-color: white;\n"
"    font-size: 15px;\n"
"    min-width: 150px;\n"
"	color: black;\n"
"	font-weight: bold;\n"
"}\n"
"QComboBox::drop-down {\n"
"    border: none; /* \320\227\320\260\320\261\320\270\321\200\320\260\321\224\320\274\320\276 \320\275\320\265\320\263\320\260\321\200\320\275\321\203 \321\201\321\202\320\260\320\275\320\264\320\260\321\200\321\202\320\275\321\203 \321\201\321\202\321\200\321\226\320\273\320\276\321\207\320\272\321\203 */\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    background-color: white;         /* \320\221\321\226\320\273\320\270\320\271 \321\204\320\276\320\275 \321\201\320\277\320\270\321\201\320\272\321\203 */\n"
"    border: 1px solid #e0e0e0;       /* \320\233\320\265\320\263\320\272\320\260 \321\201\321\226\321\200\320\260 \321\200\320\260\320\274\320\276\321\207\320\272\320\260 \320\275\320\260\320\262\320\272\320\276\320\273\320\276 \320\274\320"
                        "\265\320\275\321\216 */\n"
"    border-radius: 8px;              /* \320\227\320\260\320\276\320\272\321\200\321\203\320\263\320\273\320\265\320\275\321\226 \320\272\321\203\321\202\320\270 \320\274\320\265\320\275\321\216 */\n"
"    outline: none;                   /* \320\237\320\240\320\230\320\221\320\230\320\240\320\220\320\204\320\234\320\236 \320\277\321\203\320\275\320\272\321\202\320\270\321\200\320\275\321\203 \321\200\320\260\320\274\320\272\321\203 \321\204\320\276\320\272\321\203\321\201\320\260 (\320\264\321\203\320\266\320\265 \320\262\320\260\320\266\320\273\320\270\320\262\320\276!) */\n"
"    padding: 4px;                    /* \320\222\320\275\321\203\321\202\321\200\321\226\321\210\320\275\321\226 \320\262\321\226\320\264\321\201\321\202\321\203\320\277\320\270 \320\262\321\226\320\264 \320\272\321\200\320\260\321\227\320\262 \321\200\320\260\320\274\320\272\320\270 */\n"
"    \n"
"    /* \320\232\320\276\320\273\321\226\321\200 \320\277\321\200\320\270 \320\275\320\260\320\262\320\265\320\264"
                        "\320\265\320\275\320\275\321\226 (\321\201\320\262\321\226\321\202\320\273\320\276-\321\201\320\270\320\275\321\226\320\271, \320\277\321\226\320\264 \321\202\320\262\320\276\321\216 \320\272\320\275\320\276\320\277\320\272\321\203) */\n"
"    selection-background-color: #f0f4ff; \n"
"    selection-color: #4C75FF;        /* \320\232\320\276\320\273\321\226\321\200 \321\202\320\265\320\272\321\201\321\202\321\203 \320\277\321\200\320\270 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\275\321\226 \321\201\321\202\320\260\321\224 \321\201\320\270\320\275\321\226\320\274 */\n"
"}\n"
"\n"
"/* 3. \320\235\320\260\320\273\320\260\321\210\321\202\321\203\320\262\320\260\320\275\320\275\321\217 \320\272\320\276\320\266\320\275\320\276\320\263\320\276 \320\276\320\272\321\200\320\265\320\274\320\276\320\263\320\276 \321\200\321\217\320\264\320\272\320\260 (\"\320\220\320\275\320\263\320\273\321\226\320\271\321\201\321\214\320\272\320\260\", \"\320\243\320\272\321\200\320\260\321\227\320\275\321\201\321\214"
                        "\320\272\320\260\") */\n"
"QComboBox::item {\n"
"    height: 35px;                    /* \320\240\320\276\320\261\320\270\320\274\320\276 \320\277\321\203\320\275\320\272\321\202\320\270 \320\262\320\270\321\211\320\270\320\274\320\270, \321\211\320\276\320\261 \320\261\321\203\320\273\320\276 \320\267\321\200\321\203\321\207\320\275\320\276 \320\272\320\273\321\226\320\272\320\260\321\202\320\270 */\n"
"    border-radius: 20px;              /* \320\227\320\260\320\276\320\272\321\200\321\203\320\263\320\273\321\216\321\224\320\274\320\276 \321\201\320\260\320\274\320\265 \320\262\320\270\320\264\321\226\320\273\320\265\320\275\320\275\321\217 \320\277\321\203\320\275\320\272\321\202\321\203 */\n"
"    padding-left: 10px;              /* \320\222\321\226\320\264\321\201\321\202\321\203\320\277 \321\202\320\265\320\272\321\201\321\202\321\203 \320\262\321\226\320\264 \320\273\321\226\320\262\320\276\320\263\320\276 \320\272\321\200\320\260\321\216 */\n"
"    color: #333333;   \n"
"	pointer: cursor;             "
                        "  /* \320\242\320\265\320\274\320\275\320\276-\321\201\321\226\321\200\320\270\320\271 \321\202\320\265\320\272\321\201\321\202 \320\267\320\260 \320\267\320\260\320\274\320\276\320\262\321\207\321\203\320\262\320\260\320\275\320\275\321\217\320\274 */\n"
"}\n"
""));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(430, 378, 415, 41));
        pushButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: #4C75FF; \n"
"    color: white;\n"
"    border-radius: 16.5px;\n"
"    padding: 10px 30px; \n"
"    font-size: 15px;\n"
"    font-weight: bold;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3b5bdb; \n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2b45a2; \n"
"}"));
        LoadFileButton = new QPushButton(centralwidget);
        LoadFileButton->setObjectName("LoadFileButton");
        LoadFileButton->setGeometry(QRect(40, 380, 41, 41));
        LoadFileButton->setCursor(QCursor(Qt::CursorShape::PointingHandCursor));
        LoadFileButton->setStyleSheet(QString::fromUtf8("QPushButton#LoadFileButton {\n"
"    background-color: transparent; \n"
"    border-radius: 15px;        \n"
"    color: #888888;              \n"
"    font-size: 18px;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton#LoadFileButton:hover {\n"
"    background-color: #f0f0f0;           \n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/img/img/Upload.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        LoadFileButton->setIcon(icon1);
        LoadFileButton->setIconSize(QSize(500, 500));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "SpellChecker", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\321\226\320\272\321\203\320\262\320\260\320\275\320\275\321\217 \320\262\320\262\320\276\320\264\321\203...", nullptr));
        TextEdit->setPlainText(QString());
        TextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\321\226\321\202\321\214 \321\202\320\265\320\272\321\201\321\202", nullptr));
        clearButton->setText(QString());
        charCountLabel->setText(QCoreApplication::translate("MainWindow", "0 / 1000", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Spell Checker", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\234\320\276\320\262\320\260", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "\320\220\320\275\320\263\320\273\321\226\320\271\321\201\321\214\320\272\320\260", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "\320\243\320\272\321\200\320\260\321\227\320\275\321\201\321\214\320\272\320\260", nullptr));

        pushButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\262\321\226\321\200\320\270\321\202\320\270 \321\202\320\265\320\272\321\201\321\202", nullptr));
        LoadFileButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
