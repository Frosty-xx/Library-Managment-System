#ifndef LAB2_DATE_H
#define LAB2_DATE_H
#include <ctime>
#include <QString>

// Simple Date class
class Date
{
public:
    // Complete the default constructor prototype to initialize
    // the default date to 1/1/1990
    Date(int day = 1, int month = 1, int year = 1990);
    // Setters
    void Set_day(int day);
    void Set_month(int month);
    void Set_Year(int year);
    void Set_Hour(int hour);
    void Set_Minute(int Minute);
    void Set_Date(int month, int day, int year,int hour,int min);
    // Getters
    int Get_day();
    int Get_month();
    int Get_year();
    // Leap year();
    bool Leapyear(int Y);
    // monthDays:
    int monthDays();
    static int monthDays(bool leap, int month);
    //To string:
    QString toString() const;
    // NextDay:
    void nextDay();
    //get day
    void apply_currentDate();

    int operator-( Date &other);
    int monthdays();
    int monthAdays_to_days();


private:
    int month;
    int day;
    int year;
    int hour;
    int minute;
};

#endif // LAB2_DATE_H
