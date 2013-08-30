#include <iostream>
#include <memory>
#include <string>
#include <list>
#include <vector>
#include <set>

#include "skip_list/standard_container/map.hpp"
#include "skip_list/standard_container/set.hpp"
#include "../../tests/common.hpp"

using namespace data::skip_list;

template <typename T>
void print_map(T const& m)
{
    // C++11
    //for (std::pair<int, int> const& x: m)
    //{
    //    std::printf("(%d, %d)\n", x.first, x.second);
    //}
    //std::printf("\n");
    
    for (typename T::const_iterator it = m.begin(); it != m.end(); ++it)
    {
        std::cout << '(' << (*it).first << ", " << (*it).second << ") ";
    }
    std::printf("\n");
}

template <typename T>
void print_container(T const& m)
{
    // C++11
    //for (std::pair<int, int> const& x: m)
    //{
    //    std::printf("(%d, %d)\n", x.first, x.second);
    //}
    //std::printf("\n");
    
    for (typename T::const_iterator it = m.begin(); it != m.end(); ++it)
    {
        std::cout << *it << ' ';
    }
    std::printf("\n");
}

int main()
{
    set<int> sls;
    std::set<int> stds; 

    /*
    sls.insert("1");
    sls.insert("2");
    sls.insert("3");

    sls.erase("1");
    sls.erase("2");
    sls.erase("3");

    sls.insert("2");
    sls.insert("3");

    sls.erase("1");
    sls.erase("2");
    sls.erase("3");
    */

    random_generator_parameters<std::vector<int>> rgp;
    rgp.value_generator_parameters.min = 0;
    rgp.value_generator_parameters.max = 9999999;

    std::vector<int> data = random<std::vector<int>>(rgp);
    std::vector<int> data_erase = random_subset(data);
    
    //print_container(data);
    //print_container(data_erase);

    insert_into(data, sls);
    insert_into(data, stds);
    //print_container(sls);
    erase_from(data_erase, sls); 
    erase_from(data_erase, stds); 
    set<int> sls_(sls);
    
    data = random_subset(data_erase);
    insert_into(data, sls);
    insert_into(data, sls_);
    insert_into(data, stds);
    erase_from(data_erase, sls); 
    erase_from(data_erase, sls_); 
    erase_from(data_erase, stds); 
    //print_container(sls);
    //print_container(stds);
    printf("%lu\n", sls.size());
    printf("%lu\n", sls_.size());
    printf("%lu\n", stds.size());

    //(sls).find(5);
    static_cast<set<int> const&>(sls).find(5);

    sls.erase(sls.cbegin(), sls.cend());
    sls.clear();
}

