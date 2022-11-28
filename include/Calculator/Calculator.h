//
// Created by Ace Rodstin on 25 Nov 2022.
//

#ifndef ACE_CALCULATOR_H
#define ACE_CALCULATOR_H


#include <iostream>
#include "../Lexer/Parser.h"
#include "../Expression/Parser.h"
#include "../Interpretator/Interpretator.h"
#include "../lib/StringManager.h"

class Calculator {
public:
	string calculate(string expression);
};


#endif //ACE_CALCULATOR_H
