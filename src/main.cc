#include <iostream>
#include "ast-factory.hh"
#include "parse-driver.hh"
#include "bignum.hh"
#include "base.hh"



int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <file>\n";
        return 2;
    }
    try
    {
        bistro::parser::ParseDriver p(argv[1]);
        const auto ast = p.parse();
        ast->eval()->print(std::cout, p.get_base());
        std::cout << std::endl;
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
