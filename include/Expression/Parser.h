//
// Created by Ace Rodstin on 22 Nov 2022.
//

#ifndef GRAMMARPARSER_PARSER_H
#define GRAMMARPARSER_PARSER_H


#include <string>
#include <vector>
#include <map>
#include "Node.h"
#include "../Lexer/Parser.h"
#include <list>
#include "../lib/Array/Array.h"

using namespace std;

namespace Expression {
	class Parser {
	public:
		class Error: exception {
		public:
			enum class Reason {
				invalid_parenthesis,
				invalid_operand,
				invalid_operator
			};

			const Reason reason;

			explicit Error(Reason reason);
			const char * what() const noexcept override;
		};

		Node* parse(vector<Lexer::Token> &tokens);

	private:
		typedef Array<Lexer::Token> Buffer;

		Node* create_expression(Buffer buffer);
		Node* create_a_term(Buffer buffer);
		Node* create_b_term(Buffer buffer);
		Node* create_c_term(Buffer buffer);
		Buffer::iterator first_operator(Node::Kind non_terminal_kind, Buffer &buffer);
		Buffer::iterator first_punctuator(Ace::Punctuator kind, Buffer &buffer);
		Buffer::iterator last_punctuator(Ace::Punctuator kind, Buffer &buffer);
		bool is_parenthesis_correct(Buffer buffer);
		bool is_operands_correct(Buffer buffer);
		bool is_operators_correct(Buffer buffer);
	};
}


#endif //GRAMMARPARSER_PARSER_H
