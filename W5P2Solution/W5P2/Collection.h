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

#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <cstddef>
#include <stdexcept>
#include <string>

namespace seneca {
	template <typename T>
	class Collection {
	private:
		std::string m_name;
		T* m_items = nullptr;
		size_t m_size = 0;
		void (*m_observer)(const Collection<T>&, const T&) = nullptr;
	public:
        Collection(const std::string& name) : m_name(name) {}
        ~Collection() { delete[] m_items; }
        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;

        const std::string& name() const { return m_name; }
        size_t size() const { return m_size; }

        void setObserver(void (*observer)(const Collection<T>&, const T&)) {
            m_observer = observer;
        }

        Collection<T>& operator+=(const T& item) {
            // Check if item is already in the collection
            for (size_t i = 0; i < m_size; ++i) {
                if (m_items[i].title() == item.title()) return *this; // Item already exists
            }

            // Add new item
            T* temp = new T[m_size + 1];
            for (size_t i = 0; i < m_size; ++i) {
                temp[i] = m_items[i];
            }
            temp[m_size] = item;
            ++m_size;
            delete[] m_items;
            m_items = temp;

            // Notify observer if set
            if (m_observer) m_observer(*this, item);

            return *this;
        }

        T& operator[](size_t idx) const {
            if (idx >= m_size) throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items.");
            return m_items[idx];
        }

        T* operator[](const std::string& title) const {
            for (size_t i = 0; i < m_size; ++i) {
                if (m_items[i].title() == title) return &m_items[i];
            }
            return nullptr;
        }
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const Collection<T>& collection) {
        for (size_t i = 0; i < collection.size(); ++i) {
            out << collection[i];
        }
        return out;
    }
}
#endif // !SENECA_COLLECTION_H
