// Name: Bruno Amaral
// Seneca Student ID: 143766228
// Seneca email: bamaral2@myseneca.ca
// Date of completion: August 4th, 2024
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SENECA_STATION_H
#define SENECA_STATION_H

#include <iostream>
#include <string>
#include "Utilities.h"

namespace seneca {
	// The Station class represents a station in a factory.
	class Station {
		int m_id; // The ID of the station
		std::string m_itemName; // The name of the item
		std::string m_stationDesc; // The description of the station
		size_t m_serialNumber; // The next serial number to be assigned
		size_t m_quantityInStock; // The quantity of items in stock
		static size_t m_widthField; // The maximum field width
		static int id_generator; // The ID generator
	public:
		// Initializes a Station object with the record received.
		Station(const std::string& record);

		// Returns the name of the item.
		const std::string& getItemName() const;

		// Returns the next serial number to be assigned.
		size_t getNextSerialNumber();

		// Returns the quantity of items in stock.
		size_t getQuantity() const;

		// Updates the quantity of items in stock.
		void updateQuantity();

		//	Displays the station information.
		void display(std::ostream& os, bool full) const;
	};
}

#endif // !SENECA_STATION_H
