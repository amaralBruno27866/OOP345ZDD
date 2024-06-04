/*/////////////////////////////////////////////////////////////////////////
                          Workshop - #3 P2
Full Name  : Bruno Amaral
Student ID#: 143766228
Email      : bamaral2@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/
#ifndef SENECA_ORDEREDCOLLECTION_H
#define SENECA_ORDEREDCOLLECTION_H

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

#endif // !SENECA_ORDEREDCOLLECTION_H
