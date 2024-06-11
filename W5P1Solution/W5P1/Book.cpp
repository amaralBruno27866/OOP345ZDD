#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Book.h"

namespace seneca {
	Book::Book() : m_author(""), m_title(""), m_country(""), m_year(0), m_price(0), m_description("") {}

	Book::Book(std::string author, std::string title, std::string country, int year, double price, std::string description) :
		m_author(author), m_title(title), m_country(country), m_year(year), m_price(price), m_description(description) {}

	Book::Book(const Book& book) {
		m_author = book.m_author;
		m_title = book.m_title;
		m_country = book.m_country;
		m_year = book.m_year;
		m_price = book.m_price;
		m_description = book.m_description;
	}

	Book& Book::operator=(const Book& book) {
		if(this != &book) {
			m_author = book.m_author;
			m_title = book.m_title;
			m_country = book.m_country;
			m_year = book.m_year;
			m_price = book.m_price;
			m_description = book.m_description;
		}
		return *this;
	}

	Book::~Book() {}

	Book::Book(const std::string& strBook) {
		std::istringstream ss(strBook);
		std::string field;

		// Extracting the author
		std::getline(ss, field, ',');
		m_author = trim(field);

		// Extracting the title
		std::getline(ss, field, ',');
		m_title = trim(field);

		// Extracting the country
		std::getline(ss, field, ',');
		m_country = trim(field);

		// Extracting the price
		ss >> m_price;
		ss.ignore();

		// Extracting the year
		ss >> m_year;
		ss.ignore();

		// Extracting the description
		std::getline(ss, field, ',');
		m_description = trim(field);
	}

	std::ostream& operator<<(std::ostream& os, const Book& book) {
		os << std::setw(20) << std::setfill(' ') << std::right << book.m_author;
		os << " | ";
		os << std::setw(22) << std::setfill(' ') << std::right << book.m_title;
		os << " | ";
		os << std::setw(5) << std::setfill(' ') << std::right << book.m_country;
		os << " | ";
		os << std::setw(4) << book.m_year;
		os << " | ";
		os << std::setw(6) << std::fixed << std::setprecision(2) << book.m_price;
		os << " | ";
		os << book.m_description;
		return os;
	}
}