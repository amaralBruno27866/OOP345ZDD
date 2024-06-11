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
		size_t start = 0;
		size_t end = strBook.find(',');

		// Extracting the author
		std::string author = strBook.substr(start, end - start);
		author.erase(0, author.find_first_not_of(' ')); // Trim leading spaces
		author.erase(author.find_last_not_of(' ') + 1); // Trim trailing spaces
		m_author = author;


		// Extracting the title
		start = end + 1;
		end = strBook.find(',', start);
		std::string title = strBook.substr(start, end - start);
		title.erase(0, title.find_first_not_of(' ')); // Trim leading spaces
		title.erase(title.find_last_not_of(' ') + 1); // Trim trailing spaces
		m_title = title;

		// Extracting the country
		start = end + 1;
		end = strBook.find(',', start);
		std::string country = strBook.substr(start, end - start);
		country.erase(0, country.find_first_not_of(' ')); // Trim leading spaces
		country.erase(country.find_last_not_of(' ') + 1); // Trim trailing spaces
		m_country = country;

		// Extracting the year
		start = end + 1;
		end = strBook.find(',', start);
		std::string year = strBook.substr(start, end - start);
		year.erase(0, year.find_first_not_of(' ')); // Trim leading spaces
		year.erase(year.find_last_not_of(' ') + 1); // Trim trailing spaces
		m_year = std::stoi(year);

		// Extracting the price
		start = end + 1;
		end = strBook.find(',', start);
		std::string price = strBook.substr(start, end - start);
		price.erase(0, price.find_first_not_of(' ')); // Trim leading spaces
		price.erase(price.find_last_not_of(' ') + 1); // Trim trailing spaces
		m_price = std::stod(price);

		// Extracting the description
		start = end + 1;
		end = strBook.find(',', start);
		std::string description = strBook.substr(start, end - start);
		description.erase(0, description.find_first_not_of(' ')); // Trim leading spaces
		description.erase(description.find_last_not_of(' ') + 1); // Trim trailing spaces
		m_description = description;
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