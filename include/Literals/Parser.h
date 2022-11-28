//
// Created by Ace Rodstin on 16 Nov 2022.
//

#ifndef PARSELITERAL_LITERALSPARSER_H
#define PARSELITERAL_LITERALSPARSER_H


#include <string>
#include <optional>
#include "../Ace.h"

using namespace std;

namespace Literals {
	class Parser {
	public:
		optional<Ace::Literal> parse(string str);
		bool is_literal(string str);

	private:
		bool is_integer_literal(string str);
		bool is_double_literal(string str);
		bool is_string_literal(string str);
		bool is_character_literal(string str);
		bool is_boolean_literal(string str);
	};
}


#endif //PARSELITERAL_LITERALSPARSER_H
