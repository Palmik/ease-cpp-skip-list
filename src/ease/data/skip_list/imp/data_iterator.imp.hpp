template <typename NODE, typename VALUE_PTR, typename VALUE_REF>
struct skip_list_iterator
{
    template<typename> friend class skip_list;

    typedef typename NODE::type_skip_list_traits type_skip_list_traits;
    
    typedef       skip_list_node<type_skip_list_traits> type_node;
    typedef const skip_list_node<type_skip_list_traits> type_const_node;

    typedef NODE  type_this_node;
    typedef NODE* type_this_node_pointer;
    typedef VALUE_PTR type_this_value_pointer;
    typedef VALUE_REF type_this_value_reference;

    typedef skip_list_iterator
        < type_node
        , typename type_skip_list_traits::type_value*
        , typename type_skip_list_traits::type_value&
        > type_iterator;

    typedef skip_list_iterator
        < type_const_node
        , typename type_skip_list_traits::type_value const*
        , typename type_skip_list_traits::type_value const&
        > type_const_iterator;

    typedef skip_list_iterator
        < type_this_node
        , type_this_value_pointer
        , type_this_value_reference
        > type_this;
    
    // STD TYPEDEFS
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef typename type_skip_list_traits::type_value value_type;
    typedef typename std::ptrdiff_t difference_type;
    typedef type_this_value_pointer pointer;
    typedef type_this_value_reference reference;

    skip_list_iterator() : position_m(0)
    {
    }

    skip_list_iterator(type_this_node* position) : position_m(position)
    {
    }

    skip_list_iterator(type_iterator const& x) : position_m(x.position_m)
    {
    }

    typename type_skip_list_traits::type_value& key() const
    {
        return position_m->key;
    }

    type_this_value_pointer operator->() const
    {
        return &position_m->value;
    }

    type_this_value_reference operator*() const
    {
        return position_m->value;
    }

    type_this& operator++()
    {
        position_m = position_m->next[0];
        return *this;
    }

    type_this& operator--()
    {
        position_m = position_m->prev;
        return *this;
    }

    type_this operator++(int)
    {
        type_this tmp = *this;
        ++*this;
        return tmp;
    }
    
    type_this operator--(int)
    {
        type_this tmp = *this;
        --*this;
        return tmp;
    }

    bool operator!=(type_this const& other) const
    {
        return position_m != other.position_m;
    }

    bool operator==(type_this const& other) const
    {
        return position_m == other.position_m;
    }

    // In case of:
    //   * delete: deletes the node pointed to by `position_m`
    //   * insert: inserts after the node pointed to by `position_m`
    type_this_node* position_m;

    type_this_node* node() { return position_m; }
};

