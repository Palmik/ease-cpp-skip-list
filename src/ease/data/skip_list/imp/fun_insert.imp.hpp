template <typename T>
inline
std::pair<typename skip_list<T>::type_iterator, bool>
skip_list<T>::insert_unique
    ( typename skip_list<T>::type_value const& value
    )
{
    type_node* update[level_max];
    type_node* candidate = lookup_internal(key(value), update);
    // ASSERT:
    // candidate == node_end() (the list is empty) or 
    // key(candidate->value) == key(value) (the list contains the key `key(value)`, then `candidate` is the first node with the key `key(value)`) or
    // key(candidate->value) >  key(value) (the list does not contain the key `key(value)`)

    // candiate == node_end() or key(candidate->value) > key(value)
    if (candidate == node_end() || cmp_lq_m(key(value), key(candidate->value)))
    {
        return std::make_pair(type_iterator(insert_at_internal(value, update)), true);
    }
    
    // key(candiate->value) == key(value)
    return std::make_pair(candidate, false);
}

template <typename T>
inline
typename skip_list<T>::type_iterator
skip_list<T>::insert
    ( typename skip_list<T>::type_value const& value
    )
{
    type_node* update[level_max];
    lookup_internal(key(value), update);

    return type_iterator(insert_at_internal(value, update));
}

