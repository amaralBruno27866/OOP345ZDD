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

	Movie::Movie() {
		m_title = "";
		m_year = 0;
		m_description = "";
	}

	Movie::Movie(const std::string& strMovie) {
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

	std::ostream& operator<<(std::ostream& os, const Movie& movie) {
		os << std::setw(40) << std::setfill(' ') << std::right << movie.m_title;
		os << " | ";
		os << std::setw(4) << std::setfill(' ') << std::right << movie.m_year;
		os << " | ";
		os << movie.m_description;
		os << std::endl;
		return os;
	}
}
