//
//  unit_test.cpp
//  epita-LibBistro
//
//  Created by Matthieu Archambault on 26/01/2019.
//  Copyright © 2019 Matthieu Archambault. All rights reserved.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/base.hh"
#include "../src/bignum.hh"

TEST_CASE(  "Check Base")
{
    using value_t = uint8_t;
    using bignum_t = bistro::BigNum<value_t>;
    
    using base_t = bistro::Base<value_t>;
    std::initializer_list<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    bistro::Base A(list);
    
    auto b = bignum_t(10);
    b.set_digit(2, 6);
    REQUIRE( b.get_digit.at(0) == 1)
    REQUIRE( b.get_digit.at(1) == 1)
    REQUIRE( b.get_digit.at(2) == 6)

    

    std::cout << '\n';
    auto b2 = bignum_t(10);
    b2.set_digit(2, 6);
    b2.print(std::cout, A);
    std::cout << '\n';
}
