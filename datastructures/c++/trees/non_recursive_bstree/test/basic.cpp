#include <gtest_helper.hpp>

#include <non_recursive_bstree.hpp>

struct Parallelogram
{
    long double x = 0.0;
    long double y = 0.0;
    long double z = 0.0;

    Parallelogram () = default; // required

    Parallelogram ( long double x, long double y, long double z ) // optional
        :   x{ x }, y{ y }, z{ z }
    {}

    bool operator< ( Parallelogram const & s ) const // required
    {
        return volume() < s.volume();
    }
private:
    long double volume () const { return x * y * z; }
};

std::ostream& operator<< (
        std::ostream & os
    ,   Parallelogram const & p
)
{
    os << "{ x = " << p.x << ", y = " << p.y << ", z = " << p.z << " }";

    return os;
}

TEST ( Basic, Creation_and_deletion )
{

}

TEST ( Basic, Copying )
{

}

TEST ( Basic, Moveing )
{

}

TEST ( Basic, Finding )
{

}

TEST ( Basic, Iterating )
{

}

TEST ( Basic, Min )
{

}

TEST ( Basic, Max )
{

}

TEST ( Basic, Successor )
{

}

TEST ( Basic, Predecessor )
{

}

TEST ( Basic, Remove_and_replace__Float )
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

    std::ostringstream os1;
    os1 << obj1;

    EXPECT_EQ( os1.str(), "0.21 1.35 2.5" );

    obj1.remove( 1.35 );

    std::ostringstream os2;
    os2 << obj1;

    EXPECT_EQ( os2.str(), "0.21 2.5" );

    obj1.remove( 2.5 );

    std::ostringstream os3;
    os3 << obj1;

    EXPECT_EQ( os3.str(), "0.21" );
}

TEST ( Basic, Remove_and_replace__String )
{
    bst::NonRecursiveBSTree< std::string > obj1;
    EXPECT_EQ( obj1.empty(), true );
    EXPECT_EQ( obj1.size(), 0 );
    EXPECT_EQ( obj1.min(), obj1.end() );
    EXPECT_EQ( obj1.isEnd( obj1.max() ), true );

    obj1.insert( "Hello" );
    obj1.insert( "world" );
    obj1.insert( "I" );
    obj1.insert( "am" );
    obj1.insert( "Georgiy Kulak" );

    std::ostringstream os1;
    os1 << obj1;

    EXPECT_EQ( os1.str(), "Georgiy Kulak Hello I am world" );

    EXPECT_EQ( obj1.remove( "Georgiy Kulak" ), true );

    std::ostringstream os2;
    os2 << obj1;

    EXPECT_EQ( os2.str(), "Hello I am world" );

    EXPECT_EQ( obj1.remove( "I" ), true );
    EXPECT_EQ( obj1.remove( "am" ), true );

    std::ostringstream os3;
    os3 << obj1;

    EXPECT_EQ( os3.str(), "Hello world" );

    EXPECT_EQ( obj1.remove( "hello" ), false );

    std::ostringstream os4;
    os4 << obj1;

    EXPECT_EQ( os4.str(), "Hello world" );
}

TEST ( Basic, Remove_and_replace__Structure )
{
    bst::NonRecursiveBSTree< Parallelogram > obj1;
    EXPECT_EQ( obj1.empty(), true );
    EXPECT_EQ( obj1.size(), 0 );
    EXPECT_EQ( obj1.min(), obj1.end() );
    EXPECT_EQ( obj1.isEnd( obj1.max() ), true );

    obj1.insert( Parallelogram{ 1.2, 3.5, 8.9 } );
    obj1.insert( Parallelogram{ 10.1, 2.385, 3.4 } );
    obj1.insert( Parallelogram{ 0.235, 6.12, 5.55 } );

    std::ostringstream os1;
    os1 << obj1;

    EXPECT_EQ( os1.str(),
    "{ x = 0.235, y = 6.12, z = 5.55 } { x = 1.2, y = 3.5, z = 8.9 } { x = 10.1, y = 2.385, z = 3.4 }" );

    EXPECT_EQ( obj1.remove( Parallelogram{ 10.1, 2.385, 3.4 } ), true );

    std::ostringstream os2;
    os2 << obj1;

    EXPECT_EQ( os2.str(), "{ x = 0.235, y = 6.12, z = 5.55 } { x = 1.2, y = 3.5, z = 8.9 }" );

    EXPECT_EQ( obj1.remove( Parallelogram{ 1.2, 3.5, 9 } ), false );

    std::ostringstream os3;
    os3 << obj1;

    EXPECT_EQ( os3.str(), "{ x = 0.235, y = 6.12, z = 5.55 } { x = 1.2, y = 3.5, z = 8.9 }" );
}

TESTBENCH();