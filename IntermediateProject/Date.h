#ifndef Date_h
#define Date_h

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

class Date{

    public:

        class Year{
            private:
                static const int DEFAULT = 1900;                                    //Default value of year (int yy);
                int yy;
            public:
                Year(int yy=DEFAULT) {this->yy=yy;}                                 //Constructor of class Year. Default value (DEFAULT) will be used if the user don't give a year value (int yy).
                int getYearValue() const {return yy;}                               //Getter function for year value.
                void setYearValue(int yy){this->yy=yy;}                             //Setter function for year value.
        };
        class Month{
            private:
                static const int DEFAULT = 1;                                       //Default value of month (int mm).
                int mm;
            public:
                static const int LENGHT = 2;                                        //Max digits number for a month.
                Month(int mm=DEFAULT) {this->mm=mm;}                                //Constructor of class Month. Default value (DEFAULT) will be used if the user don't give a month value (int mm).
                int getMonthValue() const {return mm;}                              //Getter function for month value.
                void setMonthValue(int mm){this->mm=mm;}                            //Setter function for month value.
        };
        class Day{
            private:
                static const int DEFAULT = 1;                                       //Default value of day (int dd).
                int dd;
            public:
                static const int LENGHT = 2;                                        //Max digits number for a day.
                Day(int dd=DEFAULT) {this->dd=dd;}                                  //Constructor of class day. Default value (DEFAULT) will be used if the user don't give a day value (int mm).
                int getDayValue() const {return this->dd;}                          //Getter function for day value.
                void setDayValue(int dd){this->dd=dd;}                              //Setter function for day value.
        };

        //Constructors:
        Date();                                                                     //Default constructor.
        Date(std::string sDate);                                                    //Constructor if the user gives a date in the following format: mm/dd/yy (month = mm, day = dd, year = yy).
        Date(int yy);                                                               //Constructor if the user gives only the year value (year = yy).
        Date(int mm,int dd,int yy);                                                 //Constructor if the user gives all the month, day and year values (month = mm, day = dd, year = yy).

        //Getters:
        Year getYear()const;                                
        Month getMonth()const;
        Day getDay()const;
        bool exists()const;

        //Setters:
        void setYear(int yy);
        void setMonth(int mm);
        void setDay(int dd);
        void changeIsSet();

        std::string toString() const;
        
        //Operators for class Date:
        Date operator+(int daysToAdd);
        Date& operator+=(int daysToAdd);
        Date& operator++(int daysToAdd);
        Date operator-(int daysToSub);
        Date& operator-=(int daysToSub);
        Date& operator--(int daysToSub); 
        //Some operators are not declared because they aren't needed.                    

        int compareTo(const Date& dateToCompare);                                   //Function that compare two dates.
        Date& copyDate(const Date& dateToCopy);                                     //Function that copy dateToCopy values into the current date values.

        bool verifyStringDate(std::string mm,std::string dd,std::string yy);        //Function that will verify if all the strings can be converted as Date values. 

        //Exceptions of class Date:
        class InvalidFormatException : public std::exception{
            private:
                std::string message;
            public:
                InvalidFormatException(std::string message="Date()") : message(message) {}
                std::string getMessage(){return "Invalid format Exception: "+message;}
        };
        class InvalidDateException : public std::exception{
            private:
                std::string message;
            public:
                InvalidDateException(std::string message="Date()") : message(message) {}
                std::string getMessage(){return "Invalid date Exception: "+message;}
        };

    private:

        Year yy;
        Month mm;
        Day dd;
        bool isSet;

};

//Operator << for class Date:
std::ostream& operator<<(std::ostream& os,const Date& d);

//Utilities functions for class Date:
namespace dateUtil{
    bool validDay(int dd, int mm, int yy);
    bool validMonth(int mm);
    bool validYear(int yy);
}

#endif