#pragma once

#include <string>
#include <vector>

/*
Not happy with this, there are a lot of ways to represent invalid states.
*/
class PathToken {
public:
    std::string token;
    std::string tokenName;
    std::string tokenStop;
    PathToken(const std::string& token, const std::string& tokenName, const std::string& tokenStop):
        token(token), tokenName(tokenName), tokenStop(tokenStop) {}
};

const std::vector<PathToken> tokenizeUriPath(const std::string& path);