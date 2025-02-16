#include "ADS_set.h"
#include <iostream>

int main()
{
    // Create an ADS_set with some initial values
    ADS_set<int> my_set{7, 4, 1, 5, 3, 6, 0, 8, 10, 2, 9, 11};

    // Test the special mode iterator
    std::cout << "Special mode iteration:" << std::endl;
    auto it = my_set.z();
    int counter = 0;
    while (it != my_set.end())
    {
        std::cout << "Element " << counter << ": " << *it << std::endl;
        ++it;
        ++counter;
    }

    // Test the normal mode iterator
    std::cout << "Normal mode iteration:" << std::endl;
    for (auto it = my_set.begin(); it != my_set.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test special mode on an empty set
    ADS_set<int> empty_set;
    std::cout << "Special mode iteration on empty set:" << std::endl;
    for (auto it = empty_set.z(); it != empty_set.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test special mode on a set with one element
    ADS_set<int> single_element_set{42};
    std::cout << "Special mode iteration on single element set:" << std::endl;
    for (auto it = single_element_set.z(); it != single_element_set.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test special mode on a set with two elements
    ADS_set<int> two_elements_set{3, 14};
    std::cout << "Special mode iteration on two elements set:" << std::endl;
    for (auto it = two_elements_set.z(); it != two_elements_set.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // Test special mode on a set with three elements
    ADS_set<int> three_elements_set{5, 9, 7};
    std::cout << "Special mode iteration on three elements set:" << std::endl;
    for (auto it = three_elements_set.z(); it != three_elements_set.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}