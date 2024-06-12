#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <cstddef>
#include <stdexcept>

namespace seneca {
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

			if (callback) {
				callback(item);
			}
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
#endif // !SENECA_COLLECTION_H
