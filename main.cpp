#include "Regex.hpp"

int main(void)
{
    Regex r("a.+\\.php"); 
    string str("fsfsafas.php");
    std::cout << r.getSource() << " match " << str << " ? " << std::boolalpha << r.match(str) << " last match = " << r.getLastMatch() << std::endl;
    return (0);
}

/*


handle les bracket caca avec des erreurs



*/