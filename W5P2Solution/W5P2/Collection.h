#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <string>
#include <stdexcept>

namespace seneca {
	template <typename T>
	class Collection {
	private:
		std::string name;
		T* m_items = nullptr;
		size_t m_size = 0;
		void (*m_observer)(const Collection<T>&, const T&) { nullptr };
	public:
		Collection(const std::string& name) {
			this->name = name;
		}

		// Delete copy operations
		Collections(const Collection&) = delete;
		Collection& operator=(const Collection&) = delete;

		// Destructor
		~Collection() {
			delete[] m_items;
		};

		~const std::string& name() const { return m_name; };
		size_t size() const { return m_size; };
		void setObserver(void (*observer)(const Collection<T>&, const T&)){
			m_observer = observer;
		}

		// Add item
		Collection<T>& operator+=(const T& item) {
			// Check if item is already in the collection
			for (size_t i = 0; i < m_size; ++i) {
				if (m_items[i].title() == item.title()) {
					return *this; // Item found, do nothing
				}
			}

			// Item not found, add new item
			T* temp = new T[m_size + 1];
			for (size_t i = 0; i < m_size; ++i) {
				temp[i] = m_items[i];
			}
			temp[m_size] = item;
			delete[] m_items;
			m_items = temp;
			++m_size;

			// Call observer if registered
			if (m_observer) {
				m_observer(*this, item);
			}

			return *this;
		};

		// Access item by index
		T& operator[](size_t idx) const {
			if (idx >= m_size) {
				throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items.");
			}
			return m_items[idx];
		}

		// Access item by title
		T* operator[](const std::string& title) const {
			for (size_t i = 0; i < m_size; ++i) {
				if (m_items[i].title() == title) {
					return &m_items[i];
				}
			}
			return nullptr;
		}

		// Insetion operator
		template <typename F>
		std::ostream& operator<<(std::ostream& os, const Collection<F>& collection) {
			for (size_t i = 0; i < collection.size(); ++i) {
				os << collection[i];
			}
			return os;
		}
	};
}
#endif // !SENECA_COLLECTION_H
