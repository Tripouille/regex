#include "Regex.hpp"

Regex::Regex(string const & regex) throw (std::invalid_argument) : _source(regex) {
	if (regex.size() == 0)
		throw std::invalid_argument("Regex can't be empty");
	_checkPipeValidity();
	_checkParenthesisValidity();
	size_t i = 0;
	while (_source[i])
		_extractPattern(i, _root);
}

Regex::~Regex() {
    //showPattern(_root.sequence, 1);
}

/* Public */

string Regex::getSource() const {
	return (_source);
}

bool Regex::match(string const & str) const {
	size_t pos = 0;
	size_t testedPos = 0;
	size_t limit = str.size();
	
	for (; pos < limit; ++pos)
	{
		testedPos = pos;
		std::cout << std::endl << ">>>>>>>>>> TestedPos = " << pos << " <<<<<<<<<<<<<<" << std::endl;
		if (_matchSequence(str, testedPos, _root.sequence, 0))
			return (true);
	}
	return (false);
}

/* Private */

bool Regex::_matchSequence(string const & str, size_t & strPos, vector<struct pattern> const & sequence, size_t sequencePos) const {
	size_t alternativeSize;
	size_t iAlternative;
	size_t strPosSave = strPos;
	
	std::cout << "Actual sequencePos = " << sequencePos << " Actual strPos = " << strPos <<  std::endl;
	if (sequencePos == sequence.size())
		return (true);
	for (size_t repeat = 0; repeat < sequence[sequencePos].max; ++repeat)
	{
		if (_matchPattern(str, strPos, sequence[sequencePos]))
		{
			std::cout << sequence[sequencePos].value << " match ! repeat = " << repeat << std::endl;
			if (_matchSequence(str, strPos, sequence, sequencePos + 1) == true)
				return (true);
		}
		else
		{
			strPos = strPosSave;
			iAlternative = 0;
			alternativeSize = sequence[sequencePos].alternative.size();
			std::cout << sequence[sequencePos].value << " miss match / alternative = " << alternativeSize << std::endl;
			for (; iAlternative < alternativeSize && !_matchPattern(str, strPos, sequence[sequencePos].alternative[iAlternative]); ++iAlternative);
			//std::cout << "iAlternative = " << iAlternative << "  alternativeSize = " << alternativeSize << std::endl;
			if ((iAlternative < alternativeSize || sequence[sequencePos].min == 0)
			&& _matchSequence(str, strPos, sequence, sequencePos + 1) == true)
				return (true);
			else
				return (false);
		}
	}
	return (false);
}

bool Regex::_matchPattern(string const & str, size_t & strPos, struct pattern const & pattern) const {
	//std::cout << pattern.value << " in matchPattern / sequence size = " << pattern.sequence.size() << std::endl;
	if (pattern.sequence.size() != 0)
		return (_matchSequence(str, strPos, pattern.sequence, 0));
	if (pattern.isEscaped || string("(|[").find(pattern.value[0]) == string::npos)
	{
		if (pattern.value[0] == str[strPos])
		{
			++strPos;
			return (true);
		}
		return (false);
	}
	return (false);
}

bool Regex::_matchParenthesis(string const & str, size_t & strPos, struct pattern const & pattern) const {
	return (str.size() == strPos && pattern.isAlternative);
}


void Regex::_extractPattern(size_t & i, struct pattern & parent) throw (std::invalid_argument) {
	struct pattern child;

	if (_source[i] == '\\' && !isEscaped(i))
		return (_handleEscapeCharacter(i));
	else
		_handleSequence(i, child, parent);

	_setPatternMinMax(i, child);
	_insertPattern(parent, child);
}

void Regex::_handleParenthesis(size_t & i, struct pattern & parenthesis) {
	parenthesis.value = "Parenthesis";
	size_t parenthesisEnd = _getParenthesisEnd(i);
	++i;
	while (i < parenthesisEnd)
		_extractPattern(i , parenthesis);
	++i;
}

void Regex::_handlePipe(size_t & i, struct pattern & pipe, struct pattern & parent) {
	pipe.value = "Pipe";
	parent.isAlternative = true;
	size_t pipeEnd = _getPipeEnd(i);
	++i;
	while (i < pipeEnd)
		_extractPattern(i , pipe);
}

void Regex::_handleBracket(size_t & i, struct pattern & child) {
	size_t closingBracketPos = _source.find(']', i + 1);
	if (closingBracketPos == string::npos)
		throw std::invalid_argument("Regex missing ]");
	else if (closingBracketPos == i + 1)
		throw std::invalid_argument("Regex bracket can't be empty");
	child.value = string(_source, i, closingBracketPos - i + 1);
	i = closingBracketPos + 1;
}

void Regex::_handleSequence(size_t & i, struct pattern & child, struct pattern & parent) {
	child.value = "Sequence";
	size_t sequenceEnd = _getSequenceEnd(i);
	while (i < sequenceEnd)
	{
		if (_source[i] == '(' && !isEscaped(i))
			_handleParenthesis(i, child);
		else if (_source[i] == '|' && !isEscaped(i))
			_handlePipe(i, child, parent);
		else if (_source[i] == '[' && !isEscaped(i))
			_handleBracket(i, child);
		else
			_handleCharacter(i , child);
	}
}

void Regex::_handleCharacter(size_t & i, struct pattern & child) {
	struct pattern characters("character");

	size_t characterEnd = _getCharacterEnd(i);
	while (i < characterEnd)
	{
		struct pattern actualChar;

		actualChar.value = _source[i];
		actualChar.isEscaped = isEscaped(i);
		++i;
		characters.sequence.push_back(actualChar);
	}
	child.sequence.push_back(characters);
}

void Regex::_handleEscapeCharacter(size_t & i) const {
	++i;
}

void Regex::_insertPattern(struct pattern & parent, struct pattern & child) {
	if (parent.isAlternative)
		parent.sequence.back().alternative.push_back(child);
	else
		parent.sequence.push_back(child);
}

size_t Regex::_getParenthesisEnd(size_t i) {
	size_t end = i;
	ssize_t parenthesisCount = 0;

	do
	{
		if (_source[end] == '(' && !isEscaped(end))
			++parenthesisCount;
		else if (_source[end] == ')' && !isEscaped(end))
			--parenthesisCount;
	} while (parenthesisCount > 0 && _source[++end]);
	return (end);
}

size_t Regex::_getPipeEnd(size_t i) {

	while(_source[++i])
	{
		if (_source[i] == '(' && !isEscaped(i))
			i = _getParenthesisEnd(i);
		else if (!isEscaped(i) && (_source[i] == '|' || _source[i] == ')'))
			return (i);
	}
	return (i);
}

size_t Regex::_getSequenceEnd(size_t i) {

	while(_source[++i] && !_isRealPipe(i));
	return (i);
}

size_t Regex::_getCharacterEnd(size_t i) {

	while(_source[++i] && !_isRealPipe(i) && !_isRealParenthesis(i) && !_isRealBracket(i));
	return (i);
}

void Regex::_setPatternMinMax(size_t & i, struct pattern & p) {
	if (_source[i] == '*' && !isEscaped(i))
		{p.min = 0; p.max = UNLIMITED;}
	else if (_source[i] == '+' && !isEscaped(i))
		{p.min = 1; p.max = UNLIMITED;}
	else if (_source[i] == '?' && !isEscaped(i))
		{p.min = 0; p.max = 1;}
	else
	{
		//std::cout << "_setPattern not found" << std::endl;
		return ;
	}
	++i;
}

bool Regex::isEscaped(size_t i) const {
	size_t count = 0;
	while (--i >= 0 && _source[i] == '\\')
		++count;
	return (count % 2);
}

void Regex::showPattern(vector<struct pattern> & p, int x, bool isAlternative) {
	for (size_t i = 0; i < p.size(); ++i)
	{
		if (isAlternative)
			std::cout << "IS ALTERNATIVE " << std::endl;
		std::cout << "prof = " << x << " actual sequence i = " << i << std::endl;
		std::cout << "pattern value = " << p[i].value << " min = " << p[i].min << " max = " << p[i].max << std::endl;
		std::cout << "pattern sequence size = " << p[i].sequence.size() <<  "  pattern alternative size = " << p[i].alternative.size() << std::endl;
		if (p[i].sequence.size())
		{
			std::cout << "rest of sequence:" << std::endl;
			showPattern(p[i].sequence, x + 1);
		}
		if (p[i].alternative.size())
		{
			std::cout << "alternative sequence:" << std::endl;
			showPattern(p[i].alternative, x + 1, true);
		}
	}
}

void Regex::_checkPipeValidity() const throw (std::invalid_argument) {
	if (_source[0] == '|' || _source[_source.size() - 1] == '|')
		throw std::invalid_argument("Regex pipe error");
	size_t size = _source.size();
	for (size_t i = 1; i < size; ++i)
		if (!isEscaped(i) && !isEscaped(i - 1)
		&& _source[i] == '|' && _source[i - 1] == '|')
			throw std::invalid_argument("Regex pipe error");
}

void Regex::_checkParenthesisValidity() const throw (std::invalid_argument) {
	ssize_t parenthesisCount = 0;

	size_t size = _source.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (_source[i] == '(' && !isEscaped(i))
			++parenthesisCount;
		else if (_source[i] == ')' && !isEscaped(i))
			--parenthesisCount;
		if (parenthesisCount < 0)
			throw std::invalid_argument("Regex parenthesis error");
	}
	if (parenthesisCount != 0)
		throw std::invalid_argument("Regex parenthesis error");
}

bool Regex::_isRealParenthesis(size_t i) const {
	return (_source[i] == '(' && !isEscaped(i));
}

bool Regex::_isRealPipe(size_t i) const {
	return (_source[i] == '|' && !isEscaped(i));
}

bool Regex::_isRealBracket(size_t i) const {
	return (_source[i] == '[' && !isEscaped(i));
}