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
		ConfirmationSender(const ConfirmationSender& src);
		ConfirmationSender& operator=(const ConfirmationSender& src);
		~ConfirmationSender();
		ConfirmationSender& operator+=(const Reservation& res);
		ConfirmationSender& operator-=(const Reservation& res);
		friend std::ostream & operator<<(std::ostream& os, const ConfirmationSender& sender);

		//Move Constructor
		ConfirmationSender(ConfirmationSender&& other) noexcept;

		//Move Assignment Operator
		ConfirmationSender& operator=(ConfirmationSender&& other) noexcept;
	};
}

#endif // !SENECA_CONFIRMATIONSENDER_H
