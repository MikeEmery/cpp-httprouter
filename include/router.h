#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <vector>
#include "path.h"

typedef std::unordered_map<std::string, std::string> HeaderMap;
typedef std::unordered_map<std::string, std::string> QueryParams;
typedef std::unordered_map<std::string, std::string> PathParams;
typedef std::string ContentBody;

class HttpRequest {
public:
    const QueryParams queryParams;
    const PathParams pathParams;
    HttpRequest(const QueryParams& inQuery, const PathParams& inPath): 
        queryParams(inQuery), pathParams(inPath) {}
};

typedef std::function<void(const HttpRequest&)> HttpHandler;

class HttpRouter {
public:
    void handle(const std::string& fullUri);
};

class HttpRouterConfiguration {
public:
    HttpRouterConfiguration& get(const std::string& pattern, const HttpHandler& handler);
    HttpRouter finalize();
};
