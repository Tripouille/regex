#include "Regex.hpp"

int main(void)
{
    Regex r("a\\\\b"); 
    string str("a\\b");
    std::cout << r.getSource() << " match " << str << " ? " << std::boolalpha << r.match(str) << std::endl;
    return (0);
}

/*


a faire in is parenthesis pour la fin de la sequence


*/
