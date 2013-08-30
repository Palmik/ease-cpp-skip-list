template <typename T>
inline
typename skip_list<T>::type_iterator skip_list<T>::begin()
{
    return type_iterator(node_begin());
}

template <typename T>
inline
typename skip_list<T>::type_const_iterator skip_list<T>::begin() const
{
    return type_const_iterator(node_begin());
}

template <typename T>
inline
typename skip_list<T>::type_const_iterator skip_list<T>::cbegin() const
{
    return type_const_iterator(node_begin());
}

template <typename T>
inline
typename skip_list<T>::type_iterator skip_list<T>::end()
{
    return type_iterator(node_end());
}

template <typename T>
inline
typename skip_list<T>::type_const_iterator skip_list<T>::end() const
{
    return type_const_iterator(node_end());
}

template <typename T>
inline
typename skip_list<T>::type_const_iterator skip_list<T>::cend() const
{
    return type_const_iterator(node_end());
}

template <typename T>
inline
typename skip_list<T>::type_reverse_iterator skip_list<T>::rend()
{
    return type_reverse_iterator(begin());
}

template <typename T>
inline
typename skip_list<T>::type_const_reverse_iterator skip_list<T>::rend() const
{
    return type_const_reverse_iterator(cbegin());
}

template <typename T>
inline
typename skip_list<T>::type_const_reverse_iterator skip_list<T>::crend() const
{
    return type_const_reverse_iterator(cbegin());
}


template <typename T>
inline
typename skip_list<T>::type_reverse_iterator skip_list<T>::rbegin()
{
    return type_reverse_iterator(end());
}

template <typename T>
inline
typename skip_list<T>::type_const_reverse_iterator skip_list<T>::rbegin() const
{
    return type_const_reverse_iterator(cend());
}

template <typename T>
inline
typename skip_list<T>::type_const_reverse_iterator skip_list<T>::crbegin() const
{
    return type_const_reverse_iterator(cend());
}

template <typename T>
inline
typename skip_list<T>::type_node* skip_list<T>::node_begin() const
{
    return header_node_m->next[0];
}

template <typename T>
inline
typename skip_list<T>::type_node* skip_list<T>::node_end() const
{
    return header_node_m;
}


