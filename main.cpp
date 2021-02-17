#include "Regex.hpp"

int main(void)
{
    Regex r("[--z]$"); 
    string str("A");
    std::cout << r.getSource() << " match " << str << " ? " << std::boolalpha << r.match(str) << std::endl;
    return (0);
}

/*


handle les bracket caca avec des erreurs



*/