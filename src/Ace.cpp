//
// Created by Ace Rodstin on 16 Nov 2022.
//

#include "../include/Ace.h"

map<string, Ace::FileType> Ace::file_extensions {
		{ ".ace", FileType::source_code }
};

Dictionary<string, Ace::Keyword> Ace::keywords {
		{ "val", Keyword::constant },
		{ "var", Keyword::variable },
};

Dictionary<string, Ace::Punctuator> Ace::punctuators {
		{ ":", Punctuator::colon },
		{ "(", Punctuator::opening_parenthesis },
		{ ")", Punctuator::closing_parenthesis },
		{ "=", Punctuator::equal },
		{ "!", Punctuator::exclamation_point },
		{ "+", Punctuator::plus },
		{ "-", Punctuator::minus },
		{ "*", Punctuator::asterisk },
		{ "/", Punctuator::slash },
};

vector<string> Ace::boolean_literals {
		"false",
		"true"
};

optional<Ace::Operator> Ace::define_operator(Punctuator punctuator) {
	switch (punctuator) {
		case Ace::Punctuator::plus:
			return Ace::Operator::addition;
		case Ace::Punctuator::minus:
			return Ace::Operator::subtraction;
		case Ace::Punctuator::asterisk:
			return Ace::Operator::multiplication;
		case Ace::Punctuator::slash:
			return Ace::Operator::division;
		default:
			return {};
	}
}

string Ace::description(Keyword keyword) {
	switch (keyword) {
		case Keyword::constant:
			return "constant";
		case Keyword::variable:
			return "variable";
	}
}

string Ace::description(Punctuator punctuator) {
	switch (punctuator) {
		case Punctuator::colon:
			return "colon";
		case Punctuator::opening_parenthesis:
			return "opening parenthesis";
		case Punctuator::closing_parenthesis:
			return "closing parenthesis";
		case Punctuator::equal:
			return "equal";
		case Punctuator::exclamation_point:
			return "exclamation point";
		case Punctuator::plus:
			return "plus";
		case Punctuator::minus:
			return "minus";
		case Punctuator::asterisk:
			return "asterisk";
		case Punctuator::slash:
			return "slash";
	}
}

string Ace::description(Literal literal) {
	switch (literal) {
		case Literal::integer:
			return "integer";
		case Literal::_double:
			return "double";
		case Literal::character:
			return "character";
		case Literal::_string:
			return "string";
		case Literal::boolean:
			return "boolean";
	}
}