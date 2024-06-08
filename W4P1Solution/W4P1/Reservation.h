#ifndef SENECA_RESERVATION_H
#define SENECA_RESERVATION_H

#include <iostream>
#include <string>

namespace seneca {
	class Reservation {
	private:
		char m_reservation_id[10]; // array de caracteres para o id da reserva
		std::string m_name; // nome na reserva
		std::string m_email; // email para enviar a confirmação
		int m_party_size; // número de pessoas na reserva
		int m_day; // dia da reserva
		int m_hour; // hora da reserva
	public:
		Reservation();
		Reservation(char reservation_id[10], std::string name, std::string email, int party_size, int day, int hour);
		Reservation(const Reservation& src);
		Reservation& operator=(const Reservation& src);
		~Reservation();
		void init(const Reservation& src);

		char getReservationID(int index) const;
		std::string getName() const { return m_name; };
		std::string getEmail() const { return m_email; };
		int getPartySize() const { return m_party_size; };
		int getDay() const { return m_day; };
		int getHour() const { return m_hour; };

		// Modificador que atualiza o dia e a hora da reserva
		void update(int day, int time);

		// Construtor que extrai informações de uma string e inicializa os membros de dados
		Reservation(const std::string& res);

		// Sobrecarga do operador de inserção para imprimir os detalhes da reserva
		friend std::ostream& operator<<(std::ostream& os, const Reservation& res);
	};
}

#endif // !SENECA_RESERVATION_H
