#include "Date.h"

Date::Date(){
    this->dd=Day();
    this->mm=Month();
    this->yy=Year();
    this->isSet=false;
}

Date::Date(std::string sDate){
    sDate.erase(std::remove(sDate.begin(), sDate.end(), ' '), sDate.end());     //Removes all the spaces from the string sDate
    if(sDate.compare("")!=0){
        std::stringstream ss;
        ss<<sDate;
        std::string dd, mm, yy;
        std::getline(ss,mm,'/');
        std::getline(ss,dd,'/');
        std::getline(ss,yy);
        if(verifyStringDate(mm,dd,yy)){
            this->dd=Day(std::stoi(dd));
            this->mm=Month(std::stoi(mm));
            this->yy=Year(std::stoi(yy));
            this->isSet=true;
        }
        else throw InvalidFormatException(sDate);                               //sDate is in a wrong format or is incorrect.
    }
    else *this = Date();                                                        //if sDate is empty, then use the default constructor.
}

bool Date::verifyStringDate(std::string mm,std::string dd,std::string yy){
    if(mm.size()>0 && mm.size()<=Date::Month::LENGHT && dd.size()>0 && dd.size()<=Date::Day::LENGHT && yy.size()>0){
        //Verify that the day value is a number:
        int i=0;
        while(i<dd.size()){
            if(dd[i]<'0' || dd[i]>'9')
                return false;
            i++;
        }
        //Verify that the month value is a number:
        i=0;
        while(i<mm.size()){
            if(mm[i]<'0' || mm[i]>'9')
                return false;
            i++;
        }
        //Verify that the year value is a number:
        i=0;
        while(i<yy.size()){
            if(yy[i]<'0' || yy[i]>'9')
                return false;
            i++;
        }
        //Verify that day and month values are valid numbers:
        if(!dateUtil::validMonth(std::stoi(mm)) || !dateUtil::validDay(std::stoi(dd),std::stoi(mm),std::stoi(yy)))
            return false;
        return true;
    }
    return false;
}

Date::Date(int yy){ 
    this->dd=Day();
    this->mm=Month();
    if(!dateUtil::validYear(yy)) throw InvalidDateException("invalid year.");
    this->yy=Year(yy);
    this->isSet=true;
}

Date::Date(int mm,int dd,int yy){
    if(!dateUtil::validMonth(mm)) throw InvalidDateException("invalid month.");
    this->mm=Month(mm);
    if(!dateUtil::validDay(dd,mm,yy)) throw InvalidDateException("invalid day.");
    this->dd=Day(dd);
    if(!dateUtil::validYear(yy)) throw InvalidDateException("invalid year.");
    this->yy=Year(yy);
    this->isSet=true;
}

std::string Date::toString()const{
    std::stringstream s;
    if(this->isSet)
        //Creating the Date string in the following format: mm/dd/yy (month = mm, day = dd, year = yy).
        s<<this->mm.getMonthValue() << "/"<<this->dd.getDayValue() << "/"<<this->yy.getYearValue();
    return s.str();
}

Date Date::operator+(int daysToAdd){
    if(!this->isSet) throw InvalidDateException("invalid date for operator+.");
    bool completeOp=false;
    int mmToCompare=this->mm.getMonthValue();
    int yyToCompare=this->yy.getYearValue();
    int ddToCompare=this->dd.getDayValue()+daysToAdd;
    do{
        completeOp=true;
        if(mmToCompare==2 && completeOp){
            //if leap year:
            if(yyToCompare%4==0 || yyToCompare%400==0){
                if(ddToCompare>29){
                    //max days of current month:
                    ddToCompare-=29;
                    mmToCompare++;
                    completeOp=false;
                }
            }
            else{
                //if no-leap year:
                if(ddToCompare>28){
                    //max days of current month:
                    ddToCompare-=28;
                    mmToCompare++;
                    completeOp=false;
                }
            }
        }
        if((mmToCompare==1 || mmToCompare==3 || mmToCompare==5 || mmToCompare==7 || mmToCompare==8 || mmToCompare==10 || mmToCompare==12) && completeOp)
            if(ddToCompare>31){
                //max days of current month:
                ddToCompare-=31;
                mmToCompare++;
                completeOp=false;
            }
        if((mmToCompare==4 || mmToCompare==6 || mmToCompare==9 || mmToCompare==11) && completeOp)
            if(ddToCompare>30){
                //max days of current month:
                ddToCompare-=30;
                mmToCompare++;
                completeOp=false;
            }
        if(mmToCompare>12){
            mmToCompare=1;
            yyToCompare+=1;
            completeOp=false;
        }
    }
    while(!completeOp);
    //Date newDate = Date(mmToCompare,ddToCompare,yyToCompare);
    return Date(mmToCompare,ddToCompare,yyToCompare);
}

Date& Date::operator+=(int daysToAdd){
    return *this=operator+(daysToAdd);
}

Date Date::operator-(int daysToSub){
    if(!this->isSet) throw InvalidDateException("invalid date for operator-.");
    bool completeOp=false;
    int mmToCompare=this->mm.getMonthValue();
    int yyToCompare=this->yy.getYearValue();
    int ddToCompare=this->dd.getDayValue()-daysToSub;
    do{
        completeOp=true;
        //if days are still negative:
        if(ddToCompare<1){
            if(mmToCompare==3 && completeOp){
                if(yyToCompare%4==0 || yyToCompare%400==0){
                        //leap year max days:
                        ddToCompare+=29;
                        mmToCompare--;
                }
                else{
                        //no-leap year max days:
                        ddToCompare+=28;
                        mmToCompare--;
                }
                completeOp=false;
            }
            if((mmToCompare==1 || mmToCompare==2 || mmToCompare==4 || mmToCompare==6 || mmToCompare==8 || mmToCompare==9 || mmToCompare==11) && completeOp){
                //max days of previous month:
                ddToCompare+=31;
                mmToCompare--;
                completeOp=false;
            }
            if((mmToCompare==5 || mmToCompare==7 || mmToCompare==10 || mmToCompare==12) && completeOp){
                //max days of previous month:
                ddToCompare+=30;
                mmToCompare--;
                completeOp=false;
            }
            if(mmToCompare<1){
                //need to subtract a year:
                mmToCompare=12;
                yyToCompare-=1;
                completeOp=false;
            }
        }
    }
    while(!completeOp);
    //Date newDate = Date(mmToCompare,ddToCompare,yyToCompare);
    return Date(mmToCompare,ddToCompare,yyToCompare);
}

Date& Date::operator-=(int daysToSub){
    return *this=operator-(daysToSub);
}

Date& Date::operator++(int daysToAdd){
    return *this=operator+(1);
}

Date& Date::operator--(int daysToSub){
    return *this=operator-(1);
}

int Date::compareTo(const Date& dateToCompare){
    if(this->yy.getYearValue()>dateToCompare.getYear().getYearValue())
        return 1;
    if(this->yy.getYearValue()<dateToCompare.getYear().getYearValue())
        return -1;
    if(this->mm.getMonthValue()>dateToCompare.getMonth().getMonthValue())
        return 1;
    if(this->mm.getMonthValue()<dateToCompare.getMonth().getMonthValue())
        return -1;
    if(this->dd.getDayValue()>dateToCompare.getDay().getDayValue())
        return 1;
    if(this->dd.getDayValue()<dateToCompare.getDay().getDayValue())
        return -1;
    return 0;
}

std::ostream& operator<<(std::ostream& os,const Date& d){
    return os << d.toString();
}

Date& Date::copyDate(const Date& dateToCopy){
    if(!this->isSet) throw InvalidDateException("this date is not valid.");
    if(!dateToCopy.exists()) throw InvalidDateException("invalid date to copy.");
    this->dd.setDayValue(dateToCopy.getDay().getDayValue());
    this->mm.setMonthValue(dateToCopy.getMonth().getMonthValue());
    this->yy.setYearValue(dateToCopy.getYear().getYearValue());
    return *this;
}

Date::Day Date::getDay()const{return dd;}
Date::Month Date::getMonth()const{return mm;}
Date::Year Date::getYear()const{return yy;}
bool Date::exists()const{return isSet;}

void Date::setYear(int yy){
    if(!dateUtil::validYear(yy)) throw InvalidDateException("invalid year.");
    this->yy.setYearValue(yy);
}
void Date::setMonth(int mm){
    if(!dateUtil::validMonth(mm)) throw InvalidDateException("invalid month.");
    this->mm.setMonthValue(mm);
}
void Date::setDay(int dd){
    if(!dateUtil::validDay(dd,this->mm.getMonthValue(),this->yy.getYearValue())) throw InvalidDateException("invalid day.");
    this->dd.setDayValue(dd);
}

//Change the value from true to false or from false to true depending on the isSet value:
void Date::changeIsSet(){this->isSet = (this->isSet==true) ? false : true;}

bool dateUtil::validDay(int dd, int mm, int yy){
    if(dd<1)
        return false;
    if(mm==2)
        if(yy%4==0 || yy%400==0){
            if(dd>29)
                return false;
        }
        else
            if(dd>28)
                return false;
    if(mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12)
        if(dd>31)
            return false;
    if( mm==4 || mm==6 || mm==9 || mm==11)
        if(dd>30)
            return false;
    return true;
}

bool dateUtil::validMonth(int mm){
    if(mm<1 || mm>12)
        return false;
    return true;
}

bool dateUtil::validYear(int yy){
    if(yy>0)
        return true;
    return false;
}