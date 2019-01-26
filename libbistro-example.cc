// Example use of the library. Do not submit this file.
#include <iostream>
#include <cstdint>
#include <sstream>
#include <memory>

#include "src/base.hh"
#include "src/bignum.hh"
#include "src/ast-factory.hh"

int main() {
  using value_t = uint8_t;
  using bignum_t = bistro::BigNum<value_t>;

  using base_t = bistro::Base<value_t>;

  std::initializer_list<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  bistro::Base A(list);

  auto b = bignum_t(10);
  b.set_digit(2, 6);
  b.print(std::cout, A);

  std::cout << '\n';
  auto b2 = bignum_t(10);
  b2.set_digit(2, 6);
  b2.print(std::cout, A);
  std::cout << '\n';

  auto b3 = b * b2;
  b3.print(std::cout, A);
    
    b3 += b;
    b3.print(std::cout, A);
    
  b.set_digit(3, 0);
  auto base = base_t{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'};

  std::stringstream ss("cafe");

  auto bptr = std::make_shared<bignum_t>(ss, base);

  std::cout << '\n';

  bptr->print(std::cout, base);
  //
      auto factory = bistro::ASTFactory<bignum_t, base_t>{};
      auto num = factory(bptr);
      auto minus  = factory(num, bistro::OpType::MINUS);
      auto plus   = factory(num, minus, bistro::OpType::PLUS);
      plus->print_infix(std::cout, base) << '\n';
      plus->print_pol(std::cout, base) << '\n';
    //  plus->eval()->print(std::cout, base) << '\n';
}
