cmake_minimum_required(VERSION 2.8.8)
set(PROJECT_NAME_STR cpp-httprouter)
project(${PROJECT_NAME_STR} CXX)

find_package(Threads REQUIRED)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -Werror -std=c++17 -pthread)
endif()

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)
set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)

set(PROJECT_LIB_NAME ${PROJECT_NAME_STR}_impl)
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(${PROJECT_LIB_NAME} ${SRC_FILES})

add_subdirectory(${EXT_PROJECTS_DIR}/gtest)

enable_testing()
set(PROJECT_TEST_NAME ${PROJECT_NAME_STR}_test)
include_directories(${GTEST_INCLUDE_DIRS} ${COMMON_INCLUDES})


file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/test/*_test.cpp)
add_executable(${PROJECT_TEST_NAME} ${TEST_SRC_FILES})
add_dependencies(${PROJECT_TEST_NAME} googletest)
add_dependencies(${PROJECT_TEST_NAME} ${PROJECT_LIB_NAME})

target_link_libraries(${PROJECT_TEST_NAME}
    ${GTEST_LIBS_DIR}/libgtest.a
    ${GTEST_LIBS_DIR}/libgtest_main.a
)

target_link_libraries(${PROJECT_TEST_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_TEST_NAME} ${PROJECT_LIB_NAME})

add_test(trie ${PROJECT_TEST_NAME})