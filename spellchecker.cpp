#include "spellchecker.h"
#include <QFile>
#include <QTextStream>
#include <QtMath>
#include <QRegularExpression>
#include <QHash>

using namespace std;

TrieNode* createNode() {
    return new TrieNode();
}


void freeDictionary(TrieNode* root) {
    if (!root) return;

    QHashIterator<QChar, TrieNode*> i(root->children);
    while (i.hasNext()) {
        i.next();
        freeDictionary(i.value());
    }
    delete root;
}


bool loadDictionaryFromFile(TrieNode* root, const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream in(&file);

    QStringList validShortWords = {
        "a", "i", "am", "an", "as", "at", "be", "by", "do", "go", "he", "hi",
        "if", "in", "is", "it", "me", "my", "no", "of", "oh", "on", "or",
        "ox", "so", "to", "up", "us", "we", "я", "в", "у", "з", "і", "й", "о", "а", "ж", "б", "чи", "це", "ти",
        "ми", "ви", "он", "до", "по", "за", "на", "об", "от", "та", "не", "ні"
    };


    while (!in.atEnd()) {
        QString word = in.readLine().trimmed();

        if (word.length() <= 2 && !validShortWords.contains(word)) {
            continue;
        }

        if (word.length() > 2 && !word.contains(QRegularExpression("[aeiouyаеєиіїоуюя]"))) {
            continue;
        }

        insertWord(root, word);
    }
    file.close();
    return true;
}


void insertWord(TrieNode* root, const QString& word, int freq) {
    TrieNode* current = root;
    for (QChar c : word.toLower()) {
        if (!current->children.contains(c)) {
            current->children[c] = new TrieNode();
        }
        current = current->children[c];
    }
    current->isEndOfWord = true;
}


bool checkWord(TrieNode* root, const QString& word) {
    TrieNode* current = root;
    for (QChar c : word.toLower()) {
        if (!current->children.contains(c)) return false;
        current = current->children[c];
    }
    return current->isEndOfWord;
}

QHash<QString, int> bigramFreqs;

bool loadBigrams(const QString& filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        if (parts.size() >= 3) {
            QString bigram = parts[0].toLower() + " " + parts[1].toLower();
            int count = parts[2].toInt();
            bigramFreqs[bigram] = count;
        }
    }
    file.close();
    return true;
}

int getBigramFrequency(const QString& word1, const QString& word2) {
    if (word1.isEmpty() || word2.isEmpty()) return 0;
    QString bigram = word1.toLower() + " " + word2.toLower();
    return bigramFreqs.value(bigram, 0);
}

int levenshteinDistance(const QString& s1, const QString& s2) {
    int len1 = s1.length();
    int len2 = s2.length();
    QVector<QVector<int>> d(len1 + 1, QVector<int>(len2 + 1));

    for (int i = 0; i <= len1; ++i) d[i][0] = i;
    for (int j = 0; j <= len2; ++j) d[0][j] = j;

    for (int i = 1; i <= len1; ++i) {
        for (int j = 1; j <= len2; ++j) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;
            d[i][j] = std::min({ d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost });
        }
    }
    return d[len1][len2];
}

void sortSuggestionsByContext(QVector<QString>& suggestions, const QString& prevWord, const QString& targetWord) {
    if (suggestions.isEmpty()) return;

    std::sort(suggestions.begin(), suggestions.end(), [&prevWord, &targetWord](const QString& a, const QString& b) {

        int distA = levenshteinDistance(a, targetWord);
        int distB = levenshteinDistance(b, targetWord);
        if (distA != distB) return distA < distB;

        if (!prevWord.isEmpty()) {
            int countA = getBigramFrequency(prevWord, a);
            int countB = getBigramFrequency(prevWord, b);

            if (countA != countB) return countA > countB;
        }

        return a.length() < b.length();
    });
}

void findSuggestions(TrieNode* node, QString currentWord, const QString& targetWord, QVector<QString>& results) {
    if (!node) return;

    if (currentWord.length() > targetWord.length() + 2) return;

    if (currentWord.length() >= 2) {
        int len = currentWord.length();
        QString targetPrefix = targetWord.left(len);

        if (levenshteinDistance(currentWord, targetPrefix) > 2) {
            return;
        }
    }

    if (node->isEndOfWord) {
        int dist = levenshteinDistance(currentWord, targetWord);
        int maxDist = (targetWord.length() <= 4) ? 1 : 2;
        if (dist > 0 && dist <= maxDist) {
            results.append(currentWord);
        }
    }

    QHashIterator<QChar, TrieNode*> i(node->children);
    while (i.hasNext()) {
        i.next();
        findSuggestions(i.value(), currentWord + i.key(), targetWord, results);
    }
}