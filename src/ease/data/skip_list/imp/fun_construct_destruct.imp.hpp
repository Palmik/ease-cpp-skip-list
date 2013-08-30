template <typename T>
inline
skip_list<T>::skip_list
    ( typename skip_list<T>::type_key_comparator const& cmp_lq
    , typename skip_list<T>::type_value_allocator const& value_allocator
    )
    : value_allocator_m(value_allocator)
    , cmp_lq_m(cmp_lq)
    , header_node_m(0)
    , level_max_current_m(1)
    , size_m(0)
{
    header_node_m = create_header_node();
}

template <typename T>
inline
skip_list<T>::~skip_list()
{
    clear();
    delete_header_node(header_node_m);
}

template <typename T>
inline
void skip_list<T>::clear()
{
    type_node* curr = header_node_m->next[0];
    type_node* curr_tmp = 0;

    while (curr != node_end())
    {
        curr_tmp = curr->next[0];
        delete_node(curr);
        curr = curr_tmp;
    }

    std::fill(header_node_m->next, header_node_m->next + header_node_m->next_size, header_node_m);
    header_node_m->prev = header_node_m;

    size_m = 0;
}

// min(max_level, 1 + the position of the least significant bit of (index + 1) that is set to 1 (or infinity for 0))
template <typename SL>
u8 node_level(typename SL::type_size index, u8 max_level)
{
    ++index;
    
    // TODO: Look into using ffs (POSIX) or bfs (x86 assembly).
    u8 res = 1;
    for (
        ; !(index % SL::type_skip_list_traits::level_pro_inverse) && (res < max_level)
        ;  (index /= SL::type_skip_list_traits::level_pro_inverse), ++res
        )
    {
    }

    return res;
}

// TODO: Eww. 
template <typename T>
inline
skip_list<T>::skip_list
    ( typename skip_list<T>::type_this const& other
    )
    : value_allocator_m(other.value_allocator_m)
    , cmp_lq_m(other.cmp_lq_m)
    , header_node_m(0)
    , level_max_current_m(0)
    , size_m(other.size_m)
{

    header_node_m = create_header_node();
   
    // TODO: We need to use allocator here. Look into it.
    //std::unique_ptr<type_node*[]> nodes(new type_node*[size_m]); 

    type_node** nodes = node_pointer_allocator_m.allocate(size_m); 
    type_node* prev_node = header_node_m;
    type_size i = 0;
    for ( type_node* ocurr = other.header_node_m->next[0]
        ; i < size_m
        ; ocurr = ocurr->next[0]
        )
    {
        u8 lvl = node_level<type_this>(i, level_max);
        nodes[i] = create_node(prev_node, lvl, ocurr->value);
        prev_node = nodes[i];
        ++i; 
        level_max_current_m = (lvl > level_max_current_m) ? lvl : level_max_current_m; 
    }

    for (type_size i = 0; i < size_m; ++i)
    {
        type_size skip = 1;
        for (u8 lvl = 0; lvl < nodes[i]->next_size; ++lvl)
        {
            // TODO: This has potential for integer overflow.
            if (i + skip >= size_m)
            {
                nodes[i]->next[lvl] = node_end();
            }
            else
            {
                nodes[i]->next[lvl] = nodes[i + skip];
            }
         
            skip *= type_skip_list_traits::level_pro_inverse;
        }
    }

    type_size skip = 1;
    for (u8 lvl = 0; lvl < level_max_current_m; ++lvl)
    {
        if (skip > size_m)
        {
            header_node_m->next[lvl] = header_node_m;
        }
        else
        {
            header_node_m->next[lvl] = nodes[skip - 1];
        }
         
        skip *= type_skip_list_traits::level_pro_inverse;
    }

    header_node_m->prev = nodes[size_m - 1];

    node_pointer_allocator_m.deallocate(nodes, size_m);
}

