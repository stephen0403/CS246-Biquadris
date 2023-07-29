#include <iostream>;
#include <string>;
#include <utility>;
#include "trie.h"
using namespace std;

const int NUM_CHARS = 26;

TrieNode::TrieNode() {
    size = 1;
    words = 0;
    isWord = false;
    letters = new TrieNode* [NUM_CHARS];
    for (int i = 0; i < NUM_CHARS; ++i) {
        letters[i] = nullptr;
    }
}

TrieNode::~TrieNode() {
    for (int i = 0; i < NUM_CHARS; ++i) {
        delete letters[i];
    }
    delete[] letters;
}

TrieNode::TrieNode(const TrieNode &other) {
    size = other.size;
    words = other.words;
    isWord = other.isWord;
    letters = new TrieNode* [NUM_CHARS];
    for (int i = 0; i < NUM_CHARS; ++i) {
        if (other.letters[i]) {
            letters[i] = new TrieNode {*other.letters[i]};
        } else {
            letters[i] = nullptr;
        }
    }
} 

TrieNode::TrieNode(TrieNode &&other){
    size = other.size;
    words = other.words;
    isWord = other.isWord;

    letters = new TrieNode* [NUM_CHARS];
    for (int i = 0; i < NUM_CHARS; ++i) {
        letters[i] = other.letters[i];
        other.letters[i] = nullptr;
    }
} 

TrieNode &TrieNode::operator=(const TrieNode &other) {
    if (this == &other) return *this;
    TrieNode **tmp = letters;
    letters = new TrieNode* [NUM_CHARS];
    for (int i = 0; i < NUM_CHARS; ++i) {
        if (other.letters[i]) {
            letters[i] = new TrieNode(*other.letters[i]);
        } else {
            letters[i] = nullptr;
        }
    }
    size = other.size;
    words = other.words;
    isWord = other.isWord;
    for (int i = 0; i < NUM_CHARS; ++i) {
        delete tmp[i];
    }
    delete[] tmp;
    return *this;
}

TrieNode &TrieNode::operator=(TrieNode &&other) {
    if (this == &other) return *this;
    size = other.size;
    words = other.words;
    isWord = other.isWord;
    for (int i = 0; i < NUM_CHARS; ++i) {
        delete letters[i];
    }
    delete[] letters;
    letters = new TrieNode* [NUM_CHARS];
    for (int i = 0; i < NUM_CHARS; ++i) {
        letters[i] = other.letters[i];
        other.letters[i] = nullptr;
    }
    return *this;
}

void TrieNode::updateSize() {
    int sum = 1;
    for (int i = 0; i < NUM_CHARS; ++i) {
        if (letters[i]) {
            letters[i]->updateSize();
            sum += letters[i]->size;
        }
        if (size != sum) {
            size = sum;
        }
    }
}

void TrieNode::updateWords() {
    int sum = 0;
    if (isWord) {
        words = 1;
    }
    for (int i = 0; i < NUM_CHARS; ++i) {
        if (letters[i]) {
            letters[i]->updateWords();
            sum += letters[i]->words;
        }
        if (words != sum) {
            words = sum;
        }
    }
}

void TrieNode::insert(const string &word) {
    TrieNode *currentNode = this;
    int length = word.length();
    for (int i = 0; i < length; ++i) {
        int index = word[i] - 'a';
        if (!(currentNode->letters[index])) {
            currentNode->letters[index] = new TrieNode;
        }
        currentNode = currentNode->letters[index];
    }
    currentNode->isWord = true;
    updateWords();
}

void TrieNode::remove(const string &word) {
    TrieNode *currentNode = this;
    int length = word.length();
    for (int i = 0; i < length; ++i) {
        int index = word[i] - 'a';
        if (!(currentNode->letters[index])) {
            return;
        }
        currentNode = currentNode->letters[index];
    }
    currentNode->isWord = false;
    updateWords();
}

std::vector<std::string> TrieNode::addWords(const string &word, int &wordCount) const {
    std::vector<std::string> autocompletions;
    const TrieNode *currentNode = this;
    int length = word.length();

    for (int i = 0; i < length; ++i) {
        int index = word[i] - 'a';
        if (!(currentNode->letters[index])) {
            return autocompletions;
        }
        currentNode = currentNode->letters[index];
    }

    if (currentNode->isWord) {
        autocompletions.emplace_back(word);
        ++wordCount;
    }

    for (int i = 0; i < NUM_CHARS; ++i) {
        if (currentNode->letters[i]) {
            std::vector<std::string> a1 = addWords(word + char('a' + i), wordCount);
            autocompletions.insert(autocompletions.end(), a1.begin(), a1.end());
        }
    }
    return autocompletions;
}

std::vector<std::string> TrieNode::find(const string &word) const {
    int wordCount = 0;
    return addWords(word, wordCount);
}

int TrieNode::getSize() const {
    return size;
}
