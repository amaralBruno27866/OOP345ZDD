#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace seneca {
	template <typename T>
	class Collection {
	private:
		std::string m_name;
		std::vector<T> m_items;
		void (*m_observer)(const Collection<T>&, const T&);
	public:
		Collection(const std::string& name):m_name(name), m_observer(nullptr) {}
		const std::string& name() const { return m_name; };
		size_t size() const { return m_items.size(); };

		void setObserver(void(*obeserver)(const Collection<T>&, const T&)) {
			m_observer = obeserver;
		}

		Collection<T>& operator+=(const T& item) {
			auto isTitleMatch = [&](const T& i) { return i.title() == item.title(); };

			auto it = std::find_if(m_items.begin(), m_items.end(), isTitleMatch);

			bool itemExists = it != m_items.end();

			if (!itemExists) {
				m_items.push_back(item);
				if (m_observer) {
					m_observer(*this, item);
				}
			}

			return *this;
		}

		const T& operator[](size_t idx) const {
			if (idx >= m_items.size()) {
				std::string errorMessage = "Bad index [";
				errorMessage += std::to_string(idx);
				errorMessage += "]. Collection has [";
				errorMessage += std::to_string(m_items.size());
				errorMessage += "] items.";
				throw std::out_of_range(errorMessage);
			}

			return m_items[idx];
		}

		T* operator[](const std::string& title) const {
			auto isTitleMatch = [&](const T& i) { return i.title() == title; };

			auto it = std::find_if(m_items.begin(), m_items.end(), isTitleMatch);

			return it != m_items.end() ? &(*it) : nullptr;
		}

		friend std::ostream& operator<<(std::ostream& os, const Collection<T>& collection) {
			for (const auto& item : collection.m_items) {
				os << item;
			}
			return os;
		}
	};
}
#endif // !SENECA_COLLECTION_H
