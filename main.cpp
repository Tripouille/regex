#include "Regex.hpp"

int main(void)
{
    Regex r("a(b(c|o)d?)|(efg)"); 
    string str("There efgabore two needles in this needle haystack");
    std::cout << r.getSource() << " match " << str << " ? " << std::boolalpha << r.match(str) << std::endl;
    return (0);
}

/*


a faire in is parenthesis pour la fin de la sequence


*/
