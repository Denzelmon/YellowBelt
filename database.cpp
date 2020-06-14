#include "database.h"
#include <algorithm>
#include <stdexcept>

void Database::Add(const Date &date, const string &event) {
    auto& events_on_date_vec = records_vec[date];
    auto& events_on_date_set = records_set[date];

    if (events_on_date_set.count(event) == 0) {
        events_on_date_set.insert(event);
        events_on_date_vec.push_back(event);
    }
}

void Database::Print(ostream& os) const {
    for (const auto& [date, events] : records_vec) {
        for (const auto& event : events) {
            os << date << " " << event << endl;
        }
    }
}

vector<pair<Date, string>> Database::FindIf(const function<bool (const Date &, const string &)>& predicate) const {

    vector<pair<Date, string>> entries;

    for (const auto& [date, events] : records_vec) {
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

    for (auto& [date, events] : records_vec) {
        auto it = stable_partition(events.begin(), events.end(),
        [&, date = date](auto& event) {
            return !predicate(date, event);
        });

        for (auto it_set = it; it_set != events.end(); it_set++) {
            records_set[date].erase(*it_set);
        }

        removes_count += events.end() - it;
        events.erase(it, events.end());

        if (events.empty()) {
            date_need_to_delete.insert(date);
        }
    }

    for (const auto& date : date_need_to_delete) {
        records_vec.erase(date);
        records_set.erase(date);
    }

    return removes_count;
}

pair<Date, string> Database::Last(const Date &date) const{

    auto it = records_vec.upper_bound(date);

    if (it == records_vec.begin()) {
        throw invalid_argument("No entries");
    }

    it = prev(it);

    return {it->first, it->second.back()};
}

ostream& operator<<(ostream& os, const pair<Date, string>& entry) {
    os << entry.first << " " << entry.second;
    return os;
}