#pragma once
#include "date.h"
#include "node.h"
#include <map>
#include <vector>
#include <set>
#include <functional>

using namespace std;

class Database {
public:
    void Add(const Date& date, const string& event);
    void Print(ostream& os) const;
    vector<pair<Date, string>> FindIf(const function<bool(const Date&, const string&)>& predicate) const;
    int RemoveIf(const function<bool(const Date&, const string&)>& predicate);
    pair<Date, string> Last(const Date& date) const;
private:
    map<Date, vector<string>> records_vec;
    map<Date, set<string>> records_set;
};


ostream& operator<<(ostream& os, const pair<Date, string>& entry);