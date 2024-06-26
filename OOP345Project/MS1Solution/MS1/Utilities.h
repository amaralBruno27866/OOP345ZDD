#ifndef SENECA_UTILITIES_H
#define SENECA_UTILITIES_H

#include <iostream>
#include <string>

namespace seneca {
	// The Utilities class provides helper functions for parsing strings.
	class Utilities {
		size_t m_widthField = 1; // Current maximum field width
		static char m_delimiter; // Delimiter used for token extraction
	public:
		// Sets the field width of the current object
		void setFieldWidth(size_t newWidth);

		// Returns the field width of the current object
		size_t getFieldWidth() const;

		// Extracts tokens from the first parameter.
		std::string extractToken(const std::string& str, size_t& next_pos, bool& more);

		// Sets the delimiter for this class to the character received
		static void setDelimiter(char newDelimiter);

		// Returns the delimiter character of the current object
		static char getDelimiter();
	};
}

#endif // !SENECA_UTILITIES_H
