#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H

#include <iostream>
#include <iomanip>
#include <string>
#include "SpellChecker.h"

namespace seneca {
	class Book {
	private:
		std::string m_author;
		std::string m_title;
		std::string m_country;
		size_t m_year;
		double m_price;
		std::string m_description;
	public:
		Book();
		Book(std::string author, std::string title, std::string country, int year, double price, std::string description);
		Book(const Book& book);
		Book& operator=(const Book& book);
		~Book();

		std::string getAuthor() const { return m_author; };
		std::string getDescription() const { return m_description; };

		const std::string& title() const { return m_title; };
		const std::string& country() const { return m_country; };
		const size_t& year() const { return m_year; };
		double& price()	{ return m_price; };

		Book(const std::string& strBook);

		friend std::ostream& operator<<(std::ostream& os, const Book& book);

		template<typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(m_description);
		}
	};

	template <typename T>
	class Collection {
	private:
		T* items;
		size_t size;
	public:
		Collection() : items(nullptr), size(0) {}
		~Collection() { delete[] items; }

		void add(const T& item) {
			T* temp = new T[size + 1];
			for (size_t i = 0; i < size; i++) {
				temp[i] = items[i];
			}
			temp[size] = item;
			delete[] items;
			items = temp;
			size++;
		}

		T& operator[](size_t index) {
			if (index >= size) {
				throw std::out_of_range("Invalid index");
			}
			return items[index];
		}

		size_t getSize() const { return size; }
	};
}

#endif // !SENECA_BOOK_H
