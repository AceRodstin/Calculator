//
// Created by Ace Rodstin on 23 Nov 2022.
//

#ifndef AC_STRINGS_DICTIONARY_H
#define AC_STRINGS_DICTIONARY_H


#include <map>
#include <optional>
#include <initializer_list>

using namespace std;

template<typename K, typename V>
class Dictionary {
public:
	typedef typename map<K, V>::value_type  value_type;

	Dictionary(initializer_list<value_type> elements) {
		for (auto element : elements) {
			storage.insert(element);
		}
	}

	optional<V> operator[](K key) {
		if (storage.contains(key)) {
			return storage[key];
		} else {
			return {};
		}
	}

	bool contains(K key) {
		return storage.contains(key);
	}

private:
	map<K, V> storage;
};


#endif //AC_STRINGS_DICTIONARY_H
