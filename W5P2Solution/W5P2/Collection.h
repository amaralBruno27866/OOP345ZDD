#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <string>
#include <stdexcept>

namespace seneca {
	template <typename T>
	class Collection {
	private:
		std::string m_name;
		T* m_items;
		size_t m_size;
		void (*m_observer)(const Collection<T>&, const T&)
	public:
		Collection(const std::string& name);

		// Delete copy operations
		Collections(const Collection&) = delete;
		Collection& operator=(const Collection&) = delete;

		// Destructor
		~Collection();

		~const std::string& name() const { return m_name; };
		size_t size() const { return m_size; };
		void setObserver(void (*observer)(const Collection<T>&, const T&));

		// Add item
		Collection<T>& operator+=(const T& item);

		// Access item by index
		T& operator[](size_t idx) const;

		// Access item by title
		T* operator[](const std::string& title) const;

		// Insetion operator
		template <typename F>
		std::ostream& operator<<(std::ostream& os, const Collection<F>& collection);
	};
}
#endif // !SENECA_COLLECTION_H
