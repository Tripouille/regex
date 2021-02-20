#include "Regex.hpp"

int main(void)
{
    Regex r("((((((((.+\\.php))))))))?.+\\.php$"); 
    string str("coucou.php");
    std::cout << r.getSource() << " match " << str << " ? " << std::boolalpha << r.match(str) << " last match = " << r.getLastMatch() << std::endl;
    return (0);
}
