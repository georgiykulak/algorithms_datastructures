#include <gtest_helper.hpp>

#include <non_recursive_bstree.hpp>

TEST( Basic, Basic )
{
    bst::NonRecursiveBSTree< double > obj1;
    EXPECT_EQ( obj1.empty(), true );
    EXPECT_EQ( obj1.size(), 0 );
    EXPECT_EQ( obj1.min(), obj1.end() );
    EXPECT_EQ( obj1.isEnd( obj1.max() ), true );

    obj1.insert( 1.35 );
    obj1.insert( 0.21 );
    obj1.insert( 2.5 );
    
    EXPECT_EQ( obj1.empty(), false );
    EXPECT_EQ( obj1.size(), 3 );
    EXPECT_EQ( *( obj1.min() ), 0.21 );
    EXPECT_EQ( *( obj1.max() ), 2.5 );
    EXPECT_EQ( *( obj1.successor( 0.21 ) ), 1.35 );
    EXPECT_EQ( *( obj1.successor( 1.35 ) ), 2.5 );
    EXPECT_EQ( obj1.successor( 2.5 ), obj1.end() );
    EXPECT_EQ( obj1.begin(), obj1.min() );

    std::ostringstream os;
    os << obj1;

    EXPECT_EQ( os.str(), "0.21 1.35 2.5" );
}

TESTBENCH();