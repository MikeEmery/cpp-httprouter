#include <algorithm>

#include "path.h"


const std::vector<PathToken> tokenizeUriPath(const std::string& path) {
    auto result = std::vector<PathToken>();

    for(auto it = path.cbegin(); it < path.cend(); ++it) {
        if (*it == ':') {
            ++it;
            std::string tokenName = "";
            while(*it != '/' && it < path.cend()) {
                tokenName.append(1, *it);
                ++it;
            }
            result.push_back(PathToken(":", tokenName, "/"));
            result.push_back(PathToken("/", "", ""));
        }
        else if (*it == '*') {
            auto tokenName = std::string(next(it), path.cend());
            result.push_back(PathToken("*", tokenName, ""));
            break;
        }
        else {
            result.push_back(PathToken(std::string(1, *it), "", ""));
        }
    }

    return result;
}