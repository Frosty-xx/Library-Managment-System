#include "Date.h"
#include "QString"
using namespace std;
// Simple Date constructor with no range checking
// You need to modify this constructor to add checks
Date::Date(int m, int d, int y)
{
    Set_month(m);
    Set_day(d);
    Set_Year(y);
}
bool Date::Leapyear(int Y)
{
    return ((Y % 400 == 0) or (Y % 4 == 0 and Y % 100 != 0));
};
int Date::monthDays()
{
    int Months[12] = {31, Leapyear(year) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return Months[month - 1];
}
void Date::Set_day(int d)
{
    day = (d >= 0 and d <= monthDays()) ? d : 0;
}
void Date::Set_month(int m)
{
    month = (m > 0 and m <= 12) ? m : 1;
}
void Date::Set_Year(int y)
{
    year = (y > 0) ? y : 1990;
}
void Date::Set_Hour(int h)
{
    hour = (h >= 0) ? h : 0;
}
void Date::Set_Minute(int mi)
{
    minute = (mi >= 0) ? mi : 0;
}
void Date::Set_Date(int m, int d, int y,int h,int mi)
{
    Set_month(m);
    Set_day(d);
    Set_Year(y);
    Set_Hour(h);
    Set_Minute(mi);
}
// Getters
int Date::Get_day()
{
    return day;
}
int Date::Get_month()
{
    return month;
}
int Date::Get_year()
{
    return year;
}

void Date::nextDay()
{
    (day < monthDays()) ? day++ : ((month < 12) ? (day = 1, month++) : (day = 1, month = 1, year++));
}
// to string
QString Date::toString() const
{
    return QString::fromStdString(
        ((day < 10) ? "0" + to_string(day) : to_string(day))
            + ((month < 10) ? "-0" + to_string(month) : "-" + to_string(month))
            + ('-' + to_string(year)) + "  " + (hour < 10 ? "0" + to_string(hour) : to_string(hour))
            + (minute < 10 ? ":0" + to_string(minute) : ":" + to_string(minute)));
}
// current Date
void Date::apply_currentDate()
{
    time_t timestamp = time(NULL);               // The time() function writes a timestamp to the memory location given by the parameter, but it also returns the timestamp's value.
    struct tm datetime = *localtime(&timestamp); // struct containing the data about the date
    Set_Date(int(datetime.tm_mon)+1, int(datetime.tm_mday), int(datetime.tm_year)+1900,int(datetime.tm_hour),int(datetime.tm_min)); // 1900 since tm_year returns (currentyear-1900);
}

int Date::monthDays(bool leap,int month)
{
    int Months[12] = {31, leap ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return Months[month - 1];
}
//return days
int Date::operator-( Date &other)
{
    int days = 0;
    if (this->month == other.month) {
        return this->day - other.day;
    }


    else if (this->year == other.year) {

        if (this->month < other.month) {
            for (int i = this->month; i <= other.month; i++) {
                if (i == this->month) {
                    days -= monthDays(this->Leapyear(this->year), this->month)-this->day;
                } else if (i == other.month) {
                    days -= other.day;
                } else {
                    days -= monthDays(this->Leapyear(this->year), i);
                }
            }
        } else {
            for (int i = this->month; i >= other.month; i--) {
                if (i == this->month) {
                    days += this->day;
                } else if (i == other.month) {
                    days += monthDays(this->Leapyear(this->year), other.month) - other.day;
                } else {
                    days += monthDays(this->Leapyear(this->year), i);
                }
            }
        }
    }



    else {
        if (this->year < other.year) {
            for (int i = other.year; i >= this->year; i--) {
                if (i == other.year) {
                    days -= Leapyear(i) ? 366 : 365 - other.monthAdays_to_days();
                } else if (i == this->year) {
                    days -= this->monthAdays_to_days();
                }
                else
                {
                    days -= Leapyear(i)?366:365;
                }
            }
        }

        else {
            for (int i = this->year; i >= other.year; i--) {
                if (i == other.year) {
                    days += Leapyear(i) ? 366 : 365 - other.monthAdays_to_days() ;
                } else if (i == this->year) {
                    days += this->monthAdays_to_days();
                }
                else
                {
                    days += Leapyear(i)?366:365;
                }
            }
        }
    }

    return days;
}
int Date::monthAdays_to_days()
{
    int days = this->day;
    for (int i = 1; i < this->month; i++) {
        days += monthDays(Leapyear(this->year), i);
    }
    return days;
}
