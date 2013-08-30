/*
    type_size count(type_key const& k) const;
    
    type_iterator find(type_key const& k);
    type_const_iterator find(type_key const& ki) const;
    
    type_iterator lower_bound(type_key const& k);
    type_const_iterator lower_bound(type_key const& k) const;
*/

template <typename T>
inline
typename skip_list<T>::type_size skip_list<T>::count
    ( typename skip_list<T>::type_key const& k
    ) const
{
    
    type_node* curr = lookup_internal(k);
    type_size  count = 0;
    while (!cmp_lq_m(k, key(curr->value)) && !cmp_lq_m(key(curr->value), k))
    {
        curr = curr->next[0];
        ++count;
    }

    return count;
}

template <typename T>
inline
typename skip_list<T>::type_const_iterator skip_list<T>::find
    ( typename skip_list<T>::type_key const& k
    ) const
{
    type_node* res = lookup_internal(k);

    if (res != node_end() && cmp_lq_m(k, key(res->value)))
    {
        return type_const_iterator(node_end());
    }
    
    return type_const_iterator(res);
}

template <typename T>
inline
typename skip_list<T>::type_iterator skip_list<T>::find
    ( typename skip_list<T>::type_key const& k
    )
{
    type_node* res = lookup_internal(k);

    if (res != node_end() && cmp_lq_m(k, key(res->value)))
    {
        return type_iterator(node_end());
    }
    
    return type_iterator(res);
}

template <typename T>
inline
typename skip_list<T>::type_const_iterator skip_list<T>::lower_bound
    ( typename skip_list<T>::type_key const& k
    ) const
{
    return type_const_iterator(lookup_internal(k));
}

template <typename T>
inline
typename skip_list<T>::type_iterator skip_list<T>::lower_bound
    ( typename skip_list<T>::type_key const& k
    )
{
    return type_iterator(lookup_internal(k));
}

template <typename T>
inline
typename skip_list<T>::type_const_iterator skip_list<T>::upper_bound
    ( typename skip_list<T>::type_key const& k
    ) const
{
    type_node* curr = lookup_internal(k);

    while (curr != node_end() && !cmp_lq(key(curr->value), k))
    {
        curr = curr->next[0];
    }

    return type_const_iterator(curr);
}

template <typename T>
inline
typename skip_list<T>::type_iterator skip_list<T>::upper_bound
    ( typename skip_list<T>::type_key const& k
    )
{
    type_node* curr = lookup_internal(k);

    while (curr != node_end() && !cmp_lq(key(curr->value), k))
    {
        curr = curr->next[0];
    }

    return type_iterator(curr);
}

