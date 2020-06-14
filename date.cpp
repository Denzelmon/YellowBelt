#include "date.h"
#include <iomanip>

Date::Date(uint16_t year, uint16_t month, uint16_t day) : year_(year), month_(month), day_(day) {}

uint16_t Date::GetYear() const {
    return year_;
}

uint16_t Date::GetMonth() const {
    return month_;
}

uint16_t Date::GetDay() const {
    return day_;
}

Date ParseDate(istream& is) {

    uint16_t year, month, day;
    is >> year;
    is.ignore();
    is >> month;
    is.ignore();
    is >> day;

    return {year, month, day};
}

ostream& operator<<(ostream& stream, const Date& date) {
    stream << setw(4) << setfill('0') << date.GetYear() << "-" <<
           setw(2) << setfill('0') << date.GetMonth() << "-" <<
           setw(2) << setfill('0') << date.GetDay();
    return stream;
}

bool operator<(const Date& ldate, const Date& rdate) {
    return make_tuple(ldate.GetYear(), ldate.GetMonth(), ldate.GetDay()) <
           make_tuple(rdate.GetYear(), rdate.GetMonth(), rdate.GetDay());
}

bool operator==(const Date& ldate, const Date& rdate) {
    return make_tuple(ldate.GetYear(), ldate.GetMonth(), ldate.GetDay()) ==
           make_tuple(rdate.GetYear(), rdate.GetMonth(), rdate.GetDay());
}

bool operator!=(const Date& ldate, const Date& rdate) {
    return !(ldate == rdate);
}

bool operator<=(const Date& ldate, const Date& rdate) {
    return (ldate == rdate) || (ldate < rdate);
}

bool operator>(const Date& ldate, const Date& rdate) {
    return make_tuple(ldate.GetYear(), ldate.GetMonth(), ldate.GetDay()) >
           make_tuple(rdate.GetYear(), rdate.GetMonth(), rdate.GetDay());
}

bool operator>=(const Date& ldate, const Date& rdate) {
    return (ldate == rdate) || (ldate > rdate);
}
