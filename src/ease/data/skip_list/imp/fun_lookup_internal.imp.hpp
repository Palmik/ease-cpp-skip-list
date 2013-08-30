template <typename T>
inline
typename skip_list<T>::type_node* skip_list<T>::lookup_internal
    ( typename skip_list<T>::type_node const* pos
    , typename skip_list<T>::type_node* (&update)[T::level_max]
    ) const
{
    // ASSERT: pos != 0
    
    type_node* curr = header_node_m;
    type_node* next = 0;
    type_key const& k = key(pos->value);

    // lvl takes values from [level_max_current_m - 1, .. , 0]
    for (u8 lvl = level_max_current_m; lvl-- > 0; )
    {
        next = curr->next[lvl];
        while ( next != node_end() &&
                ( cmp_lq_m(key(next->value), k) ||
                  ( !cmp_lq_m(k, key(next->value)) && next != pos )
                )
              )
        {
            curr = next;
            next = curr->next[lvl];
        }
        // ASSERT: curr->next[lvl] == node_end() (we are the end of the list) or
        //   key(curr->next[lvl]->value) >= k (we found node with such key, or it does not exist)
        
        update[lvl] = curr;
    }

    return curr->next[0]; // == update[0]->next[0]
}

template <typename T>
inline
typename skip_list<T>::type_node* skip_list<T>::lookup_internal
    ( typename skip_list<T>::type_node const* pos
    ) const
{
    // ASSERT: pos != 0
    // key(pos->value) == k
    
    type_node* curr = header_node_m;
    type_node* next = 0;
    type_key const& k = key(pos->value);

    // lvl takes values from [level_max_current_m - 1, .. , 0]
    for (u8 lvl = level_max_current_m; lvl-- > 0; )
    {
        next = curr->next[lvl];
        while ( next != node_end() &&
                ( cmp_lq_m(key(next->value), k) ||
                  ( !cmp_lq_m(k, key(next->value)) && next != pos )
                )
              )
        {
            curr = next;
            next = curr->next[lvl];
        }
        // ASSERT: curr->next[lvl] == node_end() (we are the end of the list) or
        //   key(curr->next[lvl]->value) >= k (we found node with such key, or it does not exist)
    }

    return curr->next[0]; // == update[0]->next[0]
}

template <typename T>
inline
typename skip_list<T>::type_node* skip_list<T>::lookup_internal
    ( typename skip_list<T>::type_key const& k
    , typename skip_list<T>::type_node* (&update)[T::level_max]
    ) const
{
    type_node* curr = header_node_m;
    // lvl takes values from [level_max_current_m - 1, .. , 0]
    for (u8 lvl = level_max_current_m; lvl-- > 0; )
    {
        // ASSERT: curr->next_size > lvl

        while (curr->next[lvl] != node_end() && cmp_lq_m(key(curr->next[lvl]->value), k))
        {
            // ASSERT: curr->next_size > lvl
            curr = curr->next[lvl];
        }
        // ASSERT: curr->next[lvl] == node_end() (we are the end of the list) or
        //   key(curr->next[lvl]->value) >= k (we found node with such key, or it does not exist)
        
        update[lvl] = curr;
    }

    return curr->next[0]; // == update[0]->next[0]
}

template <typename T>
inline
typename skip_list<T>::type_node* skip_list<T>::lookup_internal
    ( typename skip_list<T>::type_key const& k
    ) const 
{
    type_node* curr = header_node_m;
    type_node* next = 0;

    // lvl takes values from [level_max_current_m - 1, .. , 0]
    for (u8 lvl = level_max_current_m; lvl-- > 0; )
    {
        next = curr->next[lvl];
        while (next != node_end() && cmp_lq_m(key(next->value), k))
        {
            curr = next;
            next = curr->next[lvl];
        }
        // ASSERT: curr->next[lvl] == node_end() (we are the end of the list) or
        //       key(curr->next[lvl]->value) >= k (we found node with such key, or it does not exist)
    }

    return curr->next[0]; // == update[0]->next[0]
}

