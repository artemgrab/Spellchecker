#include "mainwindow.h"
#include "spellchecker.h"
#include "ui_mainwindow.h"
#include <QTextCharFormat>
#include <QTextCursor>
#include <QRegularExpression>
#include <QGraphicsDropShadowEffect>
#include <QMenu>
#include <QAction>
#include <QEvent>
#include <algorithm>
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QAbstractItemView>

using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(this->width(), this->height());

    QTextCharFormat normalFormat;
    normalFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
    ui->TextEdit->setCurrentCharFormat(normalFormat);

    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setBlurRadius(15.2);
    shadow->setColor(QColor(205, 62, 195, 120));
    ui->comboBox->setCursor(Qt::PointingHandCursor);

    ui->comboBox->view()->viewport()->setCursor(Qt::PointingHandCursor);

    connect(ui->TextEdit, &QPlainTextEdit::textChanged, this, [=]() {
        int currentLength = ui->TextEdit->toPlainText().length();
        int maxLength = 1000;

        ui->charCountLabel->setText(QString("%1 / %2").arg(currentLength).arg(maxLength));

        if (currentLength > maxLength) {
            ui->charCountLabel->setStyleSheet("color: #D32F2F; font-size: 13px;");
            ui->pushButton->setDisabled(true);
        } else {
            ui->charCountLabel->setStyleSheet("color: black; font-size: 13px;");
            ui->pushButton->setEnabled(true);
        }
    });

    ui->frame->setGraphicsEffect(shadow);

    connect(ui->clearButton, &QPushButton::clicked, this, [=]() {
        ui->TextEdit->clear();
        ui->TextEdit->setReadOnly(false);
        ui->label_2->setText("Очікування вводу...");

        QTextCursor cursor = ui->TextEdit->textCursor();
        QTextCharFormat normalFormat;
        normalFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
        cursor.setCharFormat(normalFormat);
        ui->TextEdit->setCurrentCharFormat(normalFormat);

        ui->TextEdit->setFocus();
        ui->charCountLabel->setText("0 / 1000");
        ui->charCountLabel->setStyleSheet("color: black; font-size: 12px;");
    });

    connect(ui->LoadFileButton, &QPushButton::clicked, this, [=]() {
            QString fileName = QFileDialog::getOpenFileName(this, "Оберіть текстовий файл", "", "Текстові файли (*.txt);;Всі файли (*)");

            if (fileName.isEmpty()) return;

            QFile file(fileName);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                ui->TextEdit->setPlainText(QString::fromUtf8(file.readAll()));
                file.close();

            } else {
                QMessageBox::warning(this, "Помилка", "Не вдалося відкрити файл!");
            }
    });

    rootEn = createNode();
    rootUa = createNode();

    QString appPath = QCoreApplication::applicationDirPath();

    loadDictionaryFromFile(rootEn, appPath + "/words_en.txt");
    loadDictionaryFromFile(rootUa, appPath + "/words_ua.txt");
    loadBigrams(appPath + "/bigrams.txt");

    currentRoot = rootEn;

    on_comboBox_currentIndexChanged(ui->comboBox->currentIndex());

    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_comboBox_currentIndexChanged);
    ui->TextEdit->viewport()->installEventFilter(this);
}


MainWindow::~MainWindow()
{
    freeDictionary(rootEn);
    freeDictionary(rootUa);
    delete ui;
}


void MainWindow::on_helpButton_clicked()
{

    QString msgBoxStyle = R"(
        QLabel {
            color: #333333;
            font-size: 14px;
        }
        QPushButton {
            background-color: #E95CE0;
            color: white;
            border-radius: 6px;
            padding: 6px 20px;
            font-size: 13px;
            font-weight: bold;
            min-width: 60px;
        }
        QPushButton:hover {
            background-color: #CD3EC3;
        }
        QPushButton:pressed {
            background-color: #AC31A3;
        }
    )";

    QString helpText =
        "<h3>Інструкція користувача</h3>"
        "<p><b>1. Введення тексту:</b> Введіть текст вручну, вставте його з буфера обміну або "
        "завантажте готовий текстовий файл за допомогою кнопки "
        "<img src=':/Upload.png' width='22' height='22' align='middle'></p>"
        "<p><b>2. Перевірка:</b> Натисніть кнопку «Перевірити текст». Програма проаналізує текст:"
        "Орфографічні та граматичні (повтори, регістр) помилки підкреслюються <b><font color='red'>червоним</font></b>."
        "<p><b>3. Виправлення:</b> Натисніть <b>лівою кнопкою \"миші\"</b> на підкреслене слово. З'явиться контекстне меню з "
        "найбільш імовірними варіантами виправлення. Оберіть потрібний варіант.</p>"
        "<p><b>4. Очищення:</b> Натисніть кнопку <img src=':/Replay.png' width='18' height='20' align='middle'>, щоб зняти всі підкреслення та стерти текст.</p>";

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Довідка");
    msgBox.setText(helpText);

    msgBox.setIcon(QMessageBox::Information);

    msgBox.setStyleSheet(msgBoxStyle);


    msgBox.exec();
}

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->TextEdit->toPlainText();
    QString msgBoxStyle = R"(
        QLabel {
            color: #333333;
            font-size: 14px;
        }
        QPushButton {
            background-color: #E95CE0;
            color: white;
            border-radius: 6px;
            padding: 6px 20px;
            font-size: 13px;
            font-weight: bold;
            min-width: 60px;
        }
        QPushButton:hover {
            background-color: #CD3EC3;
        }
        QPushButton:pressed {
            background-color: #AC31A3;
        }
    )";

    if (text.trimmed().isEmpty()) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Увага");
        msgBox.setText("<b>Поле для вводу порожнє!</b>");
        msgBox.setInformativeText("Будь ласка, введіть текст для перевірки.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet(msgBoxStyle);
        msgBox.exec();
        return;
    }

    if (text.length() > 1000) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Перевищено ліміт");
        msgBox.setText("<b>Текст занадто великий!</b>");
        msgBox.setInformativeText("Будь ласка, введіть не більше 1000 символів.");
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setStyleSheet(msgBoxStyle);
        msgBox.exec();
        return;
    }

    int currentLang = ui->comboBox->currentIndex();

    if (currentLang == 0) {
        if (text.contains(QRegularExpression("[а-яА-ЯіІїЇєЄґҐ]"))) {
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Помилка мови");
            msgBox.setText("<b>Знайдено українські літери!</b>");
            msgBox.setInformativeText("Ви вибрали перевірку англійською, але в тексті є кирилиця.\nЗмініть мову словника або виправте текст.");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setStyleSheet(msgBoxStyle);
            msgBox.exec();
            return;
        }
    }
    else {
        if (text.contains(QRegularExpression("[a-zA-Z]"))) {
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Помилка мови");
            msgBox.setText("<b>Знайдено англійські літери!</b>");
            msgBox.setInformativeText("Ви вибрали перевірку українською, але в тексті є латиниця.\nЗмініть мову словника або виправте текст.");
            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setStyleSheet(msgBoxStyle);
            msgBox.exec();
            return;
        }
    }

    ui->label_2->setText("Результати перевірки:");

    ui->TextEdit->setReadOnly(true);

    QTextCursor cursor(ui->TextEdit->document());
    cursor.select(QTextCursor::Document);
    QTextCharFormat clearFormat;
    clearFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
    cursor.setCharFormat(clearFormat);
    cursor.clearSelection();
    ui->TextEdit->setTextCursor(cursor);

    QTextCharFormat errorFormat;
    errorFormat.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
    errorFormat.setUnderlineColor(Qt::red);

    QRegularExpression regex("[a-zA-Zа-яА-ЯіІїЇєЄґҐ']+");
    QRegularExpressionMatchIterator i = regex.globalMatch(text);

    QString prevWordLower = "";

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString originalWord = match.captured(0);
        QString lowerWord = originalWord.toLower();

        int startPos = match.capturedStart();
        int endPos = match.capturedEnd();

        bool isGrammarError = false;

        if (lowerWord == prevWordLower) {
            isGrammarError = true;
        }

        if (!isGrammarError && originalWord[0].isLower()) {
            if (startPos == 0) {
                isGrammarError = true;
            } else {
                for (int pos = startPos - 1; pos >= 0; --pos) {
                    if (!text[pos].isSpace()) {
                        if (text[pos] == '.' || text[pos] == '!' || text[pos] == '?') {
                            isGrammarError = true;
                        }
                        break;
                    }
                }
            }
        }

        cursor.setPosition(startPos);
        cursor.setPosition(endPos, QTextCursor::KeepAnchor);

        if (isGrammarError || !checkWord(currentRoot, lowerWord)) {
            cursor.setCharFormat(errorFormat);
        }

        prevWordLower = lowerWord;
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui->TextEdit->viewport() && event->type() == QEvent::MouseButtonRelease) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        QPoint clickPos = mouseEvent->pos();

        QTextCursor cursor = ui->TextEdit->cursorForPosition(clickPos);

        QRect cursorRect = ui->TextEdit->cursorRect(cursor);
        cursorRect.adjust(-15, -15, 15, 15);

        if (!cursorRect.contains(clickPos)) {
            return QMainWindow::eventFilter(obj, event);
        }


        if (cursor.charFormat().underlineStyle() == QTextCharFormat::SpellCheckUnderline) {
            cursor.select(QTextCursor::WordUnderCursor);
            QString originalWord = cursor.selectedText();
            QString badWord = originalWord.toLower();

            QString prevWord = "";
            QTextCursor prevCursor = cursor;
            prevCursor.setPosition(cursor.selectionStart());
            if (prevCursor.movePosition(QTextCursor::PreviousWord)) {
                prevCursor.select(QTextCursor::WordUnderCursor);
                prevWord = prevCursor.selectedText().toLower();
            }

            QVector<QString> suggestions;

            if (badWord == prevWord && !prevWord.isEmpty()) {
                suggestions.append("Видалити зайве слово");
            }

            if (!checkWord(currentRoot, badWord)) {
                QVector<QString> spellSuggestions;
                QString temp = "";
                findSuggestions(currentRoot, temp, badWord, spellSuggestions);
                sortSuggestionsByContext(spellSuggestions, prevWord, badWord);
                suggestions.append(spellSuggestions);
            }

            bool needsCapital = false;
            int startPos = cursor.selectionStart();

            QString fullText = ui->TextEdit->toPlainText();

            if (startPos == 0) {
                needsCapital = true;
            } else {
                QString textBefore = fullText.left(startPos);

                for (int i = textBefore.length() - 1; i >= 0; --i) {
                    QChar c = textBefore[i];

                    if (!c.isSpace()) {
                        if (c == '.' || c == '!' || c == '?') {
                            needsCapital = true;
                        }
                        break;
                    }
                }
            }

            if (needsCapital && originalWord[0].isLower() && checkWord(currentRoot, badWord) && badWord != prevWord) {
                QString capWord = originalWord;
                capWord[0] = capWord[0].toUpper();
                suggestions.append(capWord);
            }

            QMenu *menu = new QMenu(this);
            menu->setAttribute(Qt::WA_DeleteOnClose);
            menu->setStyleSheet(
                "QMenu { background-color: white; border: 1px solid #ccc; border-radius: 8px; padding: 5px; }"
                "QMenu::item { padding: 6px 25px 6px 20px; border-radius: 4px; color: #333; font-size: 14px; }"
                "QMenu::item:selected { background-color: #E95CE0; color: white; }"
                );

            if (suggestions.empty()) {
                menu->addAction("Немає підказок")->setEnabled(false);
            } else {
                int limit = min((int)suggestions.size(), 7);
                for (int i = 0; i < limit; ++i) {
                    QString sug = suggestions[i];

                    if ((needsCapital || (!originalWord.isEmpty() && originalWord[0].isUpper())) && sug != "[Видалити зайве слово]") {
                        sug[0] = sug[0].toUpper();
                    }

                    QAction* action = menu->addAction(sug);

                    if (i == 0) {
                        QFont f = action->font();
                        f.setBold(true);
                        action->setFont(f);
                    }

                    connect(action, &QAction::triggered, this, [=]() {
                        ui->TextEdit->setReadOnly(false);

                        QTextCursor replaceCursor = ui->TextEdit->cursorForPosition(clickPos);
                        replaceCursor.select(QTextCursor::WordUnderCursor);

                        QTextCharFormat normalFormat;
                        replaceCursor.setCharFormat(normalFormat);

                        if (sug == "Видалити зайве слово") {
                            replaceCursor.removeSelectedText();
                        } else {
                            replaceCursor.insertText(sug);
                        }

                        ui->TextEdit->setReadOnly(true);
                    });
                }
            }

            QPoint globalPos = ui->TextEdit->mapToGlobal(clickPos);
            globalPos.ry() += 15;
            menu->popup(globalPos);

            return true;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}


void MainWindow::on_comboBox_currentIndexChanged(int index) {
    if (index == 0) {
        currentRoot = rootEn;
    } else {
        currentRoot = rootUa;
    }

    ui->TextEdit->clear();
    QTextCharFormat normalFormat;
    normalFormat.setUnderlineStyle(QTextCharFormat::NoUnderline);
    ui->TextEdit->setCurrentCharFormat(normalFormat);
}