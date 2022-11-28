//
// Created by Ace Rodstin on 16 Nov 2022.
//

#include "../../include/Lexer/Parser.h"
#include "../../include/lib/StringManager.h"
#include "../../include/Literals/Parser.h"
#include <any>

using namespace Lexer;

vector<Token> Parser::parse(const string &source_code) {
	vector<Token> tokens;

	StringManager string_manager;
	auto predicate = [](char c) { return isspace(c); };
	auto split_by_space = string_manager.split(source_code, predicate);
	vector<string> components;

	for (auto component : split_by_space) {
		auto predicate = [](char c) {
			auto str = string(1, c);
			return Ace::punctuators.contains(str);
		};

		auto split_by_punctuator = string_manager.split(component, predicate, true);

		for (auto subcomponent : split_by_punctuator) {
			components.push_back(subcomponent);
		}
	}

	for (auto component : components) {
		Token token = create_token(component);
		tokens.push_back(token);
	}

	return tokens;
}

Token Parser::create_token(string lexem) {
	Token::Kind kind;
	any specifier;

	if (Ace::keywords.contains(lexem)) {
		kind = Token::Kind::keyword;
		auto keyword = Ace::keywords[lexem];
		specifier = keyword.value();
	} else if (Ace::punctuators.contains(lexem)) {
		kind = Token::Kind::punctuator;
		auto punctuator = Ace::punctuators[lexem];
		specifier = punctuator.value();
	} else if (is_literal(lexem)) {
		kind = Token::Kind::literal;
		auto literal = parse_literal(lexem);
		specifier = literal.value();
	} else if (is_identifier(lexem)) {
		kind = Token::Kind::identifier;
		auto identifier = parse_identifier(lexem);
		specifier = "";
	}

	return { kind, specifier, lexem };
}

bool Parser::is_literal(string lexem) {
	Literals::Parser parser;
	return parser.is_literal(lexem);
}

bool Parser::is_identifier(string lexem) {
	// TODO: check identifier grammar
	return true;
}

optional<Ace::Literal> Parser::parse_literal(string lexem) {
	Literals::Parser parser;
	return parser.parse(lexem);
}

optional<string> Parser::parse_identifier(string lexem) {
	return lexem;
}