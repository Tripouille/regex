#include "Regex.hpp"

Regex::Regex(string const * regex) throw (std::invalid_argument) {
	vector<struct pattern> v;
	size_t i = 0;
	while (regex[i])
	{
		if (!_extractPattern(regex, i, v))
			throw std::invalid_argument(regex);
		_patterns.push_back(v);
	}
}

Regex::~Regex() {

}

bool Regex::_extractPattern(char const * regex, size_t & i
					vector<struct pattern> & v) {
	struct pattern p;

	if (regex[i] == '.')
	{
		p.value = ".";
		++i;
	}
	else if (regex[i] == '[')
	{
		size_t closingBracketPos = regex.find('[', i + 1);
		for (int c = 0; regex[c] && regex[c] != ']'; ++i);
		if (closingBracketPos == string::npos)
			return (false);
		p.value = string(regex, 0, closingBracketPos + 1);
		i = closingBracketPos + 1;
	}
	else
	{

	}
	_setPatternMinMax(regex, p);
	v.push_back(p);
	return (true);
}

void Regex::_setPatternMinMax(string const & regex, size_t & i
							 struct pattern & p) {
	if (regex[i] == '*')
		{p.min = 0, p.max = UNLIMITED;}
	else if (regex[i] == '+')
		{p.min = 1, p.max = UNLIMITED;}
	else if (regex[i] == '?')
		{p.min = 0, p.max = 1;}
	else
		return ;
	++i;
}
