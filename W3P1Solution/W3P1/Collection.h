#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <algorithm>
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

		void print(std::ostream& os) const {
			for (unsigned i = 0; i < m_size; ++i) {
				os << m_items[i] << std::endl;
			}
		}
	};

	template <typename T, unsigned C>
	T Collection<T, C>::m_smallestItem = T();

	template <typename T, unsigned C>
	T Collection<T, C>::m_largestItem = T();
}

#endif // !SENECA_COLLECTION_H

