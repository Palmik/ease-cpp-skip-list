#ifndef EASE_DATA_SKIP_LIST
#define EASE_DATA_SKIP_LIST

#include <functional>
#include <memory>
#include <random>
#include <cassert>
#include <cstdint>

namespace ease { namespace data { namespace skip_list {

typedef unsigned int  u8;
typedef unsigned int u16;

template <typename T>
class skip_list;

#include "skip_list/imp/data_traits.imp.hpp"
#include "skip_list/imp/data_node.imp.hpp"
#include "skip_list/imp/data_iterator.imp.hpp"

template <typename T>
class skip_list
{
public:
    typedef T type_skip_list_traits;
    typedef skip_list<T> type_this;

    typedef typename T::type_key   type_key;
    typedef typename T::type_value type_value;

    typedef typename T::type_key_comparator type_key_comparator;
    typedef typename T::type_value_allocator type_value_allocator;

    typedef std::size_t type_size;

    typedef skip_list_node<T> type_node;
    
    typedef skip_list_iterator
      < type_node
      , type_value*
      , type_value&
      > type_iterator;

    typedef typename type_iterator::type_const_iterator type_const_iterator;
    typedef std::reverse_iterator<type_iterator> type_reverse_iterator;
    typedef std::reverse_iterator<type_const_iterator> type_const_reverse_iterator;

    // TODO: C++11 ifdef
    //typedef typename std::allocator_traits<type_value_allocator>::
    //  template rebind_alloc<type_node > type_node_allocator;
    //typedef typename std::allocator_traits<type_value_allocator>::
    //  template rebind_alloc<type_node*> type_node_pointer_allocator;
    typedef typename type_value_allocator::template rebind<type_node >::other
        type_node_allocator;
    typedef typename type_value_allocator::template rebind<type_node*>::other
        type_node_pointer_allocator;


    // CONSTRUCTORs & DESTRUCTOR
    // IMP: fun_construct_destruct.imp.hpp
    skip_list
      ( type_key_comparator const& c = type_key_comparator()
      , type_value_allocator const& a = type_value_allocator()
      );
    skip_list(type_this const& other);
    ~skip_list();

    // MODIFIERS
    // IMP: fun_insert.imp.hpp
    std::pair<type_iterator, bool> insert_unique(type_value const& value);
    type_iterator                  insert(type_value const& value);

    // IMP: fun_erase.imp.hpp
    type_iterator erase(type_const_iterator pos);
    std::pair<type_iterator, type_size> erase(type_const_iterator beg, type_const_iterator end);
    std::pair<type_iterator, type_size> erase(type_key const& key);
    std::pair<type_iterator, type_size> erase_unique(type_key const& key);

    // IMP: fun_construct_destruct.imp.hpp
    void clear();

    // IMP: fun_construct_destruct.imp.hpp
    void swap(type_this& other);

    // ITERATORS
    // IMP: fun_iterator.imp.hpp
    type_iterator end();
    type_const_iterator end() const;
    type_const_iterator cend() const;
 
    type_reverse_iterator rend();
    type_const_reverse_iterator rend() const;
    type_const_reverse_iterator crend() const;

    type_iterator begin();
    type_const_iterator begin() const;
    type_const_iterator cbegin() const;

    type_reverse_iterator rbegin();
    type_const_reverse_iterator rbegin() const;
    type_const_reverse_iterator crbegin() const;

    // LOOKUP
    // IMP: fun_lookup.imp.hpp
    type_size count(type_key const& k) const;
    
    type_iterator find(type_key const& k);
    type_const_iterator find(type_key const& k) const;
    
    type_iterator lower_bound(type_key const& k);
    type_const_iterator lower_bound(type_key const& k) const;

    type_iterator upper_bound(type_key const& k);
    type_const_iterator upper_bound(type_key const& k) const;

    // CAPACITY
    // IMP: fun_capacity.imp.hpp
    bool empty() const;
    type_size size() const; 
    type_size max_size() const; 
    
    static type_key const& key(type_value const& value)
    {
        return type_skip_list_traits::key(value);
    }

    void print_levels()
    {
        for (type_node* it = node_begin(); it != node_end(); it = it->next[0])
        {
            printf("%d, ", it->next_size);
        }
        printf("\n");
    }

protected:
    // IMP: fun_insert_internal.imp.hpp
    type_node* insert_at_internal(type_value const& value, type_node** update);
    
    // IMP: fun_erase_internal.imp.hpp
    type_node* erase_internal(type_node** update);

    // IMP: fun_lookup_internal.imp.hpp
    type_node* lookup_internal
      ( type_node const* pos
      , type_node* (&update)[T::level_max]
      ) const;

    type_node* lookup_internal
      ( type_node const* pos
      ) const;

    type_node* lookup_internal
      ( type_key const& key
      , type_node* (&update)[T::level_max]
      ) const;

    type_node* lookup_internal
      ( type_key const& key
      ) const;

private:
    // IMP: fun_memory_internal.imp.hpp
    type_node* create_header_node();
    void       delete_header_node(type_node* node);

    type_node* create_node(type_node* prev, u8 next_size, type_value const& key);
    void       delete_node(type_node* node);
    
    // IMP: fun_iterator.imp.hpp
    type_node* node_end() const;
    type_node* node_begin() const;

    u8 random_level() const;

private:
    static const u8 level_max = T::level_max;
    
    // ALLOCATORS
    type_node_allocator node_allocator_m;
    type_node_pointer_allocator node_pointer_allocator_m;
    type_value_allocator value_allocator_m;

    const type_key_comparator cmp_lq_m;
    type_node* header_node_m;
    u8 level_max_current_m;
    type_size size_m;
};

// CONSTRUCTORS & DESTRUCTOR
#include "skip_list/imp/fun_construct_destruct.imp.hpp"

// ITERATORS
#include "skip_list/imp/fun_iterator.imp.hpp"

// MODIFIERS
#include "skip_list/imp/fun_insert.imp.hpp"
#include "skip_list/imp/fun_erase.imp.hpp"

// LOOKUP
#include "skip_list/imp/fun_lookup.imp.hpp"

// CAPACITY
#include "skip_list/imp/fun_capacity.imp.hpp"

// INTERNAL
#include "skip_list/imp/fun_insert_internal.imp.hpp"
#include "skip_list/imp/fun_erase_internal.imp.hpp"
#include "skip_list/imp/fun_lookup_internal.imp.hpp"
#include "skip_list/imp/fun_memory_internal.imp.hpp"

template <typename T>
inline
u8 skip_list<T>::random_level() const
{
    const u8 res = T::random_level(level_max_current_m);
    return res;
}

} // namespace skip_list
} // namespace data
} // namespace ease

#endif

