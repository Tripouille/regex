#ifndef REGEX_HPP
# define REGEX_HPP
# include <sys/types.h>
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
        size_t min, max;
        vector<struct pattern> sequence;
        vector<struct pattern> alternative;
        bool isAlternative;
        bool isEscaped;
    };

    public:
        Regex(string const & regex) throw (std::invalid_argument);
        ~Regex();
        string getSource() const;
        bool match(string const & str) const;

    private:
        Regex();
        Regex(Regex const & o);
        Regex & operator=(Regex const & o);

        void _extractPattern(size_t & i, struct pattern & parent) throw (std::invalid_argument);
        void _handleParenthesis(size_t & i, struct pattern & parenthesis);
        void _handlePipe(size_t & i, struct pattern & pipe, struct pattern & parent);
        void _handleBracket(size_t & i, struct pattern & child);
        void _handleSequence(size_t & i, struct pattern & child, struct pattern & parent);
        void _handleCharacter(size_t & i, struct pattern & child);
        void _handleEscapeCharacter(size_t & i) const;
        void _setPatternMinMax(size_t & i, struct pattern & p);
        void _insertPattern(struct pattern & parent, struct pattern & child);

        bool isEscaped(size_t i) const;
        size_t _getParenthesisEnd(size_t i);
        size_t _getPipeEnd(size_t i);
        size_t _getCharacterEnd(size_t i);
        size_t _getSequenceEnd(size_t i);

        void _checkPipeValidity() const throw (std::invalid_argument);
        void _checkParenthesisValidity() const throw (std::invalid_argument);

        bool _matchSequence(string const & str, size_t & strPos, vector<struct pattern> const & sequence, size_t sequencePos) const;
        bool _matchPattern(string const & str, size_t & strPos, struct pattern const & pattern) const;
        bool _matchParenthesis(string const & str, size_t & strPos, struct pattern const & pattern) const;

        bool _isRealParenthesis(size_t i) const;
        bool _isRealPipe(size_t i) const;
        bool _isRealBracket(size_t i) const;
        //debug
        void showPattern(vector<struct pattern> & p, int x, bool isAlternative = false);

        /* Variables */
        struct pattern _root;
        string const _source;
};

#endif