//
// Created by Ace Rodstin on 16 Nov 2022.
//

#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H


#include <optional>
#include "Token.h"
#include "../Ace.h"

using namespace std;

namespace Lexer {
	class Parser {
	public:
		vector<Token> parse(const string &source_code);

	private:
		Token create_token(string lexem);
		bool is_literal(string lexem);
		bool is_identifier(string lexem);
		optional<Ace::Literal> parse_literal(string lexem);
		optional<string> parse_identifier(string lexem);
	};
}


#endif //LEXER_PARSER_H
