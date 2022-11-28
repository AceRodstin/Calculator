//
// Created by Ace Rodstin on 16 Nov 2022.
//

#include "../../include/Literals/Parser.h"
#include "../../include/lib/StringManager.h"
#include <algorithm>

using namespace Literals;

optional<Ace::Literal> Parser::parse(string str) {
	if (is_boolean_literal(str)) {
		return Ace::Literal::boolean;
	} else if (is_character_literal(str)) {
		return Ace::Literal::character;
	} else if (is_string_literal(str)) {
		return Ace::Literal::_string;
	} else if (is_double_literal(str)) {
		return Ace::Literal::_double;
	} else if (is_integer_literal(str)) {
		return Ace::Literal::integer;
	} else {
		return {};
	}
}

bool Parser::is_literal(string str) {
	return is_boolean_literal(str)
	|| is_character_literal(str)
	|| is_string_literal(str)
	|| is_double_literal(str)
	|| is_integer_literal(str);
}

bool Parser::is_integer_literal(string str) {
	bool is_integer = true;

	for (auto character : str) {
		if (!isdigit(character)) {
			is_integer = false;
			break;
		}
	}

	return is_integer;
}

bool Parser::is_double_literal(string str) {
	bool is_double = true;
	bool has_dot = false;

	for (auto character : str) {
		if (isdigit(character)) {
			continue;
		}

		if (character == '.') {
			if (has_dot) {
				is_double = false;
				break;
			} else {
				has_dot = true;
			}
		} else {
			is_double = false;
			break;
		}
	}

	return is_double && has_dot;
}

bool Parser::is_string_literal(string str) {
	if (str.empty()) {
		return false;
	}

	char quote = '\"';
	bool is_first_quote = str[0] == quote;
	bool is_last_quote = str[str.size() - 1] == quote;

	return is_first_quote && is_last_quote;
}

bool Parser::is_character_literal(string str) {
	if (str.empty()) {
		return false;
	}

	char quote = '\"';
	bool is_first_quote = str[0] == quote;
	bool is_last_quote = str[str.size() - 1] == quote;

	StringManager string_manager;
	auto predicate = [&](char c) { return c == quote; };
	string trimmed = string_manager.trim(str, predicate);
	bool is_one_character = trimmed.size() == 1;

	return is_first_quote && is_last_quote && is_one_character;
}

bool Parser::is_boolean_literal(string str) {
	auto literals = Ace::boolean_literals;
	auto iterator = std::find(literals.begin(), literals.end(), str);
	return iterator != literals.end();
}