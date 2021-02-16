#ifndef REGEX_HPP
# define REGEX_HPP
# include <sys/types.h>
# include <string>
# include <iostream>
# include <stdexcept>
# include <vector>
# include <sstream>
# include <climits>
# define UNLIMITED -1
# define STARTOFLINE "^"
# define ENDOFLINE "$"

using std::string;
using std::vector;

class Regex {



    struct pattern {
        pattern(string const & v = "default", size_t mi = 1, size_t ma = 1) : value(v), min(mi), max(ma), isAlternative(false), isEscaped(false) {}

        string value;
        size_t min, max;
        bool isAlternative;
        bool isEscaped;

        vector<struct pattern> sequence;
        vector<struct pattern> alternative;
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

        void _createSequence(size_t & i, struct pattern & parent) throw (std::invalid_argument);
        void _handleSequence(size_t & i, struct pattern & sequence, struct pattern & parent) throw (std::invalid_argument);
        void _handleParenthesis(size_t & i, struct pattern & sequence) throw (std::invalid_argument);
        void _handleBracket(size_t & i, struct pattern & sequence) throw (std::invalid_argument);
        void _handlePipe(size_t & i, struct pattern & sequence, struct pattern & parent) throw (std::invalid_argument);
        void _handleCharacter(size_t & i, struct pattern & sequence);
        void _handleEscapeCharacter(size_t & i) const;

        void _setPatternMinMax(size_t & i, struct pattern & p) throw (std::invalid_argument);
        void _insertSequence(struct pattern & sequence, struct pattern & parent);

        size_t _getParenthesisEnd(size_t i);
        size_t _getBracketEnd(size_t i);
        size_t _getPipeEnd(size_t i);
        size_t _getCharacterEnd(size_t i);
        size_t _getSequenceEnd(size_t i);

        void _checkPipeValidity() const throw (std::invalid_argument);
        void _checkParenthesisValidity() const throw (std::invalid_argument);
        void _checkDelimiterValidity() const throw (std::invalid_argument);

        bool _matchSequence(string const & str, size_t & strPos, vector<struct pattern> const & sequence, size_t sequencePos) const;
        bool _matchPattern(string const & str, size_t & strPos, struct pattern const & pattern) const;
        bool _matchCharacter(string const & str, size_t & strPos, struct pattern const & pattern) const;
        bool _matchBracket(string const & str, size_t & strPos, struct pattern const & pattern) const;

        bool _isEscaped(ssize_t i) const;
        bool _isRealOpeningParenthesis(size_t i) const;
        bool _isRealClosingParenthesis(size_t i) const;
        bool _isRealOpeningBracket(size_t i) const;
        bool _isRealClosingBracket(size_t i) const;
        bool _isRealPipe(size_t i) const;
        bool _isRealEscape(size_t i) const;
        bool _isQuantifier(size_t i) const throw(std::invalid_argument);
        bool _isRangeQuantifier(size_t i) const throw(std::invalid_argument);
        void _setRangeQuantifier(size_t & i, struct pattern & p) const;
        bool _isDigit(size_t i) const;
        //debug
        void showPattern(vector<struct pattern> & p, int x, bool isAlternative = false);

        /* Variables */
        struct pattern _root;
        string const _source;
};

#endif