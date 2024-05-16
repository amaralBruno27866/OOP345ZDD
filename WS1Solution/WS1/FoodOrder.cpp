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
	FoodOrder::FoodOrder()
	{
		m_customerName[0] = '\0';
		m_descriptionFood[0] = '\0';
		m_priceFood = 0.0;
		m_special = false;

	}

	FoodOrder::FoodOrder(char customerName[10], char descriptionFood[25], double price, bool special)
	{
		strncpy(m_customerName, customerName, sizeof(m_customerName) - 1);
		m_customerName[sizeof(m_customerName) - 1] = '\0';

		strncpy(m_descriptionFood, descriptionFood, sizeof(m_descriptionFood) - 1);
		m_descriptionFood[sizeof(m_descriptionFood) - 1] = '\0';

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
	}

	void FoodOrder::init(const FoodOrder& order)
	{
		m_customerName[0] = '\0';
		strncpy(m_customerName, order.m_customerName, sizeof(m_customerName) - 1);
		m_customerName[sizeof(m_customerName) - 1] = '\0';

		m_descriptionFood[0] = '\0';
		strncpy(m_descriptionFood, order.m_descriptionFood, sizeof(m_descriptionFood) - 1);
		m_descriptionFood[sizeof(m_descriptionFood) - 1] = '\0';

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
		char customerName[10] = {};
		char descriptionFood[25] = {};
		double price = 0.0;
		char symbol = {};
		bool special = false;

		is.getline(customerName, sizeof(customerName), ',');
		if (is.fail()) {
			is.clear();
			is.ignore(10000, '\n');
		}

		is.getline(descriptionFood, sizeof(descriptionFood), ',');
		if (is.fail()) {
			is.clear();
			is.ignore(10000, '\n');
		}

		is >> price;
		if (is.fail()) {
			is.clear();
			is.ignore(10000, '\n');
		}

		is.ignore();

		is >> symbol;

		special = (symbol == 'Y');

		cpWord(customerName, m_customerName, sizeof(m_customerName));
		cpWord(descriptionFood, m_descriptionFood, sizeof(m_descriptionFood));
		m_priceFood = price;
		m_special = special;

		return is;
	}

	bool FoodOrder::wordSize(const char* word, int size)
	{
		bool isValid = false;

		if (word != nullptr && word[0] != '\0') {
			size_t val = strlen(word);
			if (val <= static_cast<size_t>(size)) {
				isValid = true;
			}
		}

		return isValid;
	}

	void FoodOrder::cpWord(char* word, char* target, int size)
	{
		if (wordSize(word, size)) {
			strncpy(target, word, size);
			target[size - 1] = '\0';
		}
		else {
			int max = size - 1;
			strncpy(target, word, max);
			target[max] = '\0';
		}
	}
}
