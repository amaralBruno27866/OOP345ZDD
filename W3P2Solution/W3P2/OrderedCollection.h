#ifndef SENECA_ORDERED_COLLECTION_H
#define SENECA_ORDERED_COLLECTION_H

#include "Collection.h"

namespace seneca {
	template<typename T>
	class OrderedCollection : public Collection<T, 72> {
	public:
        bool operator+=(const T& it) override {
            if (this->size() >= this->capacity()) {
                return false;
            }

            unsigned pos = 0;
            while (pos < this->size() && this->getItem(pos) < it) {
                ++pos;
            }

            for (unsigned int i = this->size(); i > pos; --i) {
                this->getItem(i) = this->getItem(i - 1);
            }

            this->incrSize();
            this->getItem(pos) = it;

            this->setSmallestItem(it);
            this->setLargestItem(it);

            return true;
        }
	};
}

#endif // !SENECA_ORDERED_COLLECTION_H
