#define _CRT_SECURE_NO_WARNINGS

#include <iomanip>
#include "Book.h"

using namespace std;
namespace seneca {
	Book::Book() {
		m_title = "";
		m_numChapters = 0;
		m_numPages = 0;
	}

	Book::Book(const std::string& title, unsigned nChapters, unsigned nPages) {
		m_title = title;
		m_numChapters = nChapters;
		m_numPages = nPages;
	}

	bool Book::isValid() const {
		bool check = false;

		if (!m_title.empty() && m_numChapters > 0 && m_numPages > 0) {
			check = true;
		}

		return check;
	}

	double Book::getNumOfPagesPerChapter() const {
		double result = 0.0;

		if (m_numChapters > 0) {		
			result = static_cast<double>(m_numPages) / m_numChapters;
		}

		return result;
	}

	bool Book::operator<(const Book& book) const {
		double v1 = getNumOfPagesPerChapter();

		double v2 = book.getNumOfPagesPerChapter();

		return v1 < v2;
	}

	bool Book::operator>(const Book& book) const {
		double v1 = getNumOfPagesPerChapter();

		double v2 = book.getNumOfPagesPerChapter();

		return v1 > v2;
	}

	std::ostream& Book::print(std::ostream& os) const {
		if (isValid()) {
			double pagesPerChapter = getNumOfPagesPerChapter();

			os << right << setw(56)
				<< m_title + "," + to_string(m_numChapters) + "," + to_string(m_numPages)
				<< " | (" << left << std::fixed << std::setprecision(6) << pagesPerChapter << std::defaultfloat << ")    ";
		}
		else {
			os << "| Invalid book data";
		}

		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Book& bk) {
		return bk.print(os);
	}
}