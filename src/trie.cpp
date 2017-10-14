#include "trie.h"
#include <iostream>

using namespace std;

TrieNode* nextForToken(TrieNode* curNode, const string token) {
    if (curNode->children.find(token) == curNode->children.end()) {
        curNode->children[token] = make_unique<TrieNode>(token);
    }
    return curNode->children[token].get();
}

void Trie::insert(const std::string& path, const Parser parser) {
    const vector<PathToken> key = parser(path);
    TrieNode* curNode = root.get();

    for(auto i = key.begin(); i < key.end(); ++i) {
        const PathToken& current = *i;

        if (current.token == this->placeholder) {
            curNode = nextForToken(curNode, current.token);
            curNode->pathToken = current;
        }
        else if (current.token == this->wildcard) {
            curNode = nextForToken(curNode, current.token);
            curNode->pathToken = current;
            break;
        }
        else {
            curNode = nextForToken(curNode, current.token);
        }
    }
}

TrieContainsResult Trie::contains(const string& key) {
    auto result = TrieContainsResult(true);
    TrieNode* curNode = root.get();

    for(auto it = key.begin(); it < key.end(); ++it) {
        string curChar(1, *it);
        
        if (curNode->children[this->placeholder]) {
            curNode = curNode->children[this->placeholder].get();

            string paramValue = "";
            while(it != key.end()) {
                curChar = string(1, *it);
                paramValue.append(curChar);

                if (string(1, *next(it)) == curNode->pathToken.tokenStop) {
                    break;
                }
                ++it;
            }

            string& paramName = curNode->pathToken.tokenName;
            result.pathParams[paramName] = paramValue;
        }
        else if (curNode->children[this->wildcard]) {
            curNode = curNode->children[this->wildcard].get();

            string paramValue = "";
            while (it != key.end()) {
                curChar = string(1, *it);
                paramValue.append(curChar);
                ++it;
            }
            string& paramName = curNode->pathToken.tokenName;

            result.pathParams[paramName] = paramValue;
            break;
        }
        else if (curNode->children[curChar]) {
            curNode = curNode->children[curChar].get();
        }
        else {
            result.isContained = false;
            break;
        }
    }

    return result;
}