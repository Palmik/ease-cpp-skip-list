template <typename T>
struct skip_list_node
{
    typedef T type_skip_list_traits;

    skip_list_node
        ( skip_list_node<T>* prev
        , u8 next_size
        , typename T::type_value const& value
        )
        : prev(prev) 
        , next(0)
        , next_size(next_size)
        , value(value)
    {
    }
    
    skip_list_node
        ( skip_list_node<T>* prev
        , u8 next_size
        , typename T::type_value&& value
        )
        : prev(prev) 
        , next(0)
        , next_size(next_size)
        , value(std::move(value))
    {
    }

    skip_list_node<T>*  prev;
    skip_list_node<T>** next;

    u8 next_size;

    typename T::type_value value;

private:
    skip_list_node();
    skip_list_node(skip_list_node<T> const&);
};

