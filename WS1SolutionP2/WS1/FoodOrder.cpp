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

using namespace std;
namespace seneca {
	double g_taxrate = 0.0;
	double g_dailydiscount = 0.0;

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

	ostream& FoodOrder::display() const
	{
		static int count = 0;
		++count;

		if (m_customerName[0] == '\0') {
			cout << setw(2) << left << count << ". " << "No Order\n";
		}
		else {
			cout << setw(2) << left << count << ". "
				<< setw(10) << left << m_customerName << '|'
				<< setw(25) << left << m_descriptionFood << '|'
				<< setw(12) << left << fixed << setprecision(2) << m_priceFood * (1 + g_taxrate) << '|';

			if (m_special) {
				cout << setw(13) << right << m_priceFood * (1 + g_taxrate) / g_dailydiscount;
			}

			cout << endl;
		}

		return cout;
	}

	istream& FoodOrder::read(istream& is)
	{
		string customerName;
		string descriptionFood;
		double price = 0.0;
		char symbol = {};
		bool special = false;

		getline(is, customerName, ',');
		m_customerName = new char[customerName.length() + 1];
		strcpy(m_customerName, customerName.c_str());

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
