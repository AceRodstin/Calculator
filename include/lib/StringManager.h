//
// Created by Ace Rodstin on 15 Nov 2022.
//

#ifndef AC_STRINGS_STRINGMANAGER_H
#define AC_STRINGS_STRINGMANAGER_H


#include <string>
#include <vector>
#include <sstream>

using namespace std;

class StringManager {
public:
	template<class Predicate>
	string trim(string str, Predicate predicate) {
		unsigned long size = str.size();
		unsigned long leading_position = 0;
		unsigned long trailing_position = 0;

		while (predicate(str[leading_position])) {
			leading_position++;
		}

		while (predicate(str[size - trailing_position - 1])) {
			trailing_position++;
		}

		string trimmed = str.substr(leading_position, size);
		trimmed = trimmed.substr(0, trimmed.size() - trailing_position);

		return trimmed;
	}

	template<class Predicate>
	vector<string> split(string str, Predicate predicate, bool include_delimiter = false) {
		vector<string> result;

		unsigned long size = str.size();
		unsigned long position = 0;
		unsigned long delimiter_area = 0;

		auto split = [&](int i) {
			auto length = i - delimiter_area - position;
			auto delimiter_length = include_delimiter ? delimiter_area : 0;
			auto components = split_components(str, position, length, delimiter_length);

			for (auto component : components) {
				result.push_back(component);
			}

			position = i;
			delimiter_area = 0;
		};

		for (int i = 0; i <= size; i++) {
			bool is_end = i == size;

			if (is_end) {
				if (delimiter_area > 0) {
					split(i);
				} else {
					string slice = str.substr(position, i - position + 1);
					result.push_back(slice);
				}
			}

			char character = str[i];
			bool is_delimiter = predicate(character);

			if (is_delimiter) {
				delimiter_area++;
			} else if (delimiter_area > 0) {
				split(i);
			}
		}

		return result;
	}

	template <typename T>
	std::string to_string(const T value, const int n)
	{
		std::ostringstream out;
		out.precision(n);
		out << std::fixed << value;
		return out.str();
	}

private:
	vector<string> split_components(string str, int position, int length, int delimiter_length) {
		vector<string> result;

		string lhs = str.substr(position, length);

		if (!lhs.empty()) {
			result.push_back(lhs);
		}

		for (int j = 0; j < delimiter_length; j++) {
			string rhs = str.substr(position + length + j, 1);
			result.push_back(rhs);
		}

		return result;
	}
};


#endif //AC_STRINGS_STRINGMANAGER_H
