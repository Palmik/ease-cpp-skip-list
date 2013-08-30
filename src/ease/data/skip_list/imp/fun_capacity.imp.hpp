template <typename T>
inline
bool skip_list<T>::empty() const
{
    return size_m == 0; 
}

template <typename T>
inline
typename skip_list<T>::type_size skip_list<T>::size() const
{
    return size_m;
}

template <typename T>
inline
typename skip_list<T>::type_size skip_list<T>::max_size() const
{
    // NOTE: std::numeric_limits<type_size>::max();
    return 1 << 31;
}

