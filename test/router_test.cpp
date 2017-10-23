#include "router.h"

#include "gtest/gtest.h"

TEST(get, path_match) {
    HttpRouterConfiguration config;

    config.get("/:blah/foo/:blah2", [&](const HttpRequest& req) {
        ASSERT_TRUE(req.hasPathParam("blah"));
        ASSERT_EQ(req.getPathParam("blah"), "somevar1");
        ASSERT_TRUE(req.hasPathParam("blah2"));
        ASSERT_EQ(req.getPathParam("blah2"), "somevar2");
    });

    const HttpRouter router = config.finalize();
    router.handle(HttpMethod::GET, "/somevar1/foo/somevar2");
}