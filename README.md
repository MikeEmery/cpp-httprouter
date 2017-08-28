Work in progress HTTP router based on a trie data structure, inspired by Express' handling of routes.

# Building

Make sure you have cmake.

1. mkdir build
1. cmake ..
1. cmake --build .
1. ctest -VV

# Features

- [x] Basic Path Parsing
- [ ] Http Request Adapter
- [ ] Http Response Adapter
- [ ] Nested router support
