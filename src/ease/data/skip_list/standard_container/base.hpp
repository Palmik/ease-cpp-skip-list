#ifndef EASE_SKIP_LIST_STANDARD_CONTAINER
#define EASE_SKIP_LIST_STANDARD_CONTAINER

#include "../../skip_list.hpp"

namespace ease { namespace data { namespace skip_list {

template <typename D>
class standard_container
{
public:
    typedef D type_skip_list;
    typedef standard_container<type_skip_list> type_this;

    typedef typename type_skip_list::type_iterator type_iterator;
    typedef typename type_skip_list::type_const_iterator type_const_iterator;
    typedef typename type_skip_list::type_reverse_iterator type_reverse_iterator;
    typedef typename type_skip_list::type_const_reverse_iterator type_const_reverse_iterator;

    typedef typename type_skip_list::type_size type_size;
    typedef typename type_skip_list::type_value type_value;
    typedef typename type_skip_list::type_key type_key;

    typedef typename type_skip_list::type_key_comparator type_key_comparator;
    typedef typename type_skip_list::type_value_allocator type_value_allocator; 

    // CONSTRUCTORS

    standard_container
      ( type_key_comparator const& a = type_key_comparator()
      , type_value_allocator const& c = type_value_allocator()
      ) : data_m(a, c)
    {
    }

    standard_container(type_this const& other) : data_m(other.data_m)
    {
    }

public:
    //template <typename IT>
    //standard_container
    //  ( IT beg
    //  , IT end
    //  , type_skip_list::type_key_comparator const& a = type_skip_list::type_key_comparator()
    //  , type_skip_list::type_value_allocator const& c = type_skip_list::type_value_allocator()
    //  )
    
    // ITERATORS
    type_iterator begin() { return data_m.begin(); }
    type_const_iterator begin() const { return data_m.begin(); }
    type_const_iterator cbegin() const { return data_m.cbegin(); }

    type_iterator end() { return data_m.end(); }
    type_const_iterator end() const { return data_m.end(); }
    type_const_iterator cend() const { return data_m.cend(); }

    type_reverse_iterator rbegin() { return data_m.rbegin(); }
    type_const_reverse_iterator rbegin() const { return data_m.rbegin(); }
    type_const_reverse_iterator crbegin() const { return data_m.crbegin(); }

    type_reverse_iterator rend() { return data_m.rend(); }
    type_const_reverse_iterator rend() const { return data_m.rend(); }
    type_const_reverse_iterator crend() const { return data_m.crend(); }

    // CAPACITY
    bool empty() const { return data_m.empty(); }
    type_size size() const { return data_m.size(); }
    type_size max_size() const { return data_m.max_size(); }

    // MODIFIERS
    void clear() { data_m.clear(); }
    
    type_iterator erase(type_const_iterator pos) { return data_m.erase(pos); } 
    type_iterator erase(type_const_iterator b, type_const_iterator e)
    {
        return data_m.erase(b, e).first;
    }
    // -- SWAP

    // LOOKUPS
    type_size count(type_key const& k) const { return data_m.count(k); }
    
    type_iterator find(type_key const& k) { return data_m.find(k); }
    type_const_iterator find(type_key const& k) const { return data_m.find(k); }
    
    type_iterator lower_bound(type_key const& k) { return data_m.lower_bound(k); }
    type_const_iterator lower_bound(type_key const& k) const { return data_m.lower_bound(k); }

    type_iterator upper_bound(type_key const& k) { return data_m.upper_bound(k); }
    type_const_iterator upper_bound(type_key const& k) const { return data_m.upper_bound(k); }

    std::pair<type_const_iterator, type_const_iterator>
    equal_range(type_key const& k) const
    {
        return std::make_pair(data_m.lower_bound(k), data_m.upper_bound(k));
    }

    std::pair<type_iterator, type_iterator>
    equal_range(type_key const& k)
    {
        return std::make_pair(data_m.lower_bound(k), data_m.upper_bound(k));
    }

    // -- AT_RANK

    void print_levels()
    {
        data_m.print_levels();
    }

protected:
    type_skip_list data_m;
};

template <typename D>
class standard_container_unique : public standard_container<D>
{
public:
    typedef D type_skip_list;
    typedef standard_container_unique<type_skip_list> type_this;
    typedef standard_container<D> type_base;

    typedef typename type_base::type_iterator type_iterator;
    typedef typename type_base::type_const_iterator type_const_iterator;
    typedef typename type_base::type_reverse_iterator type_reverse_iterator;
    typedef typename type_base::type_const_reverse_iterator type_const_reverse_iterator;

    typedef typename type_base::type_size type_size;
    typedef typename type_base::type_value type_value;
    typedef typename type_base::type_key type_key;

    typedef typename type_base::type_key_comparator type_key_comparator;
    typedef typename type_base::type_value_allocator type_value_allocator; 

    standard_container_unique
      ( type_key_comparator const& a = type_key_comparator()
      , type_value_allocator const& c = type_value_allocator()
      ) : type_base(a, c)
    {
    }
    
    standard_container_unique(type_this const& other) : type_base(other) 
    {
    }
    
    template <typename IT>
    standard_container_unique
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

    std::pair<type_iterator, bool> insert(type_value const& v)
    {
        return standard_container<D>::data_m.insert_unique(v);
    }

    using type_base::erase;
    type_size erase(type_key const& k)
    {
        return standard_container<D>::data_m.erase_unique(k).second;
    }
};

template <typename D>
class standard_container_multi : public standard_container<D>
{
public:
    typedef D type_skip_list;
    typedef standard_container_multi<type_skip_list> type_this;
    typedef standard_container<D> type_base;

    typedef typename type_base::type_iterator type_iterator;
    typedef typename type_base::type_const_iterator type_const_iterator;
    typedef typename type_base::type_reverse_iterator type_reverse_iterator;
    typedef typename type_base::type_const_reverse_iterator type_const_reverse_iterator;

    typedef typename type_base::type_size type_size;
    typedef typename type_base::type_value type_value;
    typedef typename type_base::type_key type_key;

    typedef typename type_base::type_key_comparator type_key_comparator;
    typedef typename type_base::type_value_allocator type_value_allocator; 

    standard_container_multi
      ( type_key_comparator const& a = type_key_comparator()
      , type_value_allocator const& c = type_value_allocator()
      ) : type_base(a, c)
    {
    }
    
    standard_container_multi(type_this const& other) : type_base(other) 
    {
    }
    
    template <typename IT>
    standard_container_multi
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

    type_iterator insert(type_value const& v)
    {
        return standard_container<D>::data_m.insert(v);
    }

    using type_base::erase;
    type_size erase(type_key const& k)
    {
        return standard_container<D>::data_m.erase(k).second;
    }
};

// TRAITS
template < typename K
         , typename E
         , typename C = std::less<const K>
         , typename A = std::allocator<K>
         , u8 LEVEL_MAX = 32
         , u8 LEVEL_PRO_INVERSE = 4
         >
struct skip_list_traits_map :
    public skip_list_traits_base<K, std::pair<K, E>, C, A, LEVEL_MAX, LEVEL_PRO_INVERSE>
{
    typedef K type_key;
    typedef std::pair<const K, E> type_value;

    typedef C type_key_comparator;
    typedef A type_value_allocator;

    static type_key const& key(type_value const& x)
    {
        return x.first;
    }
};

template < typename K
         , typename C = std::less<const K>
         , typename A = std::allocator<K>
         , u8 LEVEL_MAX = 32
         , u8 LEVEL_PRO_INVERSE = 4
         >
struct skip_list_traits_set : public skip_list_traits_base<K, K, C, A, LEVEL_MAX, LEVEL_PRO_INVERSE>
{
    typedef K type_key;
    typedef K type_value;

    typedef C type_key_comparator;
    typedef A type_value_allocator;

    static type_key const& key(type_value const& x)
    {
        return x;
    }
};

#define STANDARD_CONTAINER_TYPEDEFS__ \
  typedef typename type_skip_list::type_iterator iterator; \
  typedef typename type_skip_list::type_const_iterator const_iterator; \
  typedef typename type_skip_list::type_reverse_iterator reverse_iterator; \
  typedef typename type_skip_list::type_const_reverse_iterator const_reverse_iterator; \
  typedef typename type_skip_list::type_value_allocator allocator_type; \
  typedef typename type_skip_list::type_key_comparator key_compare; \
  typedef typename type_skip_list::type_value value_type; \
  typedef typename type_skip_list::type_key key_type; \
  typedef typename type_skip_list::type_size size_type; \
  typedef typename type_skip_list::type_value& reference; \
  typedef typename type_skip_list::type_value const& const_reference; \
  typedef typename type_skip_list::type_value* pointer; \
  typedef typename type_skip_list::type_value const* const_pointer;

} // namespace skip_list
} // namespace data
} // namespace ease

#endif

