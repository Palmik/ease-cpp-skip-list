#ifndef EASE_SKIP_LIST_STANDARD_CONTAINER_SET
#define EASE_SKIP_LIST_STANDARD_CONTAINER_SET

#include <stdexcept>

#include "base.hpp"
#include "../../skip_list.hpp"

namespace ease { namespace data { namespace skip_list {

template < typename K
         , typename C = std::less<const K>
         , typename A = std::allocator<K>
         >
class set : public standard_container_unique<skip_list<skip_list_traits_set<K, C, A> > >
{
private:
    typedef skip_list<skip_list_traits_set<K, C, A> > type_skip_list; 
    typedef standard_container_unique<type_skip_list> type_base;
    typedef set<K, C, A> type_this;
    
    typedef typename type_base::type_key type_key;

    typedef typename type_base::type_iterator type_iterator;
    typedef typename type_base::type_const_iterator type_const_iterator;

    typedef typename type_base::type_key_comparator type_key_comparator;
    typedef typename type_base::type_value_allocator type_value_allocator; 

public:
    STANDARD_CONTAINER_TYPEDEFS__
   
    set
      ( type_key_comparator const& a = type_key_comparator()
      , type_value_allocator const& c = type_value_allocator()
      ) : type_base(a, c)
    {
    }
    
    template <typename IT>
    set
      ( IT b
      , IT e
      , type_key_comparator const& a = type_key_comparator()
      , type_value_allocator const& c = type_value_allocator()
      ) : type_base(a, c)
    {
        for (IT it = b; it != e; ++it)
        {
            insert(*it);
        }
    }

    set(type_this const& other) : type_base(other) 
    {
    }
};

template < typename K
         , typename C = std::less<const K>
         , typename A = std::allocator<K>
         >
class multiset : public standard_container_multi<skip_list<skip_list_traits_set<K, C, A> > >
{
private:
    typedef skip_list<skip_list_traits_set<K, C, A> > type_skip_list; 
    typedef standard_container_multi<type_skip_list> type_base;
    typedef multiset<K, C, A> type_this;
    
    typedef typename type_base::type_key type_key;

    typedef typename type_base::type_iterator type_iterator;
    typedef typename type_base::type_const_iterator type_const_iterator;

    typedef typename type_base::type_key_comparator type_key_comparator;
    typedef typename type_base::type_value_allocator type_value_allocator; 

public:
    STANDARD_CONTAINER_TYPEDEFS__

    multiset
      ( type_key_comparator const& a = type_key_comparator()
      , type_value_allocator const& c = type_value_allocator()
      ) : type_base(a, c)
    {
    }
    
    template <typename IT>
    multiset
      ( IT b
      , IT e
      , type_key_comparator const& a = type_key_comparator()
      , type_value_allocator const& c = type_value_allocator()
      ) : type_base(a, c)
    {
        for (IT it = b; it != e; ++it)
        {
            insert(*it);
        }
    }

    multiset(type_this const& other) : type_base(other) 
    {
    }
};

} // namespace skip_list
} // namespace data
} // namespace ease

#endif // EASE_SKIP_LIST_STANDARD_CONTAINER_SET

