//
// Created by Ace Rodstin on 22 Nov 2022.
//

#include "../../include/Expression/Parser.h"
#include <iterator>
#include <set>

using namespace Expression;

Parser::Error::Error(Reason reason): reason(reason) {}

const char *Parser::Error::what() const noexcept {
	switch (reason) {
		case Error::Reason::invalid_parenthesis:
			return "invalid parenthesis";
		case Error::Reason::invalid_operand:
			return "invalid literal";
		case Error::Reason::invalid_operator:
			return "invalid operator";
	}
}

Node* Parser::parse(vector<Lexer::Token> &tokens) {
	Buffer buffer { tokens };

	if (!is_parenthesis_correct(buffer)) {
		throw Error { Error::Reason::invalid_parenthesis };
	}

	if (!is_operands_correct(buffer)) {
		throw Error { Error::Reason::invalid_operand };
	}

	if (!is_operators_correct(buffer)) {
		throw Error { Error::Reason::invalid_operator };
	}

	return create_expression(buffer);
}

Node* Parser::create_expression(Buffer buffer) {
	auto operator_iterator = first_operator(Node::Kind::expression, buffer);

	if (operator_iterator == buffer.end()) {
		// Expression -> A_Term
		auto right_child = create_a_term(buffer);
		return new Node { Node::Kind::expression, right: right_child };
	}

	// Expression -> Expression + A_Term
	// Expression -> Expression - A_Term
	auto lhs_buffer = buffer.slice(buffer.begin(), operator_iterator);
	auto left_child = create_expression(lhs_buffer);

	auto rhs_buffer = buffer.slice(operator_iterator + 1, buffer.end());
	auto right_child = create_a_term(rhs_buffer);

	auto token = *operator_iterator;
	auto punctuator = token.to_punctuator();
	auto _operator = Ace::define_operator(punctuator.value());

	return new Node { Node::Kind::expression, _operator: _operator.value(), left: left_child, right: right_child };
}

Node* Parser::create_a_term(Buffer buffer) {
	auto operator_iterator = first_operator(Node::Kind::a_term, buffer);

	if (operator_iterator == buffer.end()) {
		// A_Term -> B_Term
		auto right_child = create_b_term(buffer);
		return new Node { Node::Kind::a_term, right: right_child };
	}

	// A_Term -> A_Term * B_Term
	// A_Term -> A_Term / B_Term
	auto lhs_buffer = buffer.slice(buffer.begin(), operator_iterator);
	auto left_child = create_a_term(lhs_buffer);

	auto rhs_buffer = buffer.slice(operator_iterator + 1, buffer.end());
	auto right_child = create_b_term(rhs_buffer);

	auto token = *operator_iterator;
	auto punctuator = token.to_punctuator();
	auto _operator = Ace::define_operator(punctuator.value());

	return new Node { Node::Kind::a_term, _operator: _operator.value(), left: left_child, right: right_child };
}

Node* Parser::create_b_term(Buffer buffer) {
	auto opening_parenthesis = first_punctuator(Ace::Punctuator::opening_parenthesis, buffer);

	if (opening_parenthesis == buffer.end()) {
		// B_Term -> C_Term
		auto right_child = create_c_term(buffer);
		return new Node { Node::Kind::b_term, right: right_child };
	}

	auto closing_parenthesis = last_punctuator(Ace::Punctuator::closing_parenthesis, buffer);

	// B_Term -> (Expression)
	auto _buffer = buffer.slice(opening_parenthesis + 1, closing_parenthesis);
	auto right_child = create_expression(_buffer);

	return new Node { Node::Kind::b_term, right: right_child };
}

Node* Parser::create_c_term(Buffer buffer) {
	// C_Term -> 0...9
	if (buffer.is_empty()) {
		throw Error { Error::Reason::invalid_operator };
	}

	auto token = buffer[0];
	auto value = stod(token.value);
	return new Node { Node::Kind::c_term, number: value };
}

Parser::Buffer::iterator Parser::first_operator(Node::Kind non_terminal_kind, Buffer &buffer) {
	auto is_non_terminal_operator = [&](Ace::Operator _operator) {
		switch (non_terminal_kind) {
			case Node::Kind::expression: {
				auto is_addition = _operator == Ace::Operator::addition;
				auto is_subtraction = _operator == Ace::Operator::subtraction;
				return is_addition || is_subtraction;
			}
			case Node::Kind::a_term: {
				auto is_multiplication = _operator == Ace::Operator::multiplication;
				auto is_division = _operator == Ace::Operator::division;
				return is_multiplication || is_division;
			}
			default: {
				return false;
			}
		}
	};

	Buffer::iterator result = buffer.end();
	int parenthesis_count = 0;

	for (auto iterator = buffer.begin(); iterator != buffer.end(); iterator++) {
		auto token = *iterator;
		auto punctuator = token.to_punctuator();

		if (!punctuator.has_value()) {
			continue;
		}

		if (punctuator == Ace::Punctuator::opening_parenthesis) {
			parenthesis_count += 1;
			continue;
		}

		if (punctuator == Ace::Punctuator::closing_parenthesis) {
			parenthesis_count -= 1;
			continue;
		}

		if (parenthesis_count > 0) {
			continue;
		}

		auto _operator = Ace::define_operator(punctuator.value());

		if (!_operator.has_value()) {
			continue;
		}

		if (is_non_terminal_operator(_operator.value())) {
			result = iterator;
		}
	}

	return result;
}

Parser::Buffer::iterator Parser::first_punctuator(Ace::Punctuator kind, Buffer &buffer) {
	Buffer::iterator result = buffer.end();

	for (auto iterator = buffer.begin(); iterator != buffer.end(); iterator++) {
		auto token = *iterator;
		auto punctuator = token.to_punctuator();

		if (!punctuator.has_value()) {
			continue;
		}

		if (punctuator.value() == kind) {
			result = iterator;
			break;
		}
	}

	return result;
}

Parser::Buffer::iterator Parser::last_punctuator(Ace::Punctuator kind, Buffer &buffer) {
	Buffer::iterator result = buffer.end();

	for (auto iterator = buffer.begin(); iterator != buffer.end(); iterator++) {
		auto token = *iterator;
		auto punctuator = token.to_punctuator();

		if (!punctuator.has_value()) {
			continue;
		}

		if (punctuator.value() == kind) {
			result = iterator;
		}
	}

	return result;
}

bool Parser::is_parenthesis_correct(Buffer buffer) {
	int opening_parenthesis_count = 0;
	int closing_parenthesis_count = 0;

	for (auto iterator = buffer.begin(); iterator != buffer.end(); iterator++) {
		auto token = *iterator;
		auto punctuator = token.to_punctuator();

		if (!punctuator.has_value()) {
			continue;
		}

		if (punctuator == Ace::Punctuator::opening_parenthesis) {
			opening_parenthesis_count += 1;
			continue;
		}

		if (punctuator == Ace::Punctuator::closing_parenthesis) {
			closing_parenthesis_count += 1;
			continue;
		}
	}

	return opening_parenthesis_count == closing_parenthesis_count;
}

bool Parser::is_operands_correct(Expression::Parser::Buffer buffer) {
	bool is_correct = true;

	set<Lexer::Token::Kind> allowed_tokens {
		Lexer::Token::Kind::literal,
		Lexer::Token::Kind::punctuator
	};

	for (auto iterator = buffer.begin(); iterator != buffer.end(); iterator++) {
		auto token = *iterator;

		if (!allowed_tokens.contains(token.kind)) {
			is_correct = false;
			break;
		}

		auto literal = token.to_literal();

		if (!literal.has_value()) {
			continue;
		}

		switch (literal.value()) {
			case Ace::Literal::integer:
			case Ace::Literal::_double:
				continue;
			default:
				is_correct = false;
				break;
		}

		break;
	}

	return is_correct;
}

bool Parser::is_operators_correct(Expression::Parser::Buffer buffer) {
	bool is_correct = true;

	set<Ace::Punctuator> allowed_punctuators {
		Ace::Punctuator::opening_parenthesis,
		Ace::Punctuator::closing_parenthesis
	};

	for (auto iterator = buffer.begin(); iterator != buffer.end(); iterator++) {
		auto token = *iterator;
		auto punctuator = token.to_punctuator();

		if (!punctuator.has_value()) {
			continue;
		}

		if (allowed_punctuators.contains(punctuator.value())) {
			continue;
		}

		auto _operator = Ace::define_operator(punctuator.value());

		if (!_operator.has_value()) {
			is_correct = false;
			break;
		}
	}

	return is_correct;
}