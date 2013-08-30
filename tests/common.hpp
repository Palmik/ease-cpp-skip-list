#ifndef EASE_SKIP_LIST_TESTS_COMMON
#define EASE_SKIP_LIST_TESTS_COMMON

#include <string>
#include <limits>
#include <random>
#include <vector>
#include <iterator>
#include <type_traits>
#include <algorithm>

template <typename T>
inline
T const& key(T const& x)
{
    return x;
}

template <typename L, typename R>
inline
L const& key(std::pair<L, R> const& x)
{
    return x.first;
}

template <typename C, typename T>
inline
void insert_into(std::vector<T> data, C& target)
{
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        target.insert(*it);
    }
}

template <typename C, typename T>
inline
void erase_from(std::vector<T> data, C& target)
{
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        target.erase(*it);
    }
}

template <typename T>
inline
std::vector<std::pair<T, int>> make_map_values(std::vector<T> const& data)
{
    std::vector<std::pair<T, int>> res;
    res.reserve(data.size());

    int i = 0;
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        res.push_back(std::make_pair(*it, i));
        ++i;
    }

    return res;
}

template <typename T>
struct is_container
{
    static const bool value = false;
};

template <typename T>
struct is_container<std::vector<T>>
{
    static const bool value = true;
};

template <>
struct is_container<std::string>
{
    static const bool value = true;
};

template <typename T, typename E = void>
struct random_generator_parameters;

template <typename T>
struct random_generator_parameters
  < T
  , typename std::enable_if<std::is_integral<T>::value>::type
  >
{
    random_generator_parameters
      ( T min = std::numeric_limits<T>::min()
      , T max = std::numeric_limits<T>::max()
      )
      : min(min), max(max)
    {
        // ASSERT: min <= max
    }

    std::size_t min;
    std::size_t max;
};

template <typename T>
struct random_generator_parameters
  < T
  , typename std::enable_if<is_container<T>::value>::type
  >
{
    random_generator_parameters
      ( typename T::size_type min_size = 0
      , typename T::size_type max_size = 5000
      , random_generator_parameters<typename T::value_type> p =
          random_generator_parameters<typename T::value_type>()
      )
      : min_size(min_size), max_size(max_size)
      , value_generator_parameters(p)
    {
        // ASSERT: min_size <= max_size
    }

    typename T::size_type min_size;
    typename T::size_type max_size;

    random_generator_parameters<typename T::value_type> value_generator_parameters;
};

template <>
struct random_generator_parameters<std::string>
{
    random_generator_parameters
      ( std::string::size_type min_size = 0
      , std::string::size_type max_size = 50 
      , random_generator_parameters<char> p =
          random_generator_parameters<char>('0', 'z')
      )
      : min_size(min_size), max_size(max_size)
      , value_generator_parameters(p)
    {
        // ASSERT: min_size <= max_size
    }

    std::string::size_type min_size;
    std::string::size_type max_size;

    random_generator_parameters<char> value_generator_parameters;
};

template
  < typename T
  , typename std::enable_if<std::is_integral<T>::value, int>::type = 0 
  >
inline T random(random_generator_parameters<T> p = random_generator_parameters<T>())
{
    static std::random_device rd;
    static std::uniform_int_distribution<T> distribution(p.min, p.max);

    return distribution(rd);
}

template 
  < typename T
  , typename std::enable_if<is_container<T>::value, int>::type = 0
  >
inline T random (random_generator_parameters<T> p = random_generator_parameters<T>())
{
    typename T::size_type size = random<typename T::size_type>
      ( random_generator_parameters<typename T::size_type>(p.min_size, p.max_size)
      );

    T res;
    res.reserve(size);
    std::generate_n
      ( std::inserter(res, res.begin())
      , size
      , [&p]() { return random<typename T::value_type>(p.value_generator_parameters); }
      );

    return res;
}

template <typename T>
inline
std::vector<T> random_subset(std::vector<T> const& data)
{
    std::vector<T> res;
    res.reserve(data.size() / 1.5);

    for (T const& e : data)
    {
        if (random<int>() % 2)
        {
            res.push_back(e);
        }
    }

    std::random_shuffle(res.begin(), res.end());

    return res;
}

/*
inline random_generator_parameters<std::string> rp_string
  ( std::size_t min = 0
  , std::size_t max = 30
  , random_generator_parameters<char> rpc = random_generator_parameters<char>('0', 'z')
  )
{
    return random_generator_parameters<std::string>(min, max, rpc);
}

inline std::string random_string(random_generator_parameters<std::string> rgp = rp_string())
{
    return random<std::string>(rgp);
}

inline random_generator_parameters<int> rp_int
  ( int min = std::numeric_limits<int>::min()
  , int max = std::numeric_limits<int>::max()
  )
{
    return random_generator_parameters<int>(min, max);
}

inline int random_int(random_generator_parameters<int> rgp = rp_int())
{
    return random<int>(rgp);
}

inline random_generator_parameters<std::vector<int>> rp_vector_int
  ( std::size_t min = 0
  , std::size_t max = 500
  , random_generator_parameters<int> rgp = rp_int()
  )
{
    return random_generator_parameters<std::vector<int>>(min, max, rgp);
}

inline std::vector<int> random_vector_int
  ( random_generator_parameters<std::vector<int>> rgp = rp_vector_int()
  )
{
    return random<std::vector<int>>(rgp);
}

inline random_generator_parameters<std::vector<std::string>> rp_vector_string
  ( std::size_t min = 0
  , std::size_t max = 500
  , random_generator_parameters<std::string> rgp = rp_string()
  )
{
    return random_generator_parameters<std::vector<std::string>>(min, max, rgp);
}

*/

#endif // EASE_SKIP_LIST_TESTS_COMMON

