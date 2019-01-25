// Example use of the library. Do not submit this file.
#include <iostream>
#include <cstdint>
#include <sstream>
#include <memory>

#include "base.hh"
#include "bignum.hh"
#include "ast-factory.hh"
#include "ast-node.hh"

int main()
{
    using value_t = uint8_t;
    using base_t = bistro::Base<value_t>;
    using bignum_t = bistro::BigNum<value_t>;

    auto b = bignum_t(10);
    b.set_digit(3, 2);
    unsigned d1 = b.get_digit(3);
    unsigned d2 = b.get_digit(2);
    std::cout << d1 << '\n'
              << d2 << '\n'
              << b.get_num_digits() << '\n';
    b.set_digit(3, 0);
    std::cout << b.get_num_digits() << '\n';
    try
    {
        b.get_digit(0);
    } catch (const std::out_of_range& e)
    {
        std::cerr << "Out of range: " << e.what() << '\n';
    }
    auto base = base_t{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

    std::stringstream ss("cafe");

    auto bptr = std::make_shared<bignum_t>(ss, base);

    auto factory = bistro::ASTFactory<bignum_t, base_t>{};
    auto num = factory(bptr);
    auto minus = factory(num, bistro::OpType::MINUS);
    auto plus = factory(num, minus, bistro::OpType::PLUS);
    plus->print_infix(std::cout, base) << '\n';
    plus->print_pol(std::cout, base) << '\n';
    plus->eval()->print(std::cout, base) << '\n';
}
