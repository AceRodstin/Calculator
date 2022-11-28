//
// Created by Ace Rodstin on 26 Nov 2022.
//

#ifndef CALCULATOR_CALCULATOR_TESTS_H
#define CALCULATOR_CALCULATOR_TESTS_H


#include <string>
#include "../include/Calculator/Calculator.h"

using namespace std;

namespace Calculator_tests {
	void test_calculator_1() {
		// Given
		string input = "1+2";
		string expected = "1+2 = 3.00";

		// When
		Calculator calculator;
		auto output = calculator.calculate(input);

		// Then
		assert(output == expected);
		cout << "test_calculator_1 passed" << endl;
	}

	void test_calculator_2() {
		// Given
		string input = "1 + 2";
		string expected = "1 + 2 = 3.00";

		// When
		Calculator calculator;
		auto output = calculator.calculate(input);

		// Then
		assert(output == expected);
		cout << "test_calculator_2 passed" << endl;
	}

	void test_calculator_3() {
		// Given
		string input = "1 - 2";
		string expected = "1 - 2 = -1.00";

		// When
		Calculator calculator;
		auto output = calculator.calculate(input);

		// Then
		assert(output == expected);
		cout << "test_calculator_3 passed" << endl;
	}

	void test_calculator_4() {
		// Given
		string input = "(1 - 2) / 3";
		string expected = "(1 - 2) / 3 = -0.33";

		// When
		Calculator calculator;
		auto output = calculator.calculate(input);

		// Then
		assert(output == expected);
		cout << "test_calculator_4 passed" << endl;
	}

	void test_calculator_5() {
		// Given
		string input = "1 - 2 / 3";
		string expected = "1 - 2 / 3 = 0.33";

		// When
		Calculator calculator;
		auto output = calculator.calculate(input);

		// Then
		assert(output == expected);
		cout << "test_calculator_5 passed" << endl;
	}

	void test_calculator_6() {
		// Given
		string input = "(1 - 2 / (3 + 4)) * 5";
		string expected = "(1 - 2 / (3 + 4)) * 5 = 3.57";

		// When
		Calculator calculator;
		auto output = calculator.calculate(input);

		// Then
		assert(output == expected);
		cout << "test_calculator_6 passed" << endl;
	}

	void test_calculator_7() {
		// Given
		string input = "2 +2   * 2";
		string expected = "2 +2   * 2 = 6.00";

		// When
		Calculator calculator;
		auto output = calculator.calculate(input);

		// Then
		assert(output == expected);
		cout << "test_calculator_7 passed" << endl;
	}
}


#endif //CALCULATOR_CALCULATOR_TESTS_H
