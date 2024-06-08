#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include "Reservation.h"

namespace seneca {
	Reservation::Reservation() {
		m_reservation_id[0] = '\0';
		m_name = "";
		m_email = "";
		m_party_size = 0;
		m_day = 0;
		m_hour = 0;
	}

	Reservation::Reservation(char reservation_id[10], std::string name, std::string email, int party_size, int day, int hour) {
		strncpy(m_reservation_id, reservation_id, 9);
		m_reservation_id[9] = '\0';

		m_name = name;
		m_email = email;
		m_party_size = party_size;
		m_day = day;
		m_hour = hour;
	}

	Reservation::Reservation(const Reservation& src) {
		init(src);
	}

	Reservation& Reservation::operator=(const Reservation& src) {
		if (this != &src) {
			init(src);
		}

		return *this;
	}

	Reservation::~Reservation() {

	}

	void Reservation::init(const Reservation& src) {
		strncpy(m_reservation_id, src.m_reservation_id, 9);
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
		std::string id = res.substr(begin, end - begin);

		strncpy(m_reservation_id, id.c_str(), 9);
		m_reservation_id[9] = '\0';
		begin = end + 1;
		end = res.find(',', begin);

		m_name = res.substr(begin, end - begin);
		begin = end + 1;
		end = res.find(',', begin);

		m_email = res.substr(begin, end - begin);
		begin = end + 1;
		end = res.find(',', begin);

		m_party_size = std::stoi(res.substr(begin, end - begin));
		begin = end + 1;
		end = res.find(',', begin);

		m_day = std::stoi(res.substr(begin, end - begin));
		begin = end + 1;
		end = res.find(',', begin);

		m_hour = std::stoi(res.substr(begin));
	}

	std::ostream& operator<<(std::ostream& os, const Reservation& res) {
		// Print the reservation ID, name, and email
		os << "Reservation ";

		os << std::setw(10) << std::left << res.m_reservation_id;
		os << ":";

		os << std::setw(20) << std::right << res.m_name;

		os << " <" << std::setw(24) << std::right << res.m_email << ">";

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
		os << res.m_day << " @ " << std::setw(2) << std::setfill('0') << (res.m_hour % 24) << ":00";
		os << " for " << res.m_party_size << (res.m_party_size == 1 ? " person." : " people.");
		os << std::endl;

		return os;
	}
}
