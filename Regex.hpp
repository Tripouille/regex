#ifndef REGEX_HPP
# define REGEX_HPP
# include <string>
# include <stdexcept>

using std::string;

class Regex {

    public:
        Regex(string const & pattern) throw (std::invalid_argument);
        ~Regex();

    private:
        Regex();
        Regex(Regex const & o);
        Regex & operator=(Regex const & o);
        
        string _pattern;
};

#endif