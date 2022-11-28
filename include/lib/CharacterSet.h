//
// Created by Ace Rodstin on 22 Nov 2022.
//

#ifndef GRAMMARPARSER_CHARACTERSET_H
#define GRAMMARPARSER_CHARACTERSET_H


#include <set>
#include <string>
#include <algorithm>
#include <initializer_list>

using namespace std;

class CharacterSet {
public:
	struct Range {
		char start;
		char end;
	};

	static CharacterSet digits;
	static CharacterSet alphabet;
	static CharacterSet alpha_numeric;

	CharacterSet(initializer_list<Range> ranges);
	bool contains(char character);

private:
	set<char> storage;
};


#endif //GRAMMARPARSER_CHARACTERSET_H
