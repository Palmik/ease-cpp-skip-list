template <typename T>
inline
typename skip_list<T>::type_node* skip_list<T>::create_header_node()
{
    type_node* new_node = node_allocator_m.allocate(1);
    new_node->next_size = level_max;

    new_node->next = node_pointer_allocator_m.allocate(new_node->next_size);
    
    std::fill(new_node->next, new_node->next + new_node->next_size, new_node);
    new_node->prev = new_node;

    return new_node;
}

template <typename T>
inline
void skip_list<T>::delete_header_node(skip_list<T>::type_node* node)
{
    node_pointer_allocator_m.deallocate(node->next, node->next_size);
    node_allocator_m.deallocate(node, 1);
}

template <typename T>
inline
typename skip_list<T>::type_node* skip_list<T>::create_node
    ( typename skip_list<T>::type_node* prev
    , u8 next_size
    , typename skip_list<T>::type_value const& value
    )
{
    type_node* new_node = node_allocator_m.allocate(1);

    // OK. This is C++11 version of construct that can invoke the constructor.
    node_allocator_m.construct(new_node, prev, next_size, value);

    // Would this be correct for C++03?
    // node<K, E> stack_node(prev, next_size, K, E);
    // node_allocator.construct(new_node, stack_node);

    // Now we allocate the dynamic array inside the 'new_node'
    new_node->next = node_pointer_allocator_m.allocate(new_node->next_size);

    return new_node;
}

template <typename T>
inline
void skip_list<T>::delete_node(skip_list<T>::type_node* node)
{
    node_pointer_allocator_m.deallocate(node->next, node->next_size);
    node_allocator_m.destroy(node);
    node_allocator_m.deallocate(node, 1);
}

