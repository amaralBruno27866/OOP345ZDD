#ifndef SENECA_COLLECTION_H
#define SENECA_COLLECTION_H

#include <iostream>
#include <string>
#include <stdexcept>

namespace seneca {
    template <typename T>
    class Collection {
    private:
        T* items;
        size_t size;
        std::string name;
        void (*observer)(const Collection<T>&, const T&) = nullptr;

    public:
        Collection(const std::string& name = "") : items(nullptr), size(0), name(name) {}

        ~Collection() { delete[] items; }

        Collection(const Collection&) = delete;
        Collection& operator=(const Collection&) = delete;

        const std::string& getName() const { return name; }
        size_t getSize() const { return size; }

        void setObserver(void (*obs)(const Collection<T>&, const T&)) {
            observer = obs;
        }

        Collection<T>& operator+=(const T& item) {
            for (size_t i = 0; i < size; ++i) {
                if (items[i].title() == item.title()) {
                    return *this; // Item already exists
                }
            }
            T* temp = new T[size + 1];
            for (size_t i = 0; i < size; ++i) {
                temp[i] = items[i];
            }
            temp[size++] = item;
            delete[] items;
            items = temp;
            if (observer) observer(*this, item);
            return *this;
        }

        T& operator[](size_t idx) const {
            if (idx >= size) {
                throw std::out_of_range("Bad index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(size) + "] items.");
            }
            return items[idx];
        }

        T* operator[](const std::string& title) const {
            for (size_t i = 0; i < size; ++i) {
                if (items[i].title() == title) {
                    return &items[i];
                }
            }
            return nullptr;
        }
    };

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Collection<T>& collection) {
        for (size_t i = 0; i < collection.getSize(); ++i) {
            os << collection[i];
        }
        return os;
    }
}
#endif // !SENECA_COLLECTION_H
