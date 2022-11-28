//
// Created by Ace Rodstin on 25 Nov 2022.
//

#include "../../include/Interpretator/Interpretator.h"
#include "../../include/Ace.h"

Interpretator::Error::Error(Interpretator::Error::Reason reason) : reason(reason) {}

const char * Interpretator::Error::what() const noexcept {
	switch (reason) {
		return "Division by zero";
	}
}

double Interpretator::calculate(Expression::Node *node) {
	if (node->number.has_value()) {
		return node->number.value();
	} else if (node->_operator.has_value()) {
		auto _operator = node->_operator.value();
		auto lhs = calculate(node->left);
		auto rhs = calculate(node->right);

		switch (_operator) {
			case Ace::Operator::addition:
				return lhs + rhs;
			case Ace::Operator::subtraction:
				return lhs - rhs;
			case Ace::Operator::multiplication:
				return lhs * rhs;
			case Ace::Operator::division:
				if (rhs == 0) {
					throw Error { Error::Reason::division_by_zero };
				}

				return lhs / rhs;
		}
	} else {
		return calculate(node->right);
	}
}