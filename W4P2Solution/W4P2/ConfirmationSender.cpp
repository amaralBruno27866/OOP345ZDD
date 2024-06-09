#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "ConfirmationSender.h"

namespace seneca {
	ConfirmationSender::ConfirmationSender() : m_reservations(nullptr), m_size(0) {}

	ConfirmationSender& ConfirmationSender::operator+=(const Reservation& res) {
		bool isTrue = false;
		size_t i = 0;

		while (i < m_size && !isTrue) {
			if (m_reservations[i] == &res) {
				isTrue = true;
			}
			else {
				i++;
			}
		}

		if (!isTrue) {
			const Reservation** temp = new const Reservation * [m_size + 1];
			for (size_t j = 0; j < m_size; j++) {
				temp[j] = m_reservations[j];
			}
			temp[m_size] = &res;
			delete[] m_reservations;
			m_reservations = temp;
			m_size++;
		}

		return *this;
	}

	ConfirmationSender& ConfirmationSender::operator-=(const Reservation& res) {
		bool isTrue = false;
		size_t i = 0;

		while (i < m_size && !isTrue) {
			if (m_reservations[i] == &res) {
				m_reservations[i] = nullptr;
				isTrue = true;
			}
			else {
				i++;
			}
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
					os << *sender.m_reservations[i] << std::endl;
				}
			}
		}

		os << "--------------------------" << std::endl;

		return os;
	}
}
