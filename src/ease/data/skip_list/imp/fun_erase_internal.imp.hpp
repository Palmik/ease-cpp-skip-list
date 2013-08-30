template <typename T>
inline
typename skip_list<T>::type_node* skip_list<T>::erase_internal
    ( typename skip_list<T>::type_node** update
    )
{
    // ASSERT: update[0]->next[0] != node_end()
    assert(update[0]->next[0] != node_end());

    type_node* curr = update[0]->next[0];
    type_node* next = curr->next[0];

    for (u8 lvl = 0; lvl < level_max_current_m; ++lvl)
    {
        if (update[lvl]->next[lvl] == curr)
        {
            update[lvl]->next[lvl] = curr->next[lvl];
        }
    }
    next->prev = curr->prev; // == update[0]->prev

    delete_node(curr);
        
    while (level_max_current_m > 1 && header_node_m->next[level_max_current_m - 1] == node_end())
    {
        --level_max_current_m;
    }
    
    --size_m;

    return next;
}

