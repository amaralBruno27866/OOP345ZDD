#define _CRT_SECURE_NO_WARNINGS
#include <sstream>
#include <fstream>
#include <iomanip>
#include "SpellChecker.h"
#include "Movie.h"

namespace seneca {
	void Movie::trim(std::string& str) {
		size_t start = str.find_first_not_of(' ');
		size_t end = str.find_last_not_of(' ');
		str = str.substr(start, end - start + 1);
	}
}
