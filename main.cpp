#include "Regex.hpp"

int main(void)
{
    Regex r("s?a");
    string str("a");
    std::cout << r.getSource() << " match " << str << " ? " << std::boolalpha << r.match(str) << std::endl;
    return (0);
}

/*




*/