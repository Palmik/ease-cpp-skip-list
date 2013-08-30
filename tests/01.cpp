#include <cstdio>

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>
using namespace boost::unit_test;

#include "common.hpp"

#include <map>
#include <set>

#include "../src/ease/data/skip_list/standard_container/map.hpp"
#include "../src/ease/data/skip_list/standard_container/set.hpp"

typedef unsigned int uint;

template <typename T>
void properties_empty(T const& c)
{
    BOOST_CHECK(c.empty());
    BOOST_CHECK_EQUAL(c.size(), 0);

    BOOST_CHECK(c.begin() == c.end());
    BOOST_CHECK(c.cbegin() == c.cend());
    BOOST_CHECK(c.rbegin() == c.rend());
    BOOST_CHECK(c.crbegin() == c.crend());
}

template <typename C1, typename C2>
void properties_equal(C1 const& c1, C2 const& c2)
{
    BOOST_CHECK_EQUAL_COLLECTIONS(c1.begin(), c1.end(), c2.begin(), c2.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(c1.rbegin(), c1.rend(), c2.rbegin(), c2.rend());

    BOOST_CHECK_EQUAL(c1.size(), c2.size());
    BOOST_CHECK_EQUAL(c1.empty(), c2.empty());

    if (c1.empty())
    {
        properties_empty(c2);
    }

    for (auto it1 = c1.begin(); it1 != c1.end(); ++it1)
    {
        auto it2 = c2.find(key(*it1));
        BOOST_CHECK(it2 != c2.end());
        BOOST_CHECK_EQUAL(*it1, *it2);
    }
    
    for (auto it2 = c2.begin(); it2 != c2.end(); ++it2)
    {
        auto it1 = c1.find(key(*it2));
        BOOST_CHECK(it1 != c1.end());
        BOOST_CHECK_EQUAL(*it1, *it1);
    }
}

template <typename C1, typename C2, typename T>
void test_insert(std::vector<T> const& data)
{
    C1 c1;
    C2 c2;
    insert_into(data, c1);
    insert_into(data, c2);

    C2 c2_(c2);
    properties_equal(c1, c2);
    properties_equal(c1, c2_);
}

template <typename C1, typename C2, typename T>
void test_erase_key(std::vector<T> const& data)
{
    std::vector<T> data_erase = random_subset(data);
    C1 c1;
    C2 c2;
    insert_into(data, c1);
    insert_into(data, c2);
    
    C2 c2_(c2);
    erase_from(data_erase, c1);
    erase_from(data_erase, c2);
    erase_from(data_erase, c2_);
    
    insert_into(data, c1);
    insert_into(data, c2);
    insert_into(data, c2_);

    data_erase = random<std::vector<T>>();
    erase_from(data_erase, c1);
    erase_from(data_erase, c2);
    erase_from(data_erase, c2_);

    properties_equal(c1, c2);
    properties_equal(c1, c2_);
}

template <typename C1, typename C2, typename T>
void test_erase_subset_key(std::vector<T> const& data)
{
    std::vector<T> data_erase = random_subset(data);
    C1 c1;
    C2 c2;
    insert_into(data, c1);
    insert_into(data, c2);
    erase_from(data_erase, c1);
    erase_from(data_erase, c2);
    properties_equal(c1, c2);
    
    C2 c2_(c2);
    data_erase = random_subset(data);
    erase_from(data_erase, c1);
    erase_from(data_erase, c2);
    erase_from(data_erase, c2_);
    properties_equal(c1, c2);
    properties_equal(c1, c2_);
}

test_suite*
init_unit_test_suite(int, char**)
{
    static const std::size_t test_size = 100;

    // RANDOM SET DATA
    std::vector<std::vector<uint>> random_data;
    random_data.reserve(test_size);
    for (std::size_t i = 0; i < test_size; ++i)
    {
        random_data.push_back(random<std::vector<uint>>());
    }

    typedef ease::data::skip_list::set<uint> set;
    typedef std::set<uint> sample_set;
  
    // test_insert : set (int)
    framework::master_test_suite().add
      ( BOOST_PARAM_TEST_CASE((&test_insert<sample_set, set, uint>), random_data.begin(), random_data.end())
      );

    // test_erase_key : set (int)
    framework::master_test_suite().add
      ( BOOST_PARAM_TEST_CASE((&test_erase_key<sample_set, set, uint>), random_data.begin(), random_data.end())
      );

    // test_erase_subset_key : set (int)
    framework::master_test_suite().add
      ( BOOST_PARAM_TEST_CASE((&test_erase_subset_key<sample_set, set, uint>), random_data.begin(), random_data.end())
      );

    return 0;
}

