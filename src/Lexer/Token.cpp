//
// Created by Ace Rodstin on 16 Nov 2022.
//

#include "../../include/Lexer/Token.h"
#include "../../include/Ace.h"

using namespace Lexer;

Token::Token(Kind kind, any specifier, string value) {
	this->kind = kind;
	this->specifier = specifier;
	this->value = move(value);
}

bool Token::operator==(const Token &other) const {
	bool is_kind_equal = kind == other.kind;
	bool is_specifier_equal;
	bool is_value_equal = value == other.value;

	switch (kind) {
		case Kind::keyword: {
			auto lhs = any_cast<Ace::Keyword>(specifier);
			auto rhs = any_cast<Ace::Keyword>(other.specifier);
			is_specifier_equal = lhs == rhs;
			break;
		}
		case Kind::punctuator: {
			auto lhs = any_cast<Ace::Punctuator>(specifier);
			auto rhs = any_cast<Ace::Punctuator>(other.specifier);
			is_specifier_equal = lhs == rhs;
			break;
		}
		case Kind::literal: {
			auto lhs = any_cast<Ace::Literal>(specifier);
			auto rhs = any_cast<Ace::Literal>(other.specifier);
			is_specifier_equal = lhs == rhs;
			break;
		}
		case Kind::identifier: {
			is_specifier_equal = is_value_equal;
			break;
		}
	}

	return is_kind_equal && is_specifier_equal && is_value_equal;
}

string Token::description() {
	string kind_description = description(kind);
	string specifier_description;

	switch (kind) {
		case Kind::keyword: {
			auto keyword = any_cast<Ace::Keyword>(specifier);
			specifier_description = Ace::description(keyword);
			break;
		}
		case Kind::punctuator: {
			auto punctuator = any_cast<Ace::Punctuator>(specifier);
			specifier_description = Ace::description(punctuator);
			break;
		}
		case Kind::literal: {
			auto literal = any_cast<Ace::Literal>(specifier);
			specifier_description = Ace::description(literal);
			break;
		}
		case Kind::identifier:
			specifier_description = "";
			break;
	}

	return  "Kind: " + kind_description + ", " + "Specifier: " + specifier_description + ", " + "Value: " + value;
}

optional<Ace::Keyword> Token::to_keyword() {
	return kind_cast<Ace::Keyword>(Kind::keyword);
}

optional<Ace::Punctuator> Token::to_punctuator() {
	return kind_cast<Ace::Punctuator>(Kind::punctuator);
}

optional<Ace::Literal> Token::to_literal() {
	return kind_cast<Ace::Literal>(Kind::literal);
}

string Token::description(Kind kind) {
	switch (kind) {
		case Kind::keyword:
			return "keyword";
		case Kind::punctuator:
			return "punctuator";
		case Kind::literal:
			return "literal";
		case Kind::identifier:
			return "identifier";
	}
}