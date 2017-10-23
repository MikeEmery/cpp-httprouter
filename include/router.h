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

enum HttpMethod {
    GET
};

class HttpRequest {
private:
    const QueryParams queryParams;
    const PathParams pathParams;
public:
    HttpRequest(const QueryParams& inQuery, const PathParams& inPath): 
        queryParams(inQuery), pathParams(inPath) {}

    bool hasPathParam(const std::string& name) const {
        return pathParams.count(name) > 0u;
    }

    bool hasQueryParam(const std::string& name) const {
        return queryParams.count(name) > 0u;
    }

    const std::string getPathParam(const std::string& name) const {
        return pathParams.at(name);
    }

    const std::string getQueryParam(const std::string& name) const {
        return queryParams.at(name);
    }
};

typedef std::function<void(const HttpRequest&)> HttpHandler;

class HttpRouter {
public:
    void handle(HttpMethod httpMethod, const std::string& fullUri) const;
};

class HttpRouterConfiguration {
public:
    HttpRouterConfiguration& get(const std::string& pattern, const HttpHandler& handler);
    HttpRouter finalize();
};
