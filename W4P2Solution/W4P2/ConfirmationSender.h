#ifndef SENECA_CONFIRMATIONSENDER_H
#define SENECA_CONFIRMATIONSENDER_H

#include <iostream>
#include <string>
#include "Reservation.h"

namespace seneca {
	class ConfirmationSender {
		const Reservation** m_reservations;
		size_t m_size;
	public:
		ConfirmationSender();
		ConfirmationSender& operator+=(const Reservation& res);
		ConfirmationSender& operator-=(const Reservation& res);
		friend std::ostream & operator<<(std::ostream& os, const ConfirmationSender& sender);
	};
}

#endif // !SENECA_CONFIRMATIONSENDER_H
