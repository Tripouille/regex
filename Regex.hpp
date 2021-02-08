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
        pattern(string const & v = "", size_t mi = 1, size_t ma = 1) : value(v), min(mi), max(ma) {}
        string value;
        ssize_t min, max;
        vector<struct pattern> sequence;
        vector<struct pattern> alternative;
    };

    public:
        Regex(string const & regex) throw (std::invalid_argument);
        ~Regex();
        void showPattern(vector<struct pattern> & p);

    private:
        Regex();
        Regex(Regex const & o);
        Regex & operator=(Regex const & o);
        void _extractPattern(string const & regex, size_t & i, struct pattern & parent) throw (std::invalid_argument);;
        void _extractParenthesis(string const & regex, size_t & i, struct pattern & parent) throw (std::invalid_argument);;
        void _setPatternMinMax(string const & regex, size_t & i, struct pattern & p);
        size_t _getParenthesisEnd(string const & regex, size_t & i) throw (std::invalid_argument);
        bool isEscaped(string const & regex, size_t i) const;

        vector<struct pattern> _roots;
};

#endif