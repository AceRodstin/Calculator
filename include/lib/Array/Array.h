//
// Created by Ace Rodstin on 24 Nov 2022.
//

#ifndef LIBRARIES_ARRAY_H
#define LIBRARIES_ARRAY_H


#include <initializer_list>
#include <vector>
#include <algorithm>
#include <optional>
#include "array_iterator.h"

using namespace std;

template<typename T>
class Array {
public:
	typedef vector<T> Container;
	typedef array_iterator<T> iterator;

	Array() {
		storage = make_shared<Container>();
	};

	Array(initializer_list<T> elements) {
		storage = make_shared<Container>();

		for (auto element : elements) {
			storage->push_back(element);
		}
	}

	Array(Container container) {
		storage = make_shared<Container>();

		for (auto element : container) {
			storage->push_back(element);
		}
	}

	Array(const Array &other) {
		storage = make_shared<Container>();

		for (auto element : other) {
			storage->push_back(element);
		}
	}

	T operator[](int index) {
		return (*storage)[index];
	}

	iterator begin() const {
		return iterator { storage, 0 };
	}

	iterator end() const {
		return { storage, size() };
	}

	void append(T value) {
		storage->push_back(value);
	}

	bool is_empty() {
		return storage->empty();
	}

	unsigned int size() const {
		return storage->size();
	}

	bool contains(T value) {
		auto iterator = find(storage->begin(), storage->end(), value);
		return iterator != storage->end();
	}

	Array<T> slice(iterator first, iterator last) {
		Container container { storage->begin() + first.position, storage->begin() + last.position };
		return { container };
	}

	template<typename M, typename V>
	void map(M mapper, Array<V> &destination) {
		for (auto element : *storage) {
			V mapped = mapper(element);
			destination.append(mapped);
		}
	}

	template<typename M, typename V>
	void compact_map(M mapper, Array<V> &destination) {
		for (auto element : *storage) {
			optional<V> mapped = mapper(element);

			if (mapped.has_value()) {
				destination.append(mapped.value());
			}
		}
	}

private:
	shared_ptr<Container> storage;
};


#endif //LIBRARIES_ARRAY_H
