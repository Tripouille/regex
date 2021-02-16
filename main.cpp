#include "Regex.hpp"

int main(void)
{
    Regex r("\\^bc\\[$."); 
    string str("^bc[");
    std::cout << r.getSource() << " match " << str << " ? " << std::boolalpha << r.match(str) << std::endl;
    return (0);
}

/*


a faire in is parenthesis pour la fin de la sequence


*/
