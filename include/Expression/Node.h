//
// Created by Ace Rodstin on 22 Nov 2022.
//

#ifndef GRAMMARPARSER_NODE_H
#define GRAMMARPARSER_NODE_H


#include <optional>
#include "../Ace.h"

using namespace std;

namespace Expression {
	struct Node {
		enum class Kind {
			expression,
			a_term,
			b_term,
			c_term
		};

		Kind kind;
		optional<Ace::Operator> _operator;
		optional<double> number;
		Node *left;
		Node *right;
	};
}


#endif //GRAMMARPARSER_NODE_H
