#ifndef ISBN_H
#define ISBN_H

#include <algorithm>
#include <string>
#include <sstream>
#include <array>
#include <vector>

class ISBN
{
public:
	//consts
	static const int isbn_DIM = 13; //size of a isbn (000-000-000-A)
	static const int n_DIM = 3;	//size of the 3-number's array
	static const int s_DIM = 4; //virtual size of the ISBN: it is divided into 4 parts
	static const int n_DIGITS = 3; //digits of each number
	static const int x_DIGITS = 1; //last char's digits
	static const std::array<int, 3> n_DEFAULT; //default numbers
	static const char x_DEFAULT = '0'; //default char

	ISBN(const std::string isbn = "");
	ISBN(const ISBN& isbn);

	bool operator==(ISBN& isbn) const;
	bool operator!=(ISBN& isbn) const;

	std::string toString() const;

	bool set(std::string isbn); //sets all the elements of a ISBN, can't be set partially
	void erase(); //change ISBN state to uninitialized and sets n and x to their default values

	bool exists() const { return this->isSet; } //tells if the ISBN is initialized
	std::array<int, n_DIM> getN() const; //gets the array
	int getN(int id) const;	//gets one of the 3 numbers
	char getX() const { return this->x; } //gets the last "digit"

	//exceptions
	class IndexOutOfBoundsException : std::exception
	{	//called when trying to access out of the bounds of an array
	private:
		std::string message;
	public:
		IndexOutOfBoundsException(int id) {
			std::stringstream ss;
			ss << "INDEX OUT OF BOUNDS: id: " << id << std::endl;
			this->message = ss.str();
		}

		std::string getMessage() const { return this->message; }
	};

	class InvalidFormatException : std::exception
	{	//called when the ISBN string has a wrong format
	private:
		std::string message;
	public:
		InvalidFormatException(std::string isbn) {
			this->message = "INVALID FORMAT: " + isbn + "\n";
		}

		std::string getMessage() const { return this->message; }
	};

	class UninitializedException : std::exception
	{	//called when trying to get an uninitialized ISBN (getting its elements, like n or x) won't call this exception
	private:
		std::string message;
	public:
		UninitializedException(std::string isbn) {
			this->message = "UNINITIALIZED ISBN: " + isbn + "\n";
		}

		std::string getMessage() const { return this->message; }
	};

private:
	bool isSet; //tells if the ISBN has been initialized

	std::array<int, n_DIM> n; //contains the 3 numbers
	char x; //contains the last "digit"

};

//helper functions
std::ostream& operator<<(std::ostream& os, const ISBN& isbn);

namespace ISBN_UTILS {
	std::vector<std::string> divideISBN(std::string isbn); //divides the ISBN string into 4 strings of each element
	bool validateChar(std::string code); //validates x syntax
	bool validateInt(std::string code); //validates a n-element syntax
	bool validateISBN(std::string isbn); //validates ISBN syntax
}
#endif