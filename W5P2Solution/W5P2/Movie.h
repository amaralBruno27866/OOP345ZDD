#ifndef SENECA_MOVIE_H
#define SENECA_MOVIE_H

#include <iostream>
#include <iomanip>
#include <string>

namespace seneca {
	class Movie {
	private:
		std::string m_title;
		size_t m_year;
		std::string m_description;
	public:
		Movie();
		Movie(const std::string& strMovie);
		const std::string& title() const;

		template<typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(m_title);
			spellChecker(m_description);
		}

		friend std::ostream& operator<<(std::ostream& os, const Movie& movie);
	};
}
#endif // !SENECA_MOVIE_H