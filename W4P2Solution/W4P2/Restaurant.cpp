#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Restaurant.h"

namespace seneca {
	Restaurant::Restaurant(const Reservation* reservations[], size_t cnt) : m_size(cnt) {
		m_reservations = new Reservation * [m_size];
		for (size_t i = 0; i < m_size; i++) {
			m_reservations[i] = new Reservation(*reservations[i]);
		}
	}

	Restaurant::~Restaurant() {
		for (size_t i = 0; i < m_size; i++) {
			delete m_reservations[i];
		}

		delete[] m_reservations;
	}

	std::ostream& operator<<(std::ostream& os, const Restaurant& restaurant) {
		os << "--------------------------" << std::endl;
		os << "Fancy Restaurant (" << ++Restaurant::call_cnt << ")" << std::endl;
		os << "--------------------------" << std::endl;

		if (restaurant.m_size == 0) {
			os << "This restaurant is empty!" << std::endl;
		}
		else {
			for (size_t i = 0; i < restaurant.m_size; i++) {
				os << *restaurant.m_reservations[i] << std::endl;
			}
		}

		os << "--------------------------" << std::endl;

		return os;
	}

	int Restaurant::call_cnt = 0;
}
