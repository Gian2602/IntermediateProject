#include "Book.h"
#include <iostream>
#include <vector>


int main() {

	std::vector<Book> shelf(10);

	Book my_favourite_book("David", "“Foster Wallace", "Una cosa divertente che non farò mai più", "887-521-837-4");
	
	Book book = Book("Giovannino", "Ciaone", "Vado al mare", "111-333-222-1", "12/2/2000", true);

	std::cout << my_favourite_book;

	std::cout << book;

	try {
		std::cout << shelf[0];
	}
	catch (Book::BookNotExistException e) { std::cout << e.printError(); }

	shelf[0] = Book("1", "2", "3", "111-323-222-1", "12/2/2000", false);

	std::cout << shelf[0];

	std::cout << " testData copiright: " << book.get_Date() << " titolo: " << book.get_title() << " nome e cognome " << book.get_name() << " " <<
		book.get_surname();

	book.get_disponibility() ? std::cout << "funziona" : std::cout << "non è disponibile";

	std::cout << std::endl;

	book.reserve_book() ? std::cout << "funziona" : std::cout << " non e' stato riservato ";

	std::cout << std::endl;

	book.get_disponibility() ? std::cout << " e' disponibile " : std::cout << "funziona";

	std::cout << std::endl;

	book.return_book() ? std::cout << "funziona" : std::cout << " non e' stato restituito ";

	std::cout << std::endl;

	book.get_disponibility() ? std::cout << "funziona" : std::cout << " non e' disponibile ";

	std::cout << std::endl;

	book.return_book() ? std::cout << " e' stato restituito " : std::cout << "funziona";

	std::cout << std::endl;

	shelf[1] = book;

	(shelf[1] == book) ? std::cout << "== funziona correttamente" : std::cout << " == non fuonziona";

	std::cout << std::endl;

	(shelf[0] != book) ? std::cout << "!= funziona correttamente" : std::cout << "!= non fuonziona";

	std::cout << std::endl;

	(shelf[1] != book) ? std::cout << "errore" : std::cout << "!= funziona correttamente";

	std::cout << std::endl;

	(shelf[0] == book) ? std::cout << "errore" : std::cout << "== funziona correttamente";

	std::cout << std::endl;

	//test della classe Date
	try {
		Date prova1 = Date("2 / 26 / 2002");

		std::cout << prova1 << std::endl;

		//Date prova2 = Date("26/2/2002");

		//std::cout << prova2 << std::endl;

		Date prova3 = Date("");

		std::cout << prova3 << std::endl;

		prova3.setMonth(24);

		prova3.getDay();

		Date prova4 = Date("1/1/1900");

		std::cout << prova4 << std::endl;

		Date prova5 = Date("01/01/1900");

		std::cout << prova5 << std::endl;
	}
	catch (Date::InvalidDateException e) { std::cout << e.getMessage(); }
	catch (Date::InvalidFormatException e) { std::cout << e.getMessage(); }

	//prova della classe ISBN
	try{
		ISBN test1 = ISBN("999 - 112 - 321 - e");

		std::cout << test1 << std::endl;

		ISBN test2 = ISBN("999-112-321-e");

		std::cout << test2.getN(4) << std::endl;

		ISBN test3 = ISBN("99-112-321-e");

		std::cout << test3 << std::endl;

		ISBN test4 = ISBN("9a9-444-333-e");
	
		ISBN test5 = ISBN("001-00A-001-0");
		std::cout << test5 << std::endl;

		ISBN test6 = ISBN("000-000-000-1");

		std::cout << test6 << std::endl;

		ISBN test7 = ISBN("000-000-000-!");
	}
	catch (ISBN::InvalidFormatException e) { std::cout << e.getMessage(); }
	catch (ISBN::IndexOutOfBoundsException e) { std::cout << e.getMessage(); }
	
}