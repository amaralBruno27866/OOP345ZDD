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
#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <algorithm>
#include <limits>
#include "Book.h"

namespace seneca {
	template <typename T, unsigned C>
	class Collection {
	private:
		T m_items[C];
		unsigned m_size;
		static T m_smallestItem;
		static T m_largestItem;

	protected:
		void setSmallestItem(const T& src) {
			if (src < m_smallestItem) {
				m_smallestItem = src;
			}
		}

		void setLargestItem(const T& src) {
			if (src > m_largestItem) {
				m_largestItem = src;
			}
		}

		T& operator[]{
			return m_items[index];
		}

		void incrSize() {
			++m_size;
		}

	public:
		Collection() : m_size(0) {}

		static T getSmallestItem() {
			return m_smallestItem;
		}

		static T getLargestItem() {
			return m_largestItem;
		}

		unsigned size() const {
			return m_size;
		}

		unsigned capacity() const {
			return C;
		}

		bool operator+=(const T& src) {
			if (m_size >= C) {
				return false;
			}
			setSmallestItem(src);
			setLargestItem(src);
			m_items[m_size++] = src;
			return true;
		}

		void print(std::ostream& os) const {
			os << "[";
			for (unsigned i = 0; i < m_size; ++i) {
				os << m_items[i];
				if (i < m_size - 1) {
					os << ", ";
				}
			}
			os << "]";
		}
	};

	template <typename T, unsigned C>
	T Collection<T, C>::m_smallestItem = std::numeric_limits<T>::max();

	template <typename T, unsigned C>
	T Collection<T, C>::m_largestItem = std::numeric_limits<T>::lowest();

	template<>
	Book Collection<Book, 72>::m_smallestItem = Book("", 1, 10000);

	template<>
	Book Collection<Book, 72>::m_largestItem = Book("", 10000, 1);

	template<>
	void Collection<Book, 10>::print(std::ostream& os) {
		for (unsigned i = 0; i < m_size; ++i) {
			os << m_items[i] << std::endl;
		}
	}

	template<>
	void Collection<Book, 72>::print(std::ostream& os) {
		for (unsigned i = 0; i < m_size; ++i) {
			os << m_items[i] << std::endl;
		}
	}
}

#endif // !SENECA_COLLECTION_H
