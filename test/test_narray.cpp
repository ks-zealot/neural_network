//
// Created by zealot on 13.12.2022.
//
//Link to Boost


//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "narray_module"
//VERY IMPORTANT - include this last
#include "../narray/narray.h"
#include <boost/test/unit_test.hpp>




BOOST_AUTO_TEST_SUITE(test_suite1)
//


    BOOST_AUTO_TEST_CASE(constructors)
    {
        narray<int> obj = narray<int>({2, 2});
        narray<int> obj2 = narray<int>({2, 2});
//Check default constructor
//Use BOOST_CHECK for small equal checks - true or false
        BOOST_CHECK(obj.get_size() == obj2.get_size());
    }

    BOOST_AUTO_TEST_CASE(print)
    {
        narray<int> obj = narray<int>({2, 2}, random_filler<int>::GetInstance());
        print_matrix(obj);
        BOOST_CHECK(false);
//Check default constructor
//Use BOOST_CHECK for small equal checks - true or false
    }
}