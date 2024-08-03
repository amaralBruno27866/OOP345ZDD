// Name: Bruno Amaral
// Seneca Student ID: 143766228
// Seneca email: bamaral2@myseneca.ca
// Date of completion: August 4th, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Utilities.h"

namespace seneca {
	// Initialize the delimiter to a comma.
	char seneca::Utilities::m_delimiter = ',';

	// Sets the field width of the current object
	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	// Returns the field width of the current object
	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	// Extracts tokens from the first parameter.
	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		more = false; // Default to false.

		// If next_pos is past the end of the string, return an empty string.
		if (next_pos >= str.length()) {
			return "";
		}

		// Find the next delimiter.
		size_t pos = str.find(m_delimiter, next_pos);

		// If the delimiter is found at next_pos, throw an exception.
		if (pos == next_pos) {
			throw std::string("Delimiter found at next_pos");
		}

		// If no further delimiter is found, the rest of the string is the last token.
		more = (pos != std::string::npos);
		std::string token = str.substr(next_pos, pos - next_pos);
		next_pos = pos + (more ? 1 : 0);

		// Trim leading and trailing spaces.
		size_t start = token.find_first_not_of(' ');
		size_t end = token.find_last_not_of(' ');
		token = (start == std::string::npos) ? "" : token.substr(start, end - start + 1);

		if(token.length() > m_widthField) {
			m_widthField = token.length();
		}

		return token;
	}

	// Sets the delimiter for this class to the character received
	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	// Returns the delimiter character of the current object
	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}