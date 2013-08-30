template <typename T>
inline
std::pair<typename skip_list<T>::type_iterator, typename skip_list<T>::type_size>
skip_list<T>::erase
    ( typename skip_list<T>::type_const_iterator beg_it
    , typename skip_list<T>::type_const_iterator end_it
    )
{
    type_node* update[level_max];
    
    type_node* curr = beg_it.node()->next[0]->prev;
    type_node* e = end_it.node()->next[0]->prev;
    type_size  count = 0;

    if (lookup_internal(curr, update) == node_end())
    {
        return std::make_pair(type_iterator(node_end()), 0);
    }

    while (curr != e)
    {
        curr = erase_internal(update);
        ++count;
    }

    return std::make_pair(type_iterator(curr), count);
}

template <typename T>
inline
typename skip_list<T>::type_iterator skip_list<T>::erase
    ( typename skip_list<T>::type_const_iterator pos_it
    )
{
    type_node* update[level_max];
    lookup_internal(pos_it.node(), update);

    return type_iterator(erase_internal(update));
}

template <typename T>
inline
std::pair<typename skip_list<T>::type_iterator, typename skip_list<T>::type_size>
skip_list<T>::erase
    ( typename skip_list<T>::type_key const& k
    )
{
    type_node* update[level_max];
    
    type_node* curr = lookup_internal(k, update);
    type_size  count = 0;
    while (curr != node_end() && !cmp_lq_m(k, key(curr->value)) && !cmp_lq_m(key(curr->value), k))
    {
        curr = erase_internal(update);
        ++count;
    }

    return std::make_pair(type_iterator(curr), count);
}

template <typename T>
inline
std::pair<typename skip_list<T>::type_iterator, typename skip_list<T>::type_size>
skip_list<T>::erase_unique
    ( typename skip_list<T>::type_key const& k
    )
{
    type_node* update[level_max];
    
    type_node* curr = lookup_internal(k, update);
    if (curr != node_end() && !cmp_lq_m(k, key(curr->value)) && !cmp_lq_m(key(curr->value), k))
    {
        return std::make_pair(erase_internal(update), 1);
    }

    return std::make_pair(type_iterator(curr), 0);
}

