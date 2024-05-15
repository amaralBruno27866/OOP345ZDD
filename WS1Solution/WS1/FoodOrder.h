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

#ifndef SENECA_FOODORDER_H
#define SENECA_FOODORDER_H

#include <iostream>
#include <cstring>
#include <string.h>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;
namespace seneca {
	extern double g_taxrate;
	extern double g_dailydiscount;

	class FoodOrder	
	{
	private:
		char m_customerName[10];
		char m_descriptionFood[25];
		double m_priceFood;
		bool m_special;
	public:
		FoodOrder();
		FoodOrder(char customerName[10], char descriptionFood[25], double price, bool special);
		FoodOrder(const FoodOrder& order);
		FoodOrder& operator=(const FoodOrder& order);
		~FoodOrder();
		void init(const FoodOrder& order);

		char getCustomerName() const { return *m_customerName; };
		char getDescriptionFood() const { return *m_descriptionFood; };
		double getPrice() const { return m_priceFood; };
		bool getSpecial() const { return m_special; };

		ostream& display() const;
		istream& read(istream& is);

		bool wordSize(const char* word, int size);
		void cpWord(char* word, char* target, int size);
	};
}

#endif // !SENECA_FOODORDER_H
