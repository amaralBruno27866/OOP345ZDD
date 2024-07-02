// Name: Bruno Amaral
// Seneca Student ID: 143766228
// Seneca email: bamaral2@myseneca.ca
// Date of completion:
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#ifndef SENECA_CUSTOMERORDER_H
#define SENECA_CUSTOMERORDER_H

#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace seneca {
	// The Station class represents a station in a factory.
	class Item {
	public:
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		// Initializes an Item object with the name of the item.
		Item(const std::string& src) : m_itemName(src) {};
	};

	// The CustomerOrder class manages a customer order.
	class CustomerOrder {
	public:
		std::string m_name; // The name of the customer
		std::string m_product; // The name of the product
		size_t m_cntItem; // The number of items in the customer's order
		Item** m_lstItem; // The list of items in the customer's order
		static size_t m_widthField; // The maximum field width
	public:
		// Initializes a CustomerOrder object.
		CustomerOrder();

		// Initializes a CustomerOrder object with the record received.
		CustomerOrder(const std::string& str);

		// Prevents copying and copying assignment of CustomerOrder objects.
		CustomerOrder(const CustomerOrder&);

		// Prevents copying and copying assignment of CustomerOrder objects.
		CustomerOrder& operator=(const CustomerOrder&);

		// Move copy constructor
		CustomerOrder(CustomerOrder&& oth) noexcept;

		// Move assignment operator
		CustomerOrder& operator=(CustomerOrder&& oth) noexcept;

		// Destructor
		~CustomerOrder();

		// Throws an exception if the object is in an invalid state.
		bool isOrderFilled() const;

		// Returns the name of the item at index i.
		bool isItemFilled(const std::string& itemName) const;

		// Fills the item in the customer's order.
		void fillItem(Station& station, std::ostream& os);

		// Displays the customer's order.
		void display(std::ostream& os) const;
	};
}

#endif // !SENECA_CUSTOMERORDER_H
