#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <iostream>
#include <string>

namespace seneca {
	class Book {
	private:
		std::string m_title{};
		unsigned m_numChapters{};
		unsigned m_numPages{};
	public:
		Book();
		Book(const std::string& title, unsigned nChapters, unsigned nPages);

		bool isValid() const;
		unsigned getPages() const { return m_numPages; };
		unsigned getChapters() const { return m_numChapters; };
		double getNumOfPagesPerChapter() const;

		bool operator<(const Book& book) const;
		bool operator>(const Book& book) const;

		std::ostream& print(std::ostream& os) const;
	};
	std::ostream& operator<<(std::ostream& os, const Book& bk);
}

#endif // !SENECA_BOOK_H
