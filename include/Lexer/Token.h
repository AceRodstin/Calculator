//
// Created by Ace Rodstin on 16 Nov 2022.
//

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H


#include <string>
#include <map>
#include <any>
#include <vector>
#include "../Ace.h"

using namespace std;

namespace Lexer {
	struct Token {
	public:
		enum Kind {
			keyword,
			identifier,
			punctuator,
			literal
		};

		Kind kind;
		any specifier;
		string value;

		Token(Kind kind, any specifier, string value);

		bool operator==(const Token &other) const;
		string description();

		optional<Ace::Keyword> to_keyword();
		optional<Ace::Punctuator> to_punctuator();
		optional<Ace::Literal> to_literal();

	private:
		string description(Kind kind);

		template<typename T>
		optional<T> kind_cast(Kind kind) {
			if (this->kind != kind) {
				return {};
			} else {
				return any_cast<T>(specifier);
			}
		}
	};
}


#endif //LEXER_TOKEN_H
