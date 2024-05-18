/*/////////////////////////////////////////////////////////////////////////
						  Workshop - #1 P1
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
#include <cstring>
#include <string.h>
#include <string>
#include <iomanip>
#include <fstream>

#include "FoodOrder.h"

double g_taxrate = 0.0;
double g_dailydiscount = 0.0;

namespace seneca {
	FoodOrder::FoodOrder()
	{
		m_customerName = nullptr;
		m_descriptionFood = nullptr;
		m_priceFood = 0.0;
		m_special = false;

	}

	FoodOrder::FoodOrder(char* customerName, char* descriptionFood, double price, bool special)
	{
		m_customerName = new char[strlen(customerName) + 1];
		strcpy(m_customerName, customerName);

		m_descriptionFood = new char[strlen(descriptionFood) + 1];
		strcpy(m_descriptionFood, descriptionFood);

		m_priceFood = price;
		m_special = special;
	}

	FoodOrder::FoodOrder(const FoodOrder& order)
	{
		init(order);
	}

	FoodOrder& FoodOrder::operator=(const FoodOrder& order)
	{
		if (this != &order) {
			init(order);
		}
		return *this;
	}

	FoodOrder::~FoodOrder()
	{
		delete[] m_customerName;
		m_customerName = nullptr;
		delete[] m_descriptionFood;
		m_descriptionFood = nullptr;
	}

	void FoodOrder::init(const FoodOrder& order)
	{
		m_customerName = nullptr;
		m_customerName = new char[strlen(order.m_customerName) + 1];
		strcpy(m_customerName, order.m_customerName);

		m_descriptionFood = nullptr;
		m_descriptionFood = new char[strlen(order.m_descriptionFood) + 1];
		strcpy(m_descriptionFood, order.m_descriptionFood);

		m_priceFood = order.m_priceFood;
		m_special = order.m_special;
	}

	std::ostream& FoodOrder::display() const
	{
		static int count = 0;
		++count;

		double priceWithTax = (m_priceFood * g_taxrate) + m_priceFood;

		double specialPrice = priceWithTax - g_dailydiscount;


		if (m_customerName[0] == '\0') {
			std::cout << std::setw(2) << std::left << count << ". " << "No Order\n";
		}
		else {
			std::cout << std::setw(2) << std::left << count << ". "
				<< std::setw(10) << std::left << m_customerName << '|'
				<< std::setw(25) << std::left << m_descriptionFood << '|'
				<< std::setw(12) << std::left << std::fixed 
				<< std::setprecision(2) << priceWithTax << '|';

			if (m_special) {
				std::cout << std::setw(13) << std::right << specialPrice;
			}

			std::cout << std::endl;
		}

		return std::cout;
	}

	std::istream& FoodOrder::read(std::istream& is)
	{
		std::string customerName;
		std::string descriptionFood;
		double price = 0.0;
		signed char symbol = {};
		bool special = false;

		delete[] m_customerName;
		getline(is, customerName, ',');
		m_customerName = new char[customerName.length() + 1];
		strcpy(m_customerName, customerName.c_str());

		delete[] m_descriptionFood;
		getline(is, descriptionFood, ',');
		m_descriptionFood = new char[descriptionFood.length() + 1];
		strcpy(m_descriptionFood, descriptionFood.c_str());

		is >> price;
		if (is.fail()) {
			is.clear();
			is.ignore(10000, '\n');
		}

		is.ignore();

		is >> symbol;

		special = (symbol == 'Y');

		m_priceFood = price;
		m_special = special;		

		return is;
	}
}
