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

		void incrSize() {
			if (m_size < C) {
				++m_size;
			}
			else {
				throw std::out_of_range("Collection is already full");
			}
		}

		T& operator[] {
			if (index >= m_size) {
				throw std::out_of_range("Index out of range");
			}
			return m_items[index];
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
			bool isTrue = false;

			if (m_size >= C) {
				isTrue = false;
			}
			else {
				setSmallestItem(src);
				setLargestItem(src);
				m_items[m_size++] = src;
				isTrue = true;
			}

			return isTrue;
		}

		virtual void print(std::ostream& os) const {
			os << "[";
			for (unsigned i = 0; i < m_size; ++i) {
				os << m_items[i];
				if (i < m_size - 1) {
					os << ",";
				}
			}
			os << "]" << std::endl;
		}
	};

	template <typename T, unsigned C>
	T Collection<T, C>::m_smallestItem = std::numeric_limits<T>::max();

	template <typename T, unsigned C>
	T Collection<T, C>::m_largestItem = std::numeric_limits<T>::lowest();

	template<>
	Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);

	template<>
	Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);

	template<>
	Book Collection<Book, 72>::m_smallestItem = Book("", 1, 10000);

	template<>
	Book Collection<Book, 72>::m_largestItem = Book("", 10000, 1);
}

#endif // !SENECA_COLLECTION_H

