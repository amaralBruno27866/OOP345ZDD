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

#ifndef SENECA_RESERVATION_H
#define SENECA_RESERVATION_H

#include <iostream>
#include <string>

namespace seneca {
	class Reservation {
	private:
		char m_reservation_id[11];
		std::string m_name;
		std::string m_email;
		int m_party_size;
		int m_day;
		int m_hour;
	public:
		Reservation();
		Reservation(const char* reservation_id, std::string name, std::string email, int party_size, int day, int hour);
		Reservation(const Reservation& src);
		Reservation& operator=(const Reservation& src);
		~Reservation();
		void init(const Reservation& src);

		char getReservationID(int index) const;
		std::string getName() const { return m_name; };
		std::string getEmail() const { return m_email; };
		int getPartySize() const { return m_party_size; };
		int getDay() const { return m_day; };
		int getHour() const { return m_hour; };

		void update(int day, int time);
		Reservation(const std::string& res);
		friend std::ostream& operator<<(std::ostream& os, const Reservation& res);
		
		//Move Constructor
		Reservation(Reservation&& other) noexcept;

		//Move Assignment Operator
		Reservation& operator=(Reservation&& other) noexcept;
	};
}

#endif // !SENECA_RESERVATION_H
