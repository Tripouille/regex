#include "Regex.hpp"

Regex::Regex(string const & regex) throw (std::invalid_argument) {
	size_t i = 0;
	while (regex[i])
	{
		struct pattern parent("ROOT");
		_extractPattern(regex, i, parent);
		_patterns.push_back(parent);
	}
}

Regex::~Regex() {
    showPattern(_patterns);
}

void Regex::_extractPattern(string const & regex, size_t & i, struct pattern & parent) throw (std::invalid_argument) {
	struct pattern child;

	if (regex[i] == '.')
	{
		child.value = ".";
		++i;
	}
	else if (regex[i] == '[')
	{
		size_t closingBracketPos = regex.find(']', i + 1);
		std::cout << "exrtact bracket start = " << i << " end = " << closingBracketPos << std::endl;
		if (closingBracketPos == string::npos)
			throw std::invalid_argument(regex);
		child.value = string(regex, i, closingBracketPos - i + 1);
		i = closingBracketPos + 1;
	}
	else if (regex[i] == '(')
	{
		std::cout << "parenthesis detected " << i << std::endl;
		_extractParenthesis(regex, i, parent);
		_setPatternMinMax(regex, i, parent);
		return ;
	}
	_setPatternMinMax(regex, i, child);
	parent.sequence.push_back(child);
}

void Regex::_extractParenthesis(string const & regex, size_t & i, struct pattern & parent) throw (std::invalid_argument) {
	size_t parenthesisEnd = _getParenthesisEnd(regex, i);
	std::cout << "parenthesisStart = " << i << " parenthesisEnd = " << parenthesisEnd << std::endl;
	++i;
	while (i < parenthesisEnd)
	{
		std::cout << "extract parenthesis i debut = " << regex[i] << std::endl;
		_extractPattern(regex, i , parent);
		std::cout << "extract parenthesis i fin = " << regex[i] << std::endl;
	}
	i = parenthesisEnd + 1;
}

size_t Regex::_getParenthesisEnd(string const & regex, size_t & i) throw (std::invalid_argument) {
	size_t end = i;
	size_t parenthesisCount = 0;

	do
	{
		if (regex[end] == '(')
			++parenthesisCount;
		else if (regex[end] == ')')
			--parenthesisCount;
	} while (parenthesisCount && regex[++end]);
	if (parenthesisCount)
		throw std::invalid_argument(regex);
	return (end);
}

void Regex::_setPatternMinMax(string const & regex, size_t & i, struct pattern & p) {
	if (regex[i] == '*')
		{p.min = 0, p.max = UNLIMITED;}
	else if (regex[i] == '+')
		{p.min = 1, p.max = UNLIMITED;}
	else if (regex[i] == '?')
		{p.min = 0, p.max = 1;}
	else
	{
		//std::cout << "_setPattern not found" << std::endl;
		return ;
	}
	++i;
}

void Regex::showPattern(vector<struct pattern> & p) {
	for (size_t i = 0; i < p.size(); ++i)
	{
		std::cout << "actual sequence i = " << i << std::endl;
		std::cout << "pattern value = " << p[i].value << " min = " << p[i].min << " max = " << p[i].max << std::endl;
		if (p[i].sequence.size())
		{
			std::cout << "rest of sequence:" << std::endl;
			showPattern(p[i].sequence);
		}
		if (p[i].alternative.size())
		{
			std::cout << "alternative sequence:" << std::endl;
			showPattern(p[i].alternative);
		}
	}
}