/*/////////////////////////////////////////////////////////////////////////
						  Workshop - #3 P2
Full Name  : Bruno Amaral
Student ID#: 143766228
Email      : bamaral2@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

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
