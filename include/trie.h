#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include "path.h"

struct TrieNode {
    std::unordered_map<std::string, std::shared_ptr<TrieNode>> children;
    PathToken pathToken;
    TrieNode(const std::string& token): pathToken(PathToken(token, "", "")) {}
    TrieNode(const PathToken& pathToken): pathToken(pathToken) {}
};

struct TrieContainsResult {
    bool isContained;
    std::unordered_map<std::string, std::string> pathParams;
    TrieContainsResult(bool isContained):
        isContained(isContained), pathParams(std::unordered_map<std::string, std::string>()) {}
};

typedef std::function<std::vector<PathToken>(const std::string&)> Parser;

class Trie {
private:
    const std::string placeholder;
    const std::string wildcard;
    std::unique_ptr<TrieNode> root;
public:
    Trie(const std::string& placeholder, const std::string wildcard): placeholder(placeholder), wildcard(wildcard) {
        auto originPathToken = PathToken("", "", "");
        root = std::make_unique<TrieNode>(originPathToken);
    };
    void insert(const std::string& str, Parser parser);
    TrieContainsResult contains(const std::string& key);
};
