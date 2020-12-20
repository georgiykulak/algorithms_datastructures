#include "gtest/gtest.h"

#include <gtest_helper.hpp>

#include <non_recursive_bstree.hpp>

TEST( Basic, Baisc )
{
    bst::NonRecursiveBSTree< double > obj1;
    assert( obj1.empty() );
    assert( obj1.size() == 0 );
    assert( obj1.min() == obj1.end() );
    assert( obj1.isEnd( obj1.max() ) );
    std::cout << "obj1.getVector().size() = '" << obj1.getVector().size() << "'\n";

    obj1.insert( 1.35 );
    obj1.insert( 0.21 );
    obj1.insert( 2.5 );
    assert( !obj1.empty() );
    assert( obj1.size() == 3 );
    assert( *( obj1.min() ) == 0.21 );
    assert( *( obj1.max() ) == 2.5 );
    assert( *( obj1.successor( 0.21 ) ) == 1.35 );
    assert( *( obj1.successor( 1.35 ) ) == 2.5 );
    assert( obj1.successor( 2.5 ) == obj1.end() );
    assert( obj1.begin() == obj1.min() );
    auto const vec = obj1.getVector();
    std::cout << "vec.size() = '" << vec.size() << "'\n";
    
    std::cout << "Vector output:\n";
    if ( vec.size() )
        for ( auto v : vec )
            std::cout << v << " ";
    std::cout << std::endl;
    
    std::cout << "Iterational output:\n";
    std::cout << "'" << obj1 << "'" <<  std::endl;

    std::cout << std::endl;
}

TESTBENCH();