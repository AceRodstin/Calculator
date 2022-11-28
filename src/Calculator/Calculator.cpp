//
// Created by Ace Rodstin on 11/25/22.
//

#include "../../include/Calculator/Calculator.h"

string Calculator::calculate(string expression) {
	Lexer::Parser lexer_parser;
	auto lexer_tokens = lexer_parser.parse(expression);

	Expression::Parser expression_parser;
	auto grammar_tree = expression_parser.parse(lexer_tokens);

	Interpretator interpretator;
	auto result = interpretator.calculate(grammar_tree);

	StringManager string_manager;
	return expression + " = " + string_manager.to_string(result, 2);
}