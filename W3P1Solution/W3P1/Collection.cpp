#define _CRT_SECURE_NO_WARNINGS

#include "Collection.h"
#include "Book.h"

namespace seneca {
	template<>
	Book Collection<Book, 10>::m_smallestItem = Book("", 1, 10000);

	template<>
	Book Collection<Book, 10>::m_largestItem = Book("", 10000, 1);
}
