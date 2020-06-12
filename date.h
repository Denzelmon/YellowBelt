#pragma once

#include <cstdint>
#include <iostream>

using namespace std;

class Date {
public:

    Date(uint16_t year, uint16_t month, uint16_t day);

    uint16_t GetYear() const;
    uint16_t GetMonth() const;
    uint16_t GetDay() const;

private:
    const uint16_t year_;
    const uint16_t month_;
    const uint16_t day_;
};

Date ParseDate(istream& is);

ostream& operator<<(ostream& stream, const Date& date);

bool operator<(const Date& ldate, const Date& rdate);
bool operator==(const Date& ldate, const Date& rdate);
bool operator!=(const Date& ldate, const Date& rdate);
bool operator<=(const Date& ldate, const Date& rdate);
bool operator>(const Date& ldate, const Date& rdate);
bool operator>=(const Date& ldate, const Date& rdate);
