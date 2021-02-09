#include "Regex.hpp"

Regex::Regex(string const & regex) throw (std::invalid_argument) {
	size_t i = 0;
	while (regex[i])
		_extractPattern(regex, i, _root);
}

Regex::~Regex() {
    showPattern(_root.sequence, 1);
}

void Regex::_extractPattern(string const & regex, size_t & i, struct pattern & parent) throw (std::invalid_argument) {
	struct pattern child;

	if (regex[i] == '|')
	{
		parent.isAlternative = true; ++i;
		return ;
	}
	else if (regex[i] == '.')
	{
		child.value = "."; ++i;
	}
	else if (regex[i] == '[')
	{
		size_t closingBracketPos = regex.find(']', i + 1);
		if (closingBracketPos == string::npos)
			throw std::invalid_argument(regex);
		child.value = string(regex, i, closingBracketPos - i + 1);
		i = closingBracketPos + 1;
	}
	else if (regex[i] == '(')
	{
		child.value = "Parenthesis";
		size_t parenthesisEnd = _getParenthesisEnd(regex, i);
		++i;
		while (i < parenthesisEnd)
			_extractPattern(regex, i , child);
		i = parenthesisEnd + 1;
	}
	else
	{
		child.value = regex[i]; ++i;
	}
	/* Set min and max and add the pattern */
	_setPatternMinMax(regex, i, child);
	if (parent.isAlternative)
		parent.sequence.back().alternative.push_back(child);
	else
		parent.sequence.push_back(child);
}

size_t Regex::_getParenthesisEnd(string const & regex, size_t & i) throw (std::invalid_argument) {
	size_t end = i;
	size_t parenthesisCount = 0;

	do
	{
		if (regex[end] == '(' && !isEscaped(regex, end))
			++parenthesisCount;
		else if (regex[end] == ')' && !isEscaped(regex, end))
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

void Regex::showPattern(vector<struct pattern> & p, int x) {
	for (size_t i = 0; i < p.size(); ++i)
	{
		std::cout << "prof = " << x << " actual sequence i = " << i << std::endl;
		std::cout << "pattern value = " << p[i].value << " min = " << p[i].min << " max = " << p[i].max << std::endl;
		if (p[i].sequence.size())
		{
			std::cout << "rest of sequence:" << std::endl;
			showPattern(p[i].sequence, x + 1);
		}
		if (p[i].alternative.size())
		{
			std::cout << "alternative sequence:" << std::endl;
			showPattern(p[i].alternative, x + 1);
		}
	}
}

bool Regex::isEscaped(string const & regex, size_t i) const {
	size_t count = 0;
	while (--i >= 0 && regex[i] == '\\')
		++count;
	return (count % 2);
}