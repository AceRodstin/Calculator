//
// Created by Ace Rodstin on 25 Nov 2022.
//

#include <iostream>
#include <sstream>
#include "include/SourceManager/SourceManager.h"
#include "include/lib/FileManager.h"
#include "include/Calculator/Calculator.h"

using namespace std;

void print(Expression::Parser::Error error) {
	typedef typename Expression::Parser::Error::Reason Reason;
	int code;

	switch (error.reason) {
		case Reason::invalid_parenthesis:
			code = 1;
			break;
		case Reason::invalid_operand:
			code = 2;
			break;
		case Reason::invalid_operator:
			code = 3;
			break;
	}

	cout << "Error code " << code << endl;
}

void print(Interpretator::Error error) {
	typedef typename Interpretator::Error::Reason Reason;
	int code;

	switch (error.reason) {
		case Reason::division_by_zero:
			code = 4;
			break;
	}

	cout << "Error code " << code << endl;
}

int main() {
	string source_code_path = "../Resources/source_code.ace";
	string results_path = "../Resources/calculation_results.txt";

	SourceManager source_manager;
	auto source_code = source_manager.read(source_code_path);

	FileManager file_manager;
	file_manager.open_file(results_path, FileManager::OpenOption::write);

	Calculator calculator;

	stringstream stream { source_code };
	string line;

	while (getline(stream, line)) {
		try {
			auto result = calculator.calculate(line);
			file_manager.write(result);

			cout << result << endl;
		} catch (Expression::Parser::Error error) {
			print(error);
		} catch (Interpretator::Error error) {
			print(error);
		}
	}

	file_manager.close_file();
	return 0;
}
