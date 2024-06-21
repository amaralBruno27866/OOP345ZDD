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
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "Book.h"

namespace seneca {
	Book::Book() : m_author(""), m_title(""), m_country(""), m_year(0), m_price(0), m_description("") {} // Inicialização de lista de membros no construtor padrão

	Book::Book(std::string author, std::string title, std::string country, int year, double price, std::string description) :
		m_author(author), m_title(title), m_country(country), m_year(year), m_price(price), m_description(description) {} // Inicialização de lista de membros no construtor parametrizado

	Book::Book(const Book& book) { // Construtor de cópia
		m_author = book.m_author;
		m_title = book.m_title;
		m_country = book.m_country;
		m_year = book.m_year;
		m_price = book.m_price;
		m_description = book.m_description;
	}

	Book& Book::operator=(const Book& book) { // Operador de atribuição de cópia
		if (this != &book) {
			m_author = book.m_author;
			m_title = book.m_title;
			m_country = book.m_country;
			m_year = book.m_year;
			m_price = book.m_price;
			m_description = book.m_description;
		}
		return *this;
	}

	Book::~Book() {} // Destrutor

	Book::Book(const std::string& strBook) { // Construtor que aceita uma string formatada
		size_t start = 0;
		size_t end = strBook.find(',');

		// Extraindo o autor
		std::string author = strBook.substr(start, end - start);
		author.erase(0, author.find_first_not_of(' ')); // Remove espaços iniciais
		author.erase(author.find_last_not_of(' ') + 1); // Remove espaços finais
		m_author = author;

		// Extraindo o título
		start = end + 1;
		end = strBook.find(',', start);
		std::string title = strBook.substr(start, end - start);
		title.erase(0, title.find_first_not_of(' ')); // Remove espaços iniciais
		title.erase(title.find_last_not_of(' ') + 1); // Remove espaços finais
		m_title = title;

		// Extraindo o país
		start = end + 1;
		end = strBook.find(',', start);
		std::string country = strBook.substr(start, end - start);
		country.erase(0, country.find_first_not_of(' ')); // Remove espaços iniciais
		country.erase(country.find_last_not_of(' ') + 1); // Remove espaços finais
		m_country = country;

		// Extraindo o preço
		start = end + 1;
		end = strBook.find(',', start);
		std::string price = strBook.substr(start, end - start);
		price.erase(0, price.find_first_not_of(' ')); // Remove espaços iniciais
		price.erase(price.find_last_not_of(' ') + 1); // Remove espaços finais
		m_price = std::stod(price);

		// Extraindo o ano
		start = end + 1;
		end = strBook.find(',', start);
		std::string year = strBook.substr(start, end - start);
		year.erase(0, year.find_first_not_of(' ')); // Remove espaços iniciais
		year.erase(year.find_last_not_of(' ') + 1); // Remove espaços finais
		m_year = std::stoi(year);

		// Extraindo a descrição
		start = end + 1;
		end = strBook.find('\n', start);
		std::string description = strBook.substr(start, end - start);
		description.erase(0, description.find_first_not_of(' ')); // Remove espaços iniciais
		description.erase(description.find_last_not_of(' ') + 1); // Remove espaços finais
		m_description = description;
	}

	std::ostream& operator<<(std::ostream& os, const Book& book) { // Sobrecarregando o operador de inserção
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
		os << std::endl;
		return os;
	}
}
