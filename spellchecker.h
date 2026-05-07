#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

#include <QString>
#include <QHash>
#include <QVector>


struct TrieNode {
    QHash<QChar, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

TrieNode* createNode();
void insertWord(TrieNode* root, const QString& word, int freq = 0);
bool checkWord(TrieNode* root, const QString& word);
bool loadDictionaryFromFile(TrieNode* root, const QString& filename);

bool loadBigrams(const QString& filename);
int levenshteinDistance(const QString& s1, const QString& s2);
void findSuggestions(TrieNode* node, QString currentWord, const QString& targetWord, QVector<QString>& results);
void sortSuggestionsByContext(QVector<QString>& suggestions, const QString& prevWord, const QString& targetWord);

void freeDictionary(TrieNode* root);

#endif