#include <iostream>
#include <string>
#include <utility>
#include "trie.h"
using namespace std;

const int NUM_CHARS = 26;

TrieNode::TrieNode() {
    size = 1;
    words = 0;
    isWord = false;
    letters = std::make_unique<std::unique_ptr<TrieNode>[]>(NUM_CHARS);
    for (int i = 0; i < NUM_CHARS; ++i) {
        letters[i] = nullptr;
    }
}

TrieNode::~TrieNode() = default;

void TrieNode::updateSize() {
    int sum = 1;
    for (int i = 0; i < NUM_CHARS; ++i) {
        if (letters[i]) {
            letters[i].get()->updateSize();
            sum += letters[i].get()->size;
        }
    }
    size = sum;
}

void TrieNode::updateWords() {
    int sum = isWord ? 1 : 0;
    for (int i = 0; i < NUM_CHARS; ++i) {
        if (letters[i]) {
            letters[i].get()->updateWords();
            sum += letters[i].get()->words;
        }
    }
    words = sum;
}

void TrieNode::insert(const std::string &word) {
    TrieNode *currentNode = this;
    int length = word.length();
    for (int i = 0; i < length; ++i) {
        int index = word[i] - 'a';
        if (!(currentNode->letters[index])) {
            currentNode->letters[index] = std::make_unique<TrieNode>();
        }
        currentNode = currentNode->letters[index].get();
    }
    currentNode->isWord = true;
    updateWords();
}

void TrieNode::remove(const std::string &word) {
    TrieNode *currentNode = this;
    int length = word.length();
    for (int i = 0; i < length; ++i) {
        int index = word[i] - 'a';
        if (!(currentNode->letters[index])) {
            return;
        }
        currentNode = currentNode->letters[index].get();
    }
    currentNode->isWord = false;
    updateWords();
}

std::vector<std::string> TrieNode::find(const std::string &word) const {
    std::vector<std::string> autocompletions;
    const TrieNode *currentNode = this;
    int length = word.length();

    for (int i = 0; i < length; ++i) {
        int index = word[i] - 'a';
        if (!(currentNode->letters[index])) {
            return autocompletions;
        }
        currentNode = currentNode->letters[index].get();
    }

    if (currentNode->isWord) {
        autocompletions.emplace_back(word);
    }

    for (int i = 0; i < NUM_CHARS; ++i) {
        if (currentNode->letters[i]) {
            std::vector<std::string> a1 = find(word + char('a' + i));
            autocompletions.insert(autocompletions.end(), a1.begin(), a1.end());
        }
    }
    return autocompletions;
}

int TrieNode::getSize() const {
    return size;
}
