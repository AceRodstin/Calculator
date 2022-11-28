//
// Created by Ace Rodstin on 22 Nov 2022.
//

#include "../include/CharacterSet.h"

CharacterSet CharacterSet::digits {
		{ '0', '9' }
};

CharacterSet CharacterSet::alphabet {
		{ 'A', 'Z' },
		{ 'a', 'z' }
};

CharacterSet CharacterSet::alpha_numeric {
		{ '0', '9' },
		{ 'A', 'Z' },
		{ 'a', 'z' }
};

CharacterSet::CharacterSet(initializer_list<Range> ranges) {
	for (auto range : ranges) {
		char temp = range.start;

		while (temp <= range.end) {
			storage.insert(temp);
			temp++;
		}
	}
}

bool CharacterSet::contains(const char character) {
	return storage.contains(character);
}