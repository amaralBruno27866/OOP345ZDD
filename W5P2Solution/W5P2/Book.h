/*/////////////////////////////////////////////////////////////////////////
				  Workshop - #5 P2
Full Name  : Bruno Amaral
Student ID#: 143766228
Email      : bamaral2@myseneca.ca
Section    : ZDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SENECA_BOOK_H // Diretiva de pr�-processador para evitar inclus�es m�ltiplas
#define SENECA_BOOK_H

#include <iostream>
#include <iomanip>
#include <string>

namespace seneca { // Uso de namespace para evitar conflitos de nome
	class Book { // Defini��o de uma classe chamada Book
	private:
		std::string m_author; // Membros de dados privados
		std::string m_title;
		std::string m_country;
		size_t m_year;
		double m_price;
		std::string m_description;

	public:
		Book(); // Construtor padr�o
		Book(std::string author, std::string title, std::string country, int year, double price, std::string description); // Construtor parametrizado
		Book(const Book& book); // Construtor de c�pia
		Book& operator=(const Book& book); // Operador de atribui��o de c�pia
		~Book(); // Destrutor

		// M�todos de acesso (getters)
		std::string getAuthor() const { return m_author; }
		std::string getDescription() const { return m_description; }

		const std::string& title() const { return m_title; }
		const std::string& country() const { return m_country; }
		const size_t& year() const { return m_year; }
		double& price() { return m_price; }

		Book(const std::string& strBook); // Construtor que aceita uma string formatada

		friend std::ostream& operator<<(std::ostream& os, const Book& book); // Declara��o de fun��o amiga para sobrecarregar o operador de inser��o

		// Template de m�todo para corrigir a ortografia (exemplo de template de fun��o)
		template<typename T>
		void fixSpelling(T& spellChecker) {
			spellChecker(m_description);
		}
	};
}

#endif // !SENECA_BOOK_H

