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

#ifndef SENECA_MOVEI_H
#define SENECA_MOVEI_H

#include <string>

namespace seneca {
	class Movie {
		std::string m_title;
		size_t m_year;
		std::string m_description;

	public:
		Movie();
		Movie(const std::string strMovie);
		const std::string& title() const;

		template<typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(m_title);
			spellChecker(m_description);
		}

		friend std::ostream& operator<<(std::ostream& os, const Movie& theMovie);
	};
}

#endif // !SENECA_MOVEI_H
