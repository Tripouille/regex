#include "Regex.hpp"

int main(void)
{
    Regex r("bs*c?e");
    string str("astbcce");
    std::cout << r.getSource() << " match " << str << " ? " << std::boolalpha << r.match(str) << std::endl;
    return (0);
}

/*




*/
