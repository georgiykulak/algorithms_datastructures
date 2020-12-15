//#define NO_DEBUG

#include "src/non_recursive_bstree.hpp"
#include <cassert>

int main()
{
    bst::NonRecursiveBSTree< double > obj1;
    assert( obj1.empty() );
    assert( obj1.size() == 0 );
    assert( obj1.min() == nullptr );
    assert( obj1.max() == nullptr );
    std::cout << "obj1.getVector().size() = '" << obj1.getVector().size() << "'\n";

    obj1.insert( 1.35 );
    obj1.insert( 2.5 );
    obj1.insert( 0.21 );
    std::cout << "obj1.size() = " << obj1.size() << std::endl;
    auto vec = obj1.getVector();
    std::cout << "vec.size() = '" << vec.size() << "'\n";
    
    if ( vec.size() )
        for ( auto v : vec )
            std::cout << v << " ";
    
    std::cout << std::endl;

    return 0;
}