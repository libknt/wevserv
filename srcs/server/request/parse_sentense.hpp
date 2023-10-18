#ifndef	PARSE_SENTENSE_HPP
#define	PARSE_SENTENSE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <string>

enum TokenKind
{
	STRING,
	KEYWORD,
	SPACE,
};

struct Token
{
	TokenKind	token_kind;
	std::string	str;
};
ssize_t	parse_sentense(std::string line, std::string format, std::vector<std::string> &ans);
#endif