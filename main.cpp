#include "Regex.hpp"

int main(void)
{
    Regex r("\\b");
    string str("salut");
    std::cout << r.getSource() << " match " << str << " ? " << r.match(str) << std::endl;
    return (0);
}

/*




*/