#include <string>
#include <iterator>

#include "router.h"
#include "trie.h"

using namespace std;

HttpRouterConfiguration& HttpRouterConfiguration::get(const string& pattern, const HttpHandler& handler) {
    return *this;
}
