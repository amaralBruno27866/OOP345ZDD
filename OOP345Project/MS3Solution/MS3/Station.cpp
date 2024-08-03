// Name: Bruno Amaral
// Seneca Student ID: 143766228
// Seneca email: bamaral2@myseneca.ca
// Date of completion: August 4th, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"

namespace seneca {
	// Initialize the width field to zero.
	size_t Station::m_widthField = 0;

	// Initialize the ID generator to zero.
	int Station::id_generator = 0;

	// Initializes a Station object with the record received.
	Station::Station(const std::string& record) {
		// Extract the tokens from the record.
		Utilities u;

		// Extract the tokens from the record.
		size_t next_pos = 0;

		// Default to more tokens.
		bool more = true;

		// Extract the tokens.
		m_itemName = u.extractToken(record, next_pos, more);
		m_serialNumber = std::stoi(u.extractToken(record, next_pos, more));
		m_quantityInStock = std::stoi(u.extractToken(record, next_pos, more));

		m_widthField = std::max(m_widthField, u.getFieldWidth());

		// If there are more tokens, extract them.
		if (more) {
			m_stationDesc = u.extractToken(record, next_pos, more);
		}

		// Set the ID of the station.
		m_id = ++id_generator;
	}

	// Returns the name of the item.
	const std::string& Station::getItemName() const {
		return m_itemName;
	}

	// Returns the next serial number to be assigned.
	size_t Station::getNextSerialNumber() {
		return m_serialNumber++;
	}

	// Returns the quantity of items in stock.
	size_t Station::getQuantity() const {
		return m_quantityInStock;
	}

	// Updates the quantity of items in stock.
	void Station::updateQuantity() {
		// If the quantity in stock is greater than zero, decrement it.
		if (m_quantityInStock > 0) {
			--m_quantityInStock;
		}
	}

	// Displays the station information.
	void Station::display(std::ostream& os, bool full) const {
		os << std::setw(3) << std::right << std::setfill('0') << m_id << " | ";
		os << " | ";
		os << std::left << std::setw(14) << std::setfill(' ') << m_itemName;
		os << " | ";
		os << std::right << std::setw(6) << std::setfill('0') << m_serialNumber;
		os << " | ";
		if (full) {
			os << std::right << std::setw(4) << std::setfill(' ') << m_quantityInStock;
			os << " | ";
			os << m_stationDesc;
		}
		os << std::endl;
	}
}
