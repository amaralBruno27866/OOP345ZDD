#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include "Reservation.h"

using namespace std;
namespace seneca {
	Reservation::Reservation() {
		m_reservation_id[0] = '\0';
		m_name = "";
		m_email = "";
		m_party_size = 0;
		m_day = 0;
		m_hour = 0;
	}

	Reservation::Reservation(char reservation_id[10], string name, string email, int party_size, int day, int hour) {
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

	Reservation::Reservation(const string& res) {
		size_t begin = 0;
		size_t end = res.find(':');
		string id = res.substr(begin, end - begin);

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

		m_party_size = stoi(res.substr(begin, end - begin));
		begin = end + 1;
		end = res.find(',', begin);

		m_day = stoi(res.substr(begin, end - begin));
		begin = end + 1;
		end = res.find(',', begin);

		m_hour = stoi(res.substr(begin));
	}

	std::ostream& operator<<(std::ostream& os, const Reservation& res) {
		int temp_id = stoi(res.m_reservation_id);

		// Imprime o ID da reserva e o nome
		os << std::setw(10) << std::right << res.getReservationID(temp_id) << ": "
			<< std::setw(20) << std::right << res.getName() << "  <" << res.getEmail() << ">    ";

		// Determina o tipo de refei��o com base na hora
		std::string meal;

		if (res.getHour() >= 6 && res.getHour() <= 9) {
			meal = "Breakfast";
		}
		else if (res.getHour() >= 11 && res.getHour() <= 15) {
			meal = "Lunch";
		}
		else if (res.getHour() >= 17 && res.getHour() <= 21) {
			meal = "Dinner";
		}
		else {
			meal = "Drinks";
		}

		os << meal << " on day " << res.getDay() << " @ " << res.getHour() << ":00"
			<< " for " << res.getPartySize() << (res.getPartySize() == 1 ? " person." : " people.");

		return os;
	}
}
