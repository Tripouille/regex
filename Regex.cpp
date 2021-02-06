#include "Regex.hpp"

Regex::Regex(string const & pattern) throw (std::invalid_argument)
	  : _pattern(pattern) {

}

Regex::~Regex() {

}