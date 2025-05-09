/*/////////////////////////////////////////////////////////////////////////
				  Workshop - #5 P2
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
#include <string>
#include <stdexcept>
#include <iomanip>
#include "Movie.h"

namespace seneca {
	Movie::Movie() : m_year(0) {}

	Movie::Movie(const std::string strMovie) {
		size_t start = 0;
		size_t end = strMovie.find(',');

		// Extracting the title
		std::string title = strMovie.substr(start, end - start);
		title.erase(0, title.find_first_not_of(' ')); // Trim leading spaces
		title.erase(title.find_last_not_of(' ') + 1); // Trim trailing spaces
		m_title = title;

		// Extracting the year
		start = end + 1;
		end = strMovie.find(',', start);
		std::string year = strMovie.substr(start, end - start);
		year.erase(0, year.find_first_not_of(' ')); // Trim leading spaces
		year.erase(year.find_last_not_of(' ') + 1); // Trim trailing spaces
		m_year = std::stoi(year);

		// Extracting the description
		start = end + 1;
		end = strMovie.find('\n', start);
		std::string description = strMovie.substr(start, end - start);
		description.erase(0, description.find_first_not_of(' ')); // Trim leading spaces
		description.erase(description.find_last_not_of(' ') + 1); // Trim trailing spaces
		m_description = description;
	}

	const std::string& Movie::title() const {
		return m_title;
	}

	std::ostream& operator<<(std::ostream& os, const Movie& theMovie) {
		os << std::setw(40) << std::setfill(' ') << std::right << theMovie.m_title;
		os << " | ";
		os << std::setw(4) << std::setfill(' ') << std::right << theMovie.m_year;
		os << " | ";
		os << theMovie.m_description;
		os << std::endl;
		return os;
	}
}
