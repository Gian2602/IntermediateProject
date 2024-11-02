#include "Book.h"


Book::Book(std::string name, std::string surname, std::string title, std::string isbn, std::string copy_date, bool disp)
	:isbn{ ISBN(isbn) }, title{ title }, name{ name }, surname{ surname }, copy_date{ Date(copy_date) }, disp{ disp } {}

Book::Book()
	:isbn{ ISBN("") }, title{ "" }, name{ "" }, surname{ "" }, copy_date{ Date("") }, disp{ false } {}

ISBN Book::get_isbn() const { 

	if (isbn.exists())
		return isbn;
	else
		throw BookNotExistException("The book doesn't exist"); 
}

std::string Book::get_title() const {

	if (isbn.exists())
		return title;
	else
		throw BookNotExistException("The book does'n exist");
}

std::string Book::get_name() const {

	if (isbn.exists())
		return name;
	else
		throw BookNotExistException("The book does'n exist");
}

std::string Book::get_surname() const {

	if (isbn.exists())
		return surname;
	else
		throw BookNotExistException("The book does'n exist");
}

Date Book::get_Date() const {

	if(!isbn.exists())
		throw BookNotExistException("The book does'n exist");


	return copy_date;
}


bool Book::get_disponibility() const {

	if (isbn.exists())
		return disp;
	else
		throw BookNotExistException("The book does'n exist");
	
}

bool Book::reserve_book() {

	if (!isbn.exists())
		throw BookNotExistException("The book does'n exist");

	if (!disp) //se il libro è già prenotato non può essere prenotato
		return false; //quando l'operazione Book ritorna false vuol dire che non è andata a buon termine

	disp = false; //se il libro era disponibile salvo che è stato prenotato e vado a ritornare che l'operazione è andata a buon fine

	return true;
}

bool Book::return_book() {

	if (!isbn.exists())
		throw BookNotExistException("The book does'n exist");

	if (disp) //controllo che il libro non sia già disponibile nel caso vado a dire che l'operazione non è andata a buon fine
		return false; 

	disp = true; //vado a salvare che il lirbo ora è disponibile e ritorno che l'operazione è andata a buon fine

	return true;
}

bool Book::operator==(Book& book) const {

	if (isbn.exists() && book.get_isbn().exists()) {
		if (this->isbn == book.isbn) //utilizzo l'operatore == della classe ISBN per verificare se i due libri sono uguali
			return true; //se sono uguali ritorno true

		return false; //se sono diversi ritornano false
	}
	else
		throw BookNotExistException("The book does'n exist");
	
}

bool Book::operator!=(Book& book) const {

	if (isbn.exists() && book.get_isbn().exists()) {
		if (this->isbn != book.isbn) //utilizzo l'operatore != della classe ISBN per verificare se i due libri sono uguali
			return true; //se sono diversi ritorno true

		return false; //se sono uguali ritorno false
	}
	else
		throw BookNotExistException("The book does'n exist");
	
}

std::ostream& operator<<(std::ostream& os, const Book& book) {
	
	//vado a stampare isbn , titolo , nome e cognome

	os << " ISBN: " << book.get_isbn() << "\n" << " title: " << book.get_title() << "\n" << " Name and surname: " << book.get_name()
		<< " " << book.get_surname() << "\n";

	//nel caso sia stata specificata la data di copyright la vado a stampare
	if (book.get_Date().exists())
		os << " Data copyright: " << book.get_Date() << "\n";
	if (book.get_disponibility()) //stampo se è disponibile oppure è già in prestito
		os << " The book is available" << std::endl;
	else
		os << " The book is on loan" << std::endl;

	return os;
}



