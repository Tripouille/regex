#include "Regex.hpp"

int main(void)
{
    Regex r("ed[q]|e");
    string str("e");
    std::cout << r.getSource() << " match " << str << " ? " << std::boolalpha << r.match(str) << std::endl;
    return (0);
}

/*




*/
