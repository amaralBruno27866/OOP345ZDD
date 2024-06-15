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
