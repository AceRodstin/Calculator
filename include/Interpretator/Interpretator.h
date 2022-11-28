//
// Created by Ace Rodstin on 25 Nov 2022.
//

#ifndef INTERPRETATOR_INTERPRETATOR_H
#define INTERPRETATOR_INTERPRETATOR_H


#include "../Expression/Node.h"

class Interpretator {
public:
	class Error: exception {
	public:
		enum class Reason {
			division_by_zero
		};

		const Reason reason;

		explicit Error(Reason reason);
		const char * what() const noexcept override;
	};

	double calculate(Expression::Node *node);
};


#endif //INTERPRETATOR_INTERPRETATOR_H
