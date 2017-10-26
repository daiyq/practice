#ifndef PARSE_H_
#define PARSE_H_

#include "nfa.h"

enum class RegexType {
	MATCH, NOT_MATCH, REGEX_IS_OK,
	REGEX_MISSING_PARENTNESS, REGEX_MISSING_SQUARE_BRACKETS,
	REGEX_EMPTY_SQUARE_BRACKETS
};

//parseing regex(legal or illegal)
static void parse_regex(std::string regex);

static void regex(const std::string& regex, const std::string& text);
#endif 
