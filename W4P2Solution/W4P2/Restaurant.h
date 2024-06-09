/*/////////////////////////////////////////////////////////////////////////
				  Workshop - #4 P2
Full Name  : Bruno Amaral
Student ID#: 143766228
Email      : bamaral2@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SENECA_RESTAURANT_H
#define SENECA_RESTAURANT_H

#include <iostream>
#include <string>
#include "Reservation.h"

namespace seneca {
	class Restaurant {
		Reservation** m_reservations;
		size_t m_size;
		static int call_cnt;
	public:
		Restaurant(const Reservation* reservations[], size_t cnt);
		Restaurant(const Restaurant& ot);
		Restaurant& operator=(const Restaurant& ot);
		~Restaurant();
		size_t size() const { return m_size; };
		friend std::ostream& operator<<(std::ostream& os, const Restaurant& restaurant);

		// Move Constructor
		Restaurant(Restaurant&& other) noexcept;

		// Move Assignment Operator
		Restaurant& operator=(Restaurant&& other) noexcept;
	};
}

#endif // !SENECA_RESTAURANT_H
