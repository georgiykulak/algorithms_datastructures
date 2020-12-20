cmake_minimum_required( VERSION 3.9 )

project( non_recursive_bstree
    LANGUAGES CXX
)

set( CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../../../common/cmake/"
)

include( gtest_helper )

add_library( ds_trees_nr_bst OBJECT src/non_recursive_bstree.hpp )

target_include_directories( ds_trees_nr_bst PUBLIC ${CMAKE_SOURCE_DIR}/src )
target_include_directories( ds_trees_nr_bst PUBLIC ${CMAKE_SOURCE_DIR}/../../../../common/c++/ )

add_gtest( ds_trees_nr_bst basic test/basic.cpp )