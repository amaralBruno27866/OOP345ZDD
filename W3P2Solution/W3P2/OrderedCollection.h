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
#ifndef SENECA_ORDERED_COLLECTION_H
#define SENECA_ORDERED_COLLECTION_H

#include <iostream>
#include "Collection.h"

namespace seneca{
    template <typename T>
    class OrderedCollection : public Collection<T, 72> {
    public:
        bool operator+=(const T& item) override {
            if (this->size() >= this->capacity()) {
                return false;
            }
           
            unsigned pos = 0;
            while (pos < this->size() && this->m_items[pos] < item) {
                ++pos;
            }
          
            for (unsigned i = this->size(); i > pos; --i) {
                this->m_items[i] = this->m_items[i - 1];
            }
            
            this->m_items[pos] = item;
            this->incrSize();
            
            this->setSmallestItem(item);
            this->setLargestItem(item);
            return true;
        }
    };
}

#endif // !SENECA_ORDERED_COLLECTION_H
