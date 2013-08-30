#ifndef EASE_SKIP_LIST_STANDARD_CONTAINER_MAP
#define EASE_SKIP_LIST_STANDARD_CONTAINER_MAP

#include <stdexcept>

#include "base.hpp"
#include "../../skip_list.hpp"

namespace ease { namespace data { namespace skip_list {

template < typename K
         , typename E
         , typename C = std::less<const K>
         , typename A = std::allocator<K>
         >
class map : public standard_container_unique<skip_list<skip_list_traits_map<K, E, C, A> > >
{
private:
    typedef skip_list<skip_list_traits_map<K, E, C, A> > type_skip_list; 
    typedef standard_container_unique<type_skip_list> type_base;
    typedef map<K, E, C, A> type_this;

    typedef typename type_base::type_key type_key;
    typedef E type_element;

    typedef typename type_base::type_iterator type_iterator;
    typedef typename type_base::type_const_iterator type_const_iterator;

    typedef typename type_base::type_key_comparator type_key_comparator;
    typedef typename type_base::type_value_allocator type_value_allocator; 

public:
    STANDARD_CONTAINER_TYPEDEFS__
    typedef E mapped_type;

    map
      ( type_key_comparator const& a = type_key_comparator()
      , type_value_allocator const& c = type_value_allocator()
      ) : type_base(a, c)
    {
    }
    
    template <typename IT>
    map
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

    map(type_this const& other) : type_base(other) 
    {
    }
    
    type_element& operator[](type_key const& k)
    {
        return insert(std::make_pair(k, type_element())).first->second;
    } 

    type_element& at(type_key const& k)
    {
        type_iterator res = find(k);

        if (res == type_base::end())
        {
            throw std::out_of_range
              ( "data::skip_list::standard_container::map::at"
              );
        }

        return (*res).second;
    }
    
    type_element const& at(type_key const& k) const
    {
        type_const_iterator res = find(k);

        if (res == type_base::cend())
        {
            throw std::out_of_range
              ( "data::skip_list::standard_container::map::at"
              );
        }

        return (*res).second;
    }
};

template < typename K
         , typename E
         , typename C = std::less<const K>
         , typename A = std::allocator<K>
         >
class multimap : public standard_container_multi<skip_list<skip_list_traits_map<K, E, C, A> > >
{
private:
    typedef skip_list<skip_list_traits_map<K, E, C, A> > type_skip_list; 
    typedef standard_container_multi<type_skip_list> type_base;
    typedef multimap<K, E, C, A> type_this;

    typedef typename type_base::type_key type_key;
    typedef E type_element;

    typedef typename type_base::type_iterator type_iterator;
    typedef typename type_base::type_const_iterator type_const_iterator;

    typedef typename type_base::type_key_comparator type_key_comparator;
    typedef typename type_base::type_value_allocator type_value_allocator; 

public:
    STANDARD_CONTAINER_TYPEDEFS__
    typedef E mapped_type;

    multimap
      ( type_key_comparator const& a = type_key_comparator()
      , type_value_allocator const& c = type_value_allocator()
      ) : type_base(a, c)
    {
    }
    
    template <typename IT>
    multimap
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
    
    multimap(type_this const& other) : type_base(other) 
    {
    }
};

} // namespace skip_list
} // namespace data
} // namespace ease

#endif // EASE_SKIP_LIST_STANDARD_CONTAINER_MAP

