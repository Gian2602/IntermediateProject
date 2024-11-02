#ifndef Book_h
#define Book_h

#include <exception>
#include "ISBN.h"
#include "Date.h"

class Book{

public:

	/*Per costruire l'oggetto devo passare isbn titolo nome e cognome autore
		non è invece necessario passare la data di copyright.
		nel caso non venga specificato in quale stato sia il libro (prestito o in biblioteca)
		viene inizializzato come presente in biblioteca (in quanto viene registrato da lì)*/

	Book(std::string name, std::string surname, std::string title, std::string isbn, std::string copy_date = "", bool disp = true);
	Book();

	ISBN get_isbn() const; //restituisce il codice isbn
	std::string get_title() const; //restituisce il titolo del libro
	std::string get_name() const; //restituisce il nome dell'autore
	std::string get_surname() const; //restituisce il cognome dell'autore
	Date get_Date() const; //restituisce la data di copyright
	bool get_disponibility() const; //restituisce la disponibilità del libro (true se presente)

	bool reserve_book(); //fuonzione che permette di riservare il libro (libro non più disponibile)
	bool return_book(); //funzione che permette di restituire il libro (libro disponibile)

	bool operator==(Book& book) const; //overload dell'operatore == i due libri sono equivalenti?
	bool operator!=(Book& book) const; //overload dell'operatore != i due libri sono diversi?


	class BookNotExistException : std::exception {

	public:

		BookNotExistException(std::string t) : text{ t } {};

		std::string printError() {

			return text + "\n";
		}

	private:

		std::string text;
	};

private:

	ISBN isbn;
	std::string title;
	std::string name;
	std::string surname;
	Date copy_date;
	bool disp;


};

std::ostream& operator<<(std::ostream& os, const Book &book); //overload dell'operatore di stampa

#endif