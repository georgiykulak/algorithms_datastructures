cmake_minimum_required( VERSION 3.9 )

project( algorithms_datastructures
    LANGUAGES CXX
)

set( CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/common/cmake/"
)
set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED True )
set( LIBRARY_NAME algorithms_datastructures ) 

include( gtest )