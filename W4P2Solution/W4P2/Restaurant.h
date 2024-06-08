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
		~Restaurant();
		size_t size()const { return m_size; };
		friend std::ostream& operator<<(std::ostream& os, const Restaurant& restaurant);
	};
}

#endif // !SENECA_RESTAURANT_H
