#include "ISBN.h"

const std::array<int, ISBN::n_DIM> ISBN::n_DEFAULT = { 0,0,0 };

ISBN::ISBN(const std::string isbn)
{
	set(isbn);
}

ISBN::ISBN(const ISBN& isbn)
	: isSet{isbn.isSet}, n{isbn.n}, x{isbn.x}
{
}

bool ISBN::operator==(ISBN& isbn) const
{
	//if one of the operands is uninitialized there is no mean comparing them
	if (!this->exists()) throw ISBN::UninitializedException(this->toString());
	if (!isbn.exists()) throw ISBN::UninitializedException(isbn.toString());

	for (int i = 0; i < n_DIM; i++) {
		if (this->n[i] != isbn.n[i]) return false;
	}

	if (this->x != isbn.x) return false;
	
	return true;
}

bool ISBN::operator!=(ISBN& isbn) const
{
	return *this == isbn ? false : true; //no repetitive code :)
}

std::ostream& operator<<(std::ostream& os, const ISBN& isbn)
{
	//same as above: if not initialized, the default value would be printed, but it has no meaning
	if (!isbn.exists()) throw ISBN::UninitializedException(isbn.toString());
	os << isbn.toString();
	return os;
}

int ISBN::getN(int id) const
{
	//it doesn't matter if the ISBN is initialized or not; when calling this function the "user" wants to get a n value ignoring the state
	if (id < 0 || id >= n_DIM) //check if the position really exists
		throw IndexOutOfBoundsException(id); //if not, throws this exception
	return n[id];
}

std::array<int, ISBN::n_DIM> ISBN::getN() const
{
	//it doesn't matter if the ISBN is initialized or not; when calling this function the "user" wants to get n array ignoring the state

	return n;
}

std::string ISBN::toString() const
{
	std::string code = ""; //output code
	if (exists()) {
		std::stringstream ss; //output stringstream
		for(int i = 0; i < n_DIM; i++){
			std::stringstream nss; //number stringstream
			std::string ns; //number string
			nss << n[i]; //loads the number into the stream
			nss >> ns; //loads the number into the string

			for (int j = 0; j < n_DIGITS - ns.size(); j++) ss << "0"; //adds a "0" for every missing digit eg. "10-1-0-A"
		
			ss << n[i] << "-"; //appends the numbers to the stream, followed by '-'
		}

		ss << x; //appends last "digit"

		ss >> code; //writes all into the string
	}
	else code += "no such ISBN";

	return code;
}

bool ISBN::set(std::string isbn){
	isbn.erase(std::remove(isbn.begin(), isbn.end(), ' '), isbn.end()); //deletes all the spaces

	if (isbn == "") erase();
	else if (ISBN_UTILS::validateISBN(isbn)) { //check if the string has the right format

		std::vector<std::string> code_substrs = ISBN_UTILS::divideISBN(isbn); //divides the string into the 4 elements of a ISBN

		for (int i = 0; i < ISBN::n_DIM; i++) this->n[i] = std::stoi(code_substrs[i]); //copies the 3 numbers into the array
		
		
		this->x = std::toupper(code_substrs[ISBN::s_DIM - 1][0]); //copies the last "digit" into the x (puts it to uppercase)

		isSet = true; //now the ISBN is valid
	}
	else {
		erase(); //invalid string: ISBN is invalid
		throw InvalidFormatException(isbn); //if the string hasn't the right format, throws this exception
	}
	return isSet;
}

void ISBN::erase() { //"clears" ISBN values: sets it to logically "uninitialized"
	this->isSet = false;
	this->n = ISBN::n_DEFAULT;
	this->x = ISBN::x_DEFAULT;
}

std::vector<std::string> ISBN_UTILS::divideISBN(std::string isbn) { //divides ISBN string into its elements
	std::stringstream ss;
	ss << isbn;
	std::string temp;
	std::vector<std::string> code_substrs; //contains every substring of the initial code

	while (std::getline(ss, temp, '-')) {
		code_substrs.push_back(temp); //reads till '-' till there's something to read
	}
	return code_substrs;
}

bool ISBN_UTILS::validateInt(std::string code) { //the "code" string here represents one number of the ISBN, eg. 123
	if (code.size() != ISBN::n_DIGITS) return false;

	for (int i = 0; i < ISBN::n_DIGITS; i++)
		if (code[i] < '0' || code[i] > '9') return false; //checks if every char is actually a number

	return true;
}

bool ISBN_UTILS::validateChar(std::string code) { //the "code" here represents last "digit" substring
	if (code.size() != ISBN::x_DIGITS) return false; //it has to be a single char
	if((code[0]<'A' || code[0]>'Z') && (code[0]<'a' || code[0]>'z') && (code[0]<'0' || code[0] > '9'))
		return false; //and to be a letter
	return true;
}

bool ISBN_UTILS::validateISBN(std::string isbn)
{
	if (isbn.size() != ISBN::isbn_DIM) return false;

	std::vector<std::string> code_substrs = divideISBN(isbn); //divides the ISBN string by '-'

	for (int i = 0; i < ISBN::n_DIM; i++)
		if (!validateInt(code_substrs[i])) return false; //validates every number
	if (!validateChar(code_substrs[ISBN::s_DIM - 1])) return false; //validates last "digit"

	return true;
}