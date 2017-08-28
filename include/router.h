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
    const HeaderMap headers;
    const QueryParams queryParams;
    const PathParams pathParams;
    const std::string contentBody;
    HttpRequest(const HeaderMap& inHeaders, const QueryParams& inQuery, const PathParams& inPath, const std::string& inContent):
        headers(inHeaders), queryParams(inQuery), pathParams(inPath), contentBody(inContent) {}
};

typedef std::function<void(const HttpRequest&)> HttpHandler;

class HttpRouter {
public:
    void handle(const HttpRequest& req);
};

class HttpRouterConfiguration {
public:
    HttpRouterConfiguration& get(const std::string& pattern, const HttpHandler& handler);
    HttpRouter finalize();
};
