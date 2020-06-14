#include "database.h"
#include <algorithm>

void Database::Add(const Date &date, const string &event) {
    auto& events_on_date = records[date];
    if (count(events_on_date.begin(), events_on_date.end(), event) == 0) {
        events_on_date.push_back(event);
    }
}

void Database::Print(ostream& os) const {
    for (const auto& [date, events] : records) {
        for (const auto& event : events) {
            os << date << " " << event << endl;
        }
    }
}

vector<pair<Date, string>> Database::FindIf(const function<bool (const Date &, const string &)>& predicate) const {

    vector<pair<Date, string>> entries;

    for (const auto& [date, events] : records) {
        for (const auto& event : events) {
            if (predicate(date, event)) {
                entries.emplace_back(date, event);
            }
        }
    }

    return entries;
}

int Database::RemoveIf(const function<bool (const Date &, const string &)> &predicate) {



}

ostream& operator<<(ostream& os, const pair<Date, string>& entry) {
    os << entry.first << " " << entry.second;
    return os;
}