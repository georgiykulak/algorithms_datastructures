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
    std::cout << "obj output 1: '" << obj1 << "'\n";

    obj1.insert( 1.35 );
    obj1.insert( 2.5 );
    obj1.insert( 0.21 );
    std::cout << "obj output 2: '" << obj1 << "'\n";

    return 0;
}