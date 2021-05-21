cmake_minimum_required(VERSION 3.10)
project(server)
set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(common)

string(TIMESTAMP BUILD_TIME %Y%m%d%H%M%S)
get_git_branch(GIT_BRANCH)
get_git_hash(GIT_HASH)

ADD_SUBDIRECTORY(db_server)
