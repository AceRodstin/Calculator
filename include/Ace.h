//
// Created by Ace Rodstin on 16 Nov 2022.
//

#ifndef LEXER_ACE_H
#define LEXER_ACE_H


#include <map>
#include <string>
#include <vector>
#include "lib/Dictionary.h"

using namespace std;

struct Ace {
	enum class FileType {
		source_code
	};

	enum Keyword {
		constant,
		variable
	};

	enum Punctuator {
		colon,
		opening_parenthesis,
		closing_parenthesis,
		equal,
		exclamation_point,
		plus,
		minus,
		asterisk,
		slash
	};

	enum Literal {
		_string,
		integer,
		_double,
		character,
		boolean
	};

	enum Operator {
		addition,
		subtraction,
		multiplication,
		division
	};

	static map<string, FileType> file_extensions;
	static Dictionary<string, Keyword> keywords;
	static Dictionary<string, Punctuator> punctuators;
	static vector<string> boolean_literals;

	static optional<Ace::Operator> define_operator(Punctuator punctuator);

	static string description(Keyword);
	static string description(Punctuator);
	static string description(Literal);
};


#endif //LEXER_ACE_H
