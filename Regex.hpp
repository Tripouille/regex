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
        pattern(string const & v = "ROOT", size_t mi = 1, size_t ma = 1) : value(v), min(mi), max(ma), isAlternative(false), isEscaped(false) {}
        string value;
        ssize_t min, max;
        vector<struct pattern> sequence;
        vector<struct pattern> alternative;
        bool isAlternative;
        bool isEscaped;
    };

    public:
        Regex(string const & regex) throw (std::invalid_argument);
        ~Regex();
        void showPattern(vector<struct pattern> & p, int x, bool isAlternative = false);

    private:
        Regex();
        Regex(Regex const & o);
        Regex & operator=(Regex const & o);

        void _extractPattern(size_t & i, struct pattern & parent) throw (std::invalid_argument);
        void _handleParenthesis(size_t & i, struct pattern & parenthesis);
        void _handlePipe(size_t & i, struct pattern & pipe, struct pattern & parent);
        void _handleBracket(size_t & i, struct pattern & child);
        void _handleCharacter(size_t & i, struct pattern & child);
        void _insertPattern(struct pattern & parent, struct pattern & child);


        void _setPatternMinMax(size_t & i, struct pattern & p);

        size_t _getParenthesisEnd(size_t i) throw (std::invalid_argument);
        size_t _getPipeEnd(size_t i) throw (std::invalid_argument);
        bool isEscaped(size_t i) const;

        void _checkPipeValidity() const throw (std::invalid_argument);
        void _checkParenthesisValidity() const throw (std::invalid_argument);

        struct pattern _root;
        string _source;
};

#endif