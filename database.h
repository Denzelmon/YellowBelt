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
private:
    map<Date, vector<string>> records;
};


ostream& operator<<(ostream& os, const pair<Date, string>& entry);