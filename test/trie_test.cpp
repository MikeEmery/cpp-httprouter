#include "trie.h"

#include "gtest/gtest.h"

TEST(trie, nothing_matches) {
    Trie t(":", "*");
    t.insert("zoidberg", tokenizeUriPath);
    EXPECT_FALSE(t.contains("farnsworth").isContained);
}

TEST(trie, contain_after_insert) {
    Trie t(":", "*");
    t.insert("zoidberg", tokenizeUriPath);
    EXPECT_TRUE(t.contains("zoidberg").isContained);
}

TEST(trie, partial_contain) {
    Trie t(":", "*");
    t.insert("zoidberg", tokenizeUriPath);
    EXPECT_TRUE(t.contains("zoid").isContained);
}

TEST(trie, superstring_not_contains) {
    Trie t(":", "*");
    t.insert("zoidberg", tokenizeUriPath);
    EXPECT_FALSE(t.contains("zoidbergo").isContained);
}

TEST(trie, path_param) {
    Trie t(":", "*");
    t.insert("/foo/:name/blah", tokenizeUriPath);
    TrieContainsResult result = t.contains("/foo/zoidberg/blah");
    ASSERT_TRUE(result.isContained);
    EXPECT_EQ(result.pathParams.count("name"), 1u);
}

TEST(trie, multi_path_param) {
    Trie t(":", "*");
    t.insert("/foo/:name/blah/:professor", tokenizeUriPath);
    TrieContainsResult result = t.contains("/foo/zoidberg/blah/farnsworth");

    ASSERT_TRUE(result.isContained);
    ASSERT_EQ(result.pathParams.count("name"), 1u);
    EXPECT_EQ(result.pathParams["name"], "zoidberg");
    ASSERT_EQ(result.pathParams.count("professor"), 1u);
    EXPECT_EQ(result.pathParams["professor"], "farnsworth");
}