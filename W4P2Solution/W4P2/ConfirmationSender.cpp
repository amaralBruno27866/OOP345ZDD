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
#include "ConfirmationSender.h"

namespace seneca {
	ConfirmationSender::ConfirmationSender() : m_reservations(nullptr), m_size(0) {}

	ConfirmationSender::ConfirmationSender(const ConfirmationSender& src) : m_reservations(nullptr), m_size(0) {
		*this = src;
	}

	ConfirmationSender& ConfirmationSender::operator=(const ConfirmationSender& src) {
		if (this != &src) {
			delete[] m_reservations; // Libera a memória atual

			m_size = src.m_size;
			if (m_size > 0) {
				m_reservations = new const Reservation * [m_size];
				for (size_t i = 0; i < m_size; ++i) {
					m_reservations[i] = src.m_reservations[i];
				}
			}
			else {
				m_reservations = nullptr;
			}
		}
		return *this;
	}

	ConfirmationSender::~ConfirmationSender() {
		delete[] m_reservations;
	}

	ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res) {
		for (size_t i = 0; i < m_size; ++i) {
			if (m_reservations[i] == &res) {
				return *this;
			}
		}
		const Reservation** temp = new const Reservation * [m_size + 1];
		for (size_t i = 0; i < m_size; ++i) {
			temp[i] = m_reservations[i];
		}
		temp[m_size] = &res;
		delete[] m_reservations;
		m_reservations = temp;
		++m_size;
		return *this;
	}

	ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res) {
		for (size_t i = 0; i < m_size; ++i) {
			if (m_reservations[i] == &res) {
				m_reservations[i] = m_reservations[m_size - 1];
				--m_size;
				const Reservation** temp = new const Reservation * [m_size];
				for (size_t j = 0; j < m_size; ++j) {
					temp[j] = m_reservations[j];
				}
				delete[] m_reservations;
				m_reservations = temp;
				return *this;
			}
		}
		return *this;
	}

	ConfirmationSender::ConfirmationSender(ConfirmationSender&& other) noexcept : m_reservations(other.m_reservations), m_size(other.m_size) {
		other.m_reservations = nullptr;
		other.m_size = 0;
	}

	ConfirmationSender& ConfirmationSender::operator=(ConfirmationSender&& other) noexcept {
		if (this != &other) {
			delete[] m_reservations;

			m_reservations = other.m_reservations;
			m_size = other.m_size;

			other.m_reservations = nullptr;
			other.m_size = 0;
		}
		return *this;
	}

	std::ostream& operator<<(std::ostream& os, const ConfirmationSender& sender) {
		os << "--------------------------" << std::endl;
		os << "Confirmations to Send" << std::endl;
		os << "--------------------------" << std::endl;

		if(sender.m_size == 0) {
			os << "There are no confirmations to send!" << std::endl;
		}
		else {
			for (size_t i = 0; i < sender.m_size; i++) {
				if (sender.m_reservations[i] != nullptr) {
					os << *sender.m_reservations[i];
				}
			}
		}

		os << "--------------------------" << std::endl;

		return os;
	}
}
