/*/////////////////////////////////////////////////////////////////////////
				  Workshop - #8 P2
Full Name  : Bruno Amaral
Student ID#: 143766228
Email      : bamaral2@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS
#include <memory>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include <type_traits>
#include <mutex>
#include "Database.h"

namespace seneca {
	void encryptDecrypt(std::string& value) {
		const char secret[] = "secret encryption key";
		for (char& c : value) {
			for (const char& k : secret) {
				c ^= k;
			}
		}
	}

	void encryptDecrypt(long long& value) {
		const char secret[] = "super secret encryption key";
		char* valueBytes = reinterpret_cast<char*>(&value);
		for (size_t i = 0; i < sizeof(long long); ++i) {
			for (const char& k : secret) {
				valueBytes[i] ^= k;
			}
		}
	}
}