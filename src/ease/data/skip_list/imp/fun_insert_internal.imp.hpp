template <typename T>
inline
typename skip_list<T>::type_node* skip_list<T>::insert_at_internal
    ( typename skip_list<T>::type_value const& value 
    , typename skip_list<T>::type_node** update
    )
{
    u8 lvl = random_level();

    if (lvl > level_max_current_m)
    {
        for (u8 i = level_max_current_m; i < lvl; ++i)
        {
            update[i] = header_node_m;
        }

        level_max_current_m = lvl;
    }

    type_node* new_node = create_node(update[0], lvl, value);
    update[0]->next[0]->prev = new_node;

    for (u8 i = 0; i < lvl; ++i)
    {
        // ASSERT: update[i]->next_size >= i;

        new_node->next[i] = update[i]->next[i];
        update[i]->next[i] = new_node;
    }

    ++size_m;

    return new_node;
}

