#ifndef __NON_RECURSIVE_BINARY_SEARCH_TREE_HPP__
#define __NON_RECURSIVE_BINARY_SEARCH_TREE_HPP__

#ifndef NO_DEBUG
#define DEBUG( out )    \
    std::cout << "Location: " << __FUNCTION__ << "; Line: " << __LINE__ << std::endl; \
    std::cout << out << std::endl;
#else
#define DEBUG( out ) ;
#endif /* NO_DEBUG */

#include <memory>
#include <functional>
#include <cstdlib>
#include <ostream>
#include <iostream>
#include <cassert>
#include <vector>
// #include "helpers/ptr_wrapper.hpp"

namespace bst
{

//----------------------------------------------------------------------------//
// Definitions                                                                //
//----------------------------------------------------------------------------//

// TODO: Common template tree implementation
template< class ValueType/*, class Comparator = std::less< ValueType >*/ >
class NonRecursiveBSTree
{
public:
    struct Node;
    class Iterator;
    friend Iterator& Iterator::operator++ ();
    using Value = ValueType;
    using Size = std::size_t;

    ~NonRecursiveBSTree ();
    
    NonRecursiveBSTree () = default;

    NonRecursiveBSTree ( NonRecursiveBSTree const & ); // not written

    NonRecursiveBSTree ( NonRecursiveBSTree && );

    NonRecursiveBSTree& operator= ( NonRecursiveBSTree const & ); // not written

    NonRecursiveBSTree& operator= ( NonRecursiveBSTree && );

    NonRecursiveBSTree ( std::initializer_list< Value > const & ); // not written

    Iterator begin () const;

    Iterator end () const;

    Size size () const; // FIX IT

    bool empty () const;

    bool clear (); // FIX IT

    bool isEnd ( Iterator const & ) const;

    Iterator find ( Value const & ) const;

    bool insert ( Value const & );

    bool remove ( Value const & ); // CHECK IT
    
    bool replace ( Value const &, Value const & ); // CHECK IT

    Iterator successor ( Value const & ) const;

    Iterator predecessor ( Value const & ) const; // FIX IT as internalSuccessor

    Iterator min () const;

    Iterator max () const;

    std::vector< Value > getVector () const // remove soon
    {
        std::vector< Value > vec;

        /*
        for ( auto it = begin(); it != end(); ++it ) // problem here !!!!!
        {
            vec.push_back( it->value );
        }
        */

        ///*
        if ( empty() )
            return vec;

        addToVector( vec, m_root );
        //*/

        return vec;
    }

    // TODO: Some strange functions in derivated class later

/*    Size maxDepth () const;

    Value minValue () const;

    std::string toString () const;

    std::string toPostorderString () const;

    std::string getPathSum () const;

    std::string getPaths () const;

    void doubleTree ();

    bool isSame ( NonRecursiveBSTree const& ) const;

    Size countTrees () const;

    bool isBst1 () const;

    bool isBst2 () const;*/

    // TODO: implement reserve function (root become a capacity array)
    // bool reserve ( Size const& );
    // NonRecursiveBSTree ( Size const& );

private:
    using Pointer = Node *;
    // using Pointer = aldt::common::ptr_wrapper< Node >;

    Pointer m_root{ nullptr };

    static Iterator end ( Pointer );

    static Iterator min ( Pointer );

    static Iterator max ( Pointer );

    static Iterator internalFind ( Pointer, Value const & );

    static Iterator internalSuccessor ( Pointer, Value const & );

    template< class F >
    bool iterate ( F );

    void addToVector( std::vector< Value >& vec, Pointer ptr ) const
    {
        if ( !ptr )
            return;

        addToVector( vec, ptr->left );

        vec.push_back( ptr->value );

        addToVector( vec, ptr->right );
    }
};

//----------------------------------------------------------------------------//
// Public implementations                                                     //
//----------------------------------------------------------------------------//

template< class T >
struct NonRecursiveBSTree< T >::Node
{
    NonRecursiveBSTree< T >::Pointer left{ nullptr };
    NonRecursiveBSTree< T >::Pointer right{ nullptr };
    NonRecursiveBSTree< T >::Pointer parent{ nullptr };
    NonRecursiveBSTree< T >::Value value;
};

//----------------------------------------------------------------------------//

template< class T >
class NonRecursiveBSTree< T >::Iterator
{
public:
    friend class NonRecursiveBSTree< T >;

    Iterator () = default;

    Iterator ( Iterator const & it )
    {
        m_rootRef = it.m_rootRef;
        m_ptr = it.m_ptr;
    }

    Iterator (
            NonRecursiveBSTree< T >::Pointer const & root
        ,   NonRecursiveBSTree< T >::Pointer const & ptr
    )
    {
        m_rootRef = root;
        m_ptr = ptr;
    }

    Iterator operator= ( Iterator const & it )
    {
        m_rootRef = it.m_rootRef;
        m_ptr = it.m_ptr;
    }

    NonRecursiveBSTree< T >::Value operator* ()
    {
        return m_ptr->value;
    }

    bool operator== ( Iterator const & right ) const
    {
        if ( m_rootRef != right.m_rootRef )
            return false;

        return m_ptr == right.m_ptr;
    }

    bool operator!= ( Iterator const & right ) const
    {
        if ( m_rootRef != right.m_rootRef )
            return false;
            
        return m_ptr != right.m_ptr;
    }

    Iterator& operator++ ()
    {
        if ( !m_ptr )
            return *this;
        
        m_ptr = NonRecursiveBSTree< T >::internalSuccessor( m_rootRef, m_ptr->value ).m_ptr;

        return *this;
    }
    
private:
    NonRecursiveBSTree< T >::Pointer m_ptr{ nullptr };
    NonRecursiveBSTree< T >::Pointer m_rootRef{ nullptr };

    NonRecursiveBSTree< T >::Pointer operator-> ()
    {
        return m_ptr;
    }
};

//----------------------------------------------------------------------------//

template< class T >
NonRecursiveBSTree< T >::~NonRecursiveBSTree ()
{
    clear();
}

//----------------------------------------------------------------------------//

template< class T >
NonRecursiveBSTree< T >::NonRecursiveBSTree ( NonRecursiveBSTree const & tree )
{
    // TODO
}

//----------------------------------------------------------------------------//

template< class T >
NonRecursiveBSTree< T >::NonRecursiveBSTree ( NonRecursiveBSTree && tree )
{
    m_root = tree.m_root;
    tree.m_root = nullptr;
}

//----------------------------------------------------------------------------//

template< class T >
NonRecursiveBSTree< T >& NonRecursiveBSTree< T >::operator= (
    NonRecursiveBSTree const& tree
)
{
    ~NonRecursiveBSTree();

    // TODO

    return *this;
}

//----------------------------------------------------------------------------//

template< class T >
NonRecursiveBSTree< T >& NonRecursiveBSTree< T >::operator= (
    NonRecursiveBSTree && tree
)
{
    ~NonRecursiveBSTree();

    m_root = tree.m_root;
    tree.m_root = nullptr;

    return *this;
}

//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Iterator NonRecursiveBSTree< T >::begin () const
{
    return min();
}

//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Iterator NonRecursiveBSTree< T >::end () const
{
    return end( m_root );
}

//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Size NonRecursiveBSTree< T >::size () const
{
    Size counter = 0;

    for ( auto it = begin(); it != end(); ++it )
        ++counter;

    return counter;
}

//----------------------------------------------------------------------------//

template< class T >
bool NonRecursiveBSTree< T >::empty () const
{
    return !m_root;
}

//----------------------------------------------------------------------------//

template< class T >
bool NonRecursiveBSTree< T >::clear ()
{
    if ( empty() )
        return false;

    /*Pointer ptr = m_root;
    int i = 0;

    while ( ptr )
    {
        if ( ptr->left )
        {
            ptr = ptr->left;
        }
        else if ( ptr->right )
        {
            ptr = ptr->right;
        }
        else if ( !ptr->left && !ptr->right )
        {
            Pointer tmp = ptr;

            if ( ptr->parent )
            {
                if ( ptr == ptr->parent->left )
                    ptr->parent->left = nullptr;
                else
                    ptr->parent->right = nullptr;
            
                ptr = ptr->parent;
            }

            delete tmp;
            ptr = m_root;
        }
    }*/

    m_root = nullptr;

    return true;
}

//----------------------------------------------------------------------------//

template< class T >
bool NonRecursiveBSTree< T >::isEnd ( Iterator const & it ) const
{
    return it == end();
}

//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Iterator NonRecursiveBSTree< T >::find (
    Value const & value
) const
{
    return internalFind( m_root, value );
}

//----------------------------------------------------------------------------//

template< class T >
bool NonRecursiveBSTree< T >::insert ( Value const & value )
{
    if ( empty() )
    {
        m_root = new Node();
        m_root->value = value;
        return true;
    }

    Pointer ptr = m_root;

    while ( ptr )
    {
        // left sub-tree
        if ( value < ptr->value )
        {
            if ( ptr->left )
            {
                ptr = ptr->left;
            }
            else
            {
                ptr->left = new Node();
                ptr->left->value = value;
                ptr->left->parent = ptr;
                return false;
            }
        }
        // right sub-tree
        else
        {
            if ( ptr->right )
            {
                ptr = ptr->right;
            }
            else
            {
                ptr->right = new Node();
                ptr->right->value = value;
                ptr->right->parent = ptr;
                return true;
            }
        }
    }

    return true;
}

//----------------------------------------------------------------------------//

template< class T >
bool NonRecursiveBSTree< T >::remove ( Value const & value )
{
    auto it = find( value );

    if ( isEnd( it ) )
        return false;

    if ( !it->left && !it->right )
    {
        delete it.m_ptr;
        return true;
    }

    Pointer tmp;
    Pointer ptr;
    bool flag = false;

    if ( it.m_ptr == it->parent->left )
    {
        ptr = it->right;
        tmp = it->left;
        it->parent->left = ptr;
        flag = true;
    }
    else
    {
        ptr = it->left;
        tmp = it->right;
        it->parent->right = ptr;
    }

    ptr->parent = it->parent;
    it->left = nullptr;
    it->right = nullptr;
    it->parent = nullptr;
    delete it.m_ptr;

    if ( flag )
    {
        while ( ptr->left )
            ptr = ptr->left;

        ptr->left = tmp;
    }
    else
    {
        while ( ptr->right )
            ptr = ptr->right;

        ptr->right = tmp;
    }

    tmp->parent = ptr;

    return true;
}

//----------------------------------------------------------------------------//

template< class T >
bool NonRecursiveBSTree< T >::replace (
        Value const & fromValue
    ,   Value const & toValue
)
{
    auto it = find( fromValue );

    if ( isEnd( it ) )
        return false;

    it->value = toValue;

    return true;
}

//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Iterator NonRecursiveBSTree< T >::successor (
    Value const & value
) const
{
    return internalSuccessor( m_root, value );
}

//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Iterator NonRecursiveBSTree< T >::predecessor (
    Value const & value
) const
{
    auto it = find( value );

    if ( isEnd( it ) )
        return end();

    if ( isEnd( it->left ) )
        return Iterator( m_root, it->parent );

    Pointer ptr = it->left;

    while ( ptr->right )
    {
        ptr = ptr->right;
    }

    assert( ptr );
    return Iterator( m_root, ptr );
}

//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Iterator NonRecursiveBSTree< T >::min () const
{
    return min( m_root );
}

//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Iterator NonRecursiveBSTree< T >::max () const
{
    return max( m_root );
}

//----------------------------------------------------------------------------//
// Private implementations                                                    //
//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Iterator
NonRecursiveBSTree< T >::end ( Pointer root )
{
    return Iterator( root, nullptr );
}

//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Iterator
NonRecursiveBSTree< T >::min ( Pointer root )
{
    if ( !root )
        return end( root );

    Pointer ptr = root;

    while ( ptr->left )
    {
        ptr = ptr->left;
    }

    return Iterator( root, ptr );
}

//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Iterator
NonRecursiveBSTree< T >::max ( Pointer root )
{
    if ( !root )
        return end( root );

    Pointer ptr = root;

    while ( ptr->right )
    {
        ptr = ptr->right;
    }

    return Iterator( root, ptr );
}

//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Iterator
NonRecursiveBSTree< T >::internalFind (
    Pointer root, Value const & value
)
{
    Pointer ptr = root;

    while ( ptr )
    {
        if ( value < ptr->value )
        {
            ptr = ptr->left;
        }
        else if ( ptr->value < value )
        {
            ptr = ptr->right;
        }
        else
            return Iterator( root, ptr );
    }

    return end( root );
}

//----------------------------------------------------------------------------//

template< class T >
typename NonRecursiveBSTree< T >::Iterator
NonRecursiveBSTree< T >::internalSuccessor (
    Pointer root, Value const & value
)
{
DEBUG( "Before internalFind" );
    auto it = internalFind( root, value );
DEBUG( "After internalFind and before check of end, it->value = " << it->value );

    if ( it == end( root ) )
        return end( root );

DEBUG( "After check of end and before check of max" );
    if ( it == max( root ) )
        return end( root );

    Pointer ptr;

DEBUG( "After check of max and before condition" );
    if ( it->parent )
    {
DEBUG( "Parent is NOT nullptr" );
        if ( it->parent->left == it.m_ptr )
        {
DEBUG( "Left of parent is same value" );
            if ( !it->right )
                return Iterator( root, it->parent );

            ptr = it->right;
            while ( ptr->left )
            {
                ptr = ptr->left;
            }
        }
        else
        {
            ptr = it->parent;
DEBUG( "Right of parent is same value, ptr = " << ptr->value );

            while ( ptr->parent )
            {
                //DEBUG( "in loop ptr->value = " << ptr->value );
                if ( ptr->parent->left == ptr )
                {
                    DEBUG( "in left condition of loop" );
                    return Iterator( root, ptr->parent );
                }
                else
                {
                    ptr = ptr->parent;
                }
            }
        }
    }
    else
    {
DEBUG( "Parent is nullptr" );
        ptr = it->right;

        while ( ptr->left )
        {
            ptr = ptr->left;
        }
    }

    assert( ptr );
DEBUG( "After assert and before return" );
    return Iterator( root, ptr );
}

//----------------------------------------------------------------------------//

template< class T >
template< class F >
bool NonRecursiveBSTree< T >::iterate ( F f )
{
    return true;
}

} // namespace bst

template< class T >
std::ostream& operator<< (
        std::ostream & os
    ,   bst::NonRecursiveBSTree< T > const & tree
)
{
    for ( auto const it : tree )
        os << it << ' ';

    return os;
}

#endif /* __NON_RECURSIVE_BINARY_SEARCH_TREE_HPP__ */