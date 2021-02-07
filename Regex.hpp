#ifndef REGEX_HPP
# define REGEX_HPP
# include <string>
# include <iostream>
# include <stdexcept>
# include <vector>
# define UNLIMITED -1

using std::string;
using std::vector;

class Regex {

    struct pattern {
        pattern(string const & v, size_t mi, size_t ma) : value(v), min(mi), max(ma) {}
        string value;
        ssize_t min = 1, max = 1;
    };

    public:
        Regex(string const * regex) throw (std::invalid_argument);
        ~Regex();

    private:
        Regex();
        Regex(Regex const & o);
        Regex & operator=(Regex const & o);
        bool _extractPattern(char const *& regex,
					vector<struct pattern> & v);
        
        vector< vector<struct pattern> > _patterns;
};

#endif