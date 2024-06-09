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

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include "Reservation.h"

namespace seneca {
	Reservation::Reservation() : m_reservation_id{}, m_name(""), m_email(""), m_party_size(0), m_day(0), m_hour(0) {}

	Reservation::Reservation(const char* reservation_id, std::string name, std::string email, int party_size, int day, int hour)
		: m_name(name), m_email(email), m_party_size(party_size), m_day(day), m_hour(hour) 
	{
		strncpy(m_reservation_id, reservation_id, sizeof(m_reservation_id) - 1);
		m_reservation_id[sizeof(m_reservation_id) - 1] = '\0';
	}

	Reservation::Reservation(const Reservation& src) {
		*this = src;
	}

	Reservation& Reservation::operator=(const Reservation& src) {
		if (this != &src) {
			strncpy(m_reservation_id, src.m_reservation_id, sizeof(m_reservation_id) - 1);
			m_reservation_id[sizeof(m_reservation_id) - 1] = '\0';
			m_name = src.m_name;
			m_email = src.m_email;
			m_party_size = src.m_party_size;
			m_day = src.m_day;
			m_hour = src.m_hour;
		}
		return *this;
	}

	Reservation::~Reservation() {}

	void Reservation::init(const Reservation& src) {
		strncpy(m_reservation_id, src.m_reservation_id, 10);
		m_reservation_id[9] = '\0';

		m_name = src.m_name;
		m_email = src.m_email;
		m_party_size = src.m_party_size;
		m_day = src.m_day;
		m_hour = src.m_hour;
	}

	char Reservation::getReservationID(int index) const {
		char result = '\0';

		if (index >= 0 && index < 10) {
			result = m_reservation_id[index];
		}

		return result;
	}

	void Reservation::update(int day, int time) {
		this->m_day = day;
		this->m_hour = time;
	}

	Reservation::Reservation(const std::string& res) {
		size_t begin = 0;
		size_t end = res.find(':');

		// Extracting the reservation ID
		std::string id = res.substr(begin, end - begin);
		id.erase(0, id.find_first_not_of(' '));
		id.erase(id.find_last_not_of(' ') + 1);
		strncpy(m_reservation_id, id.c_str(), 10);
		m_reservation_id[10] = '\0';

		begin = end + 1;
		end = res.find(',', begin);

		// Extracting the name
		std::string name = res.substr(begin, end - begin);
		name.erase(0, name.find_first_not_of(' '));
		name.erase(name.find_last_not_of(' ') + 1);
		m_name = name;

		begin = end + 1;
		end = res.find(',', begin);

		// Extracting the email
		std::string email = res.substr(begin, end - begin);
		email.erase(0, email.find_first_not_of(' '));
		email.erase(email.find_last_not_of(' ') + 1);
		email.insert(0, "<");
		email.append(">");
		m_email = email;

		begin = end + 1;
		end = res.find(',', begin);

		// Extracting the number of people
		std::string party_size_str = res.substr(begin, end - begin);
		party_size_str.erase(0, party_size_str.find_first_not_of(' '));
		party_size_str.erase(party_size_str.find_last_not_of(' ') + 1);
		m_party_size = std::stoi(party_size_str);

		begin = end + 1;
		end = res.find(',', begin);

		// Extracting the day
		std::string day_str = res.substr(begin, end - begin);
		day_str.erase(0, day_str.find_first_not_of(' '));
		day_str.erase(day_str.find_last_not_of(' ') + 1);
		m_day = std::stoi(day_str);

		begin = end + 1;

		// Extracting the hour
		std::string hour_str = res.substr(begin);
		hour_str.erase(0, hour_str.find_first_not_of(' '));
		hour_str.erase(hour_str.find_last_not_of(' ') + 1);
		m_hour = std::stoi(hour_str);	
	}

	Reservation::Reservation(Reservation&& other) noexcept
		: m_reservation_id{}, m_name(std::move(other.m_name)), m_email(std::move(other.m_email)),
		m_party_size(other.m_party_size), m_day(other.m_day), m_hour(other.m_hour) {
		strncpy(m_reservation_id, other.m_reservation_id, sizeof(m_reservation_id) - 1);
		m_reservation_id[sizeof(m_reservation_id) - 1] = '\0';
		other.m_reservation_id[0] = '\0';
		other.m_party_size = 0;
		other.m_day = 0;
		other.m_hour = 0;
	}

	Reservation& Reservation::operator=(Reservation&& other) noexcept {
		if (this != &other) {
			strncpy(m_reservation_id, other.m_reservation_id, sizeof(m_reservation_id) - 1);
			m_reservation_id[sizeof(m_reservation_id) - 1] = '\0';
			m_name = std::move(other.m_name);
			m_email = std::move(other.m_email);
			m_party_size = other.m_party_size;
			m_day = other.m_day;
			m_hour = other.m_hour;

			other.m_reservation_id[0] = '\0';
			other.m_party_size = 0;
			other.m_day = 0;
			other.m_hour = 0;
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const Reservation& res) {
		// Print the reservation ID, name, and email
		os << "Reservation ";

		os << std::setw(10) << std::setfill(' ') << std::right << res.m_reservation_id;
		os << ": ";

		os << std::setw(20) << std::setfill(' ') << std::right << res.m_name;

		os << "  ";
		os << std::setw(20) << std::left << res.m_email;

		// Determine the meal type based on the hour
		std::string meal;
		if (res.m_hour >= 6 && res.m_hour <= 9) {
			meal = "Breakfast";
		}
		else if (res.m_hour >= 11 && res.m_hour <= 15) {
			meal = "Lunch";
		}
		else if (res.m_hour >= 17 && res.m_hour <= 21) {
			meal = "Dinner";
		}
		else {
			meal = "Drinks";
		}

		// Print the meal type, day, hour, and party size
		os << "    " << meal << " on day ";
		os << res.m_day << " @ ";
		
		std::string time = res.m_hour < 10 ? "" + std::to_string(res.m_hour) : std::to_string(res.m_hour);
		os << time << ":00";

		os << " for " << res.m_party_size << (res.m_party_size == 1 ? " person." : " people.");
		os << std::endl;

		return os;
	}
}
