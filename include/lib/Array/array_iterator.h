//
// Created by Ace Rodstin on 11/24/22.
//

#ifndef LIBRARIES_ARRAY_ITERATOR_H
#define LIBRARIES_ARRAY_ITERATOR_H


#include <iterator>
#include <algorithm>
#include "Array.h"

using namespace std;

template<typename T>
class array_iterator: std::iterator<random_access_iterator_tag, T, T, const T*, T> {
public:
	typedef vector<T> Storage;

	unsigned long position;

	array_iterator() {
		this->storage = nullptr;
		this->position = 0;
	}

	array_iterator(shared_ptr<Storage> storage, unsigned long position) {
		this->storage = storage;
		this->position = position;
	}

	array_iterator& operator++() {
		position = bounded(position + 1);
		return *this;
	}

	array_iterator& operator++(int) {
		position = bounded(position + 1);
		return *this;
	}

	array_iterator& operator--(int) {
		position = bounded(position - 1);
		return *this;
	}

	array_iterator operator+(unsigned long offset) {
		auto _position = bounded(position + offset);
		return { storage, _position };
	}

	array_iterator operator-(unsigned long offset) {
		auto _position = bounded(position - offset);
		return { storage, _position };
	}

	bool operator!=(array_iterator other) const {
		return !(*this == other);
	};

	bool operator==(array_iterator other) const {
		return position == other.position;
	}

	T operator*() const {
		return (*storage)[position];
	}

	bool operator>(array_iterator& other) {
		return this->position > other.position;
	}

	bool operator<(array_iterator& other) {
		return this->position < other.position;
	}

	bool operator>=(array_iterator& other) {
		return this->position >= other.position;
	}

	bool operator<=(array_iterator& other) {
		return this->position <= other.position;
	}

private:
	shared_ptr<Storage> storage;

	unsigned long bounded(const unsigned long position) {
		unsigned long lower_bound = 0;
		auto upper_bound = storage->size();

		auto _position = max(lower_bound, position);
		_position = min(upper_bound, _position);

		return _position;
	}
};

#endif //LIBRARIES_ARRAY_ITERATOR_H
