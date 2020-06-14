#include "database.h"
#include <algorithm>
#include <stdexcept>

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

    int removes_count = 0;

    set<Date> date_need_to_delete;

    for (auto& [date, events] : records) {
        auto it = stable_partition(events.begin(), events.end(),
        [&, date = date](auto& event) {
            return !predicate(date, event);
        });
        removes_count += events.end() - it;
        events.erase(it, events.end());

        if (events.empty()) {
            date_need_to_delete.insert(date);
        }
    }

    for (const auto& date : date_need_to_delete) {
        records.erase(date);
    }

    return removes_count;
}

pair<Date, string> Database::Last(const Date &date) {

    auto it = records.lower_bound(date);

    if (it->first == date) {
        return {date, it->second.back()};
    }

    if (it == records.begin()) {
        throw invalid_argument("No entries");
    }

    it = prev(it);
    return {it->first, it->second.back()};
}

ostream& operator<<(ostream& os, const pair<Date, string>& entry) {
    os << entry.first << " " << entry.second;
    return os;
}