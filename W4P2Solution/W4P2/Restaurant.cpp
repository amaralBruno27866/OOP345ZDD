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
#include "Restaurant.h"

namespace seneca {
	int Restaurant::call_cnt = 0;

	Restaurant::Restaurant(const Reservation* reservations[], size_t cnt) : m_reservations(nullptr), m_size(cnt) {
		m_reservations = new Reservation * [cnt];
		for (size_t i = 0; i < cnt; ++i) {
			m_reservations[i] = new Reservation(*reservations[i]);
		}
	}

	Restaurant::Restaurant(const Restaurant& ot) : m_reservations(nullptr), m_size(0) {
		*this = ot;
	}

	Restaurant& Restaurant::operator=(const Restaurant& ot) {
		if (this != &ot) {
			for (size_t i = 0; i < m_size; ++i) {
				delete m_reservations[i];
			}
			delete[] m_reservations;

			m_size = ot.m_size;
			m_reservations = new Reservation * [ot.m_size];
			for (size_t i = 0; i < ot.m_size; ++i) {
				m_reservations[i] = new Reservation(*ot.m_reservations[i]);
			}
		}
		return *this;
	}

	Restaurant::~Restaurant() {
		if (m_reservations != nullptr) {
			for (size_t i = 0; i < m_size; ++i) {
				delete m_reservations[i];
			}
			delete[] m_reservations;
		}
	}

	Restaurant::Restaurant(Restaurant&& other) noexcept : m_reservations(other.m_reservations), m_size(other.m_size) {
		other.m_reservations = nullptr;
		other.m_size = 0;
	}

	Restaurant& Restaurant::operator=(Restaurant&& other) noexcept {
		if (this != &other) {
			for (size_t i = 0; i < m_size; ++i) {
				delete m_reservations[i];
			}
			delete[] m_reservations;

			m_reservations = other.m_reservations;
			m_size = other.m_size;

			other.m_reservations = nullptr;
			other.m_size = 0;
		}
		return *this;
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
				os << *restaurant.m_reservations[i];
			}
		}

		os << "--------------------------" << std::endl;

		return os;
	}
}
