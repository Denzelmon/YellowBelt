//#include <iostream>
//#include <string>
//#include <iomanip>
//#include <vector>
//#include <map>
//#include <algorithm>
//#include <set>
//
//using namespace std;
//
//bool operator==(const Date& lhs, const Date& rhs) {
//    return lhs.GetYear() == rhs.GetYear() &&
//           lhs.GetMonth() == rhs.GetMonth() &&
//           lhs.GetDay() == rhs.GetDay();
//}
////
//bool operator<(const Date& lhs, const Date& rhs) {
//
//    // проверка года
//    if (lhs.GetYear() < rhs.GetYear()) {
//        return true;
//    } else if (lhs.GetYear() > rhs.GetYear()) {
//        return false;
//    }
//
//    // года совпадают
//    // проверяем месяцы
//    if (lhs.GetMonth() < rhs.GetMonth()) {
//        return true;
//    } else if (lhs.GetMonth() > rhs.GetMonth()) {
//        return false;
//    }
//
//    // месяцы тоже совпадают
//    // проверяем дни
//    return lhs.GetDay() < rhs.GetDay();
//}
//
//class Database {
//public:
//    void AddEvent(const Date& date, const string& event) {
//        events[date].insert(event);
//    }
//    bool DeleteEvent(const Date& date, const string& event) {
//        if (isDateIncluded(date)) {
//            // удаляем событие по дате
//            auto deletedEvents = events[date].erase(event);
//            if (deletedEvents > 0) {
//                cout << "Deleted successfully" << endl;
//                return true;
//            }
//        }
//        cout << "Event not found" << endl;
//        return false;
//    }
//
//    int DeleteDate(const Date& date) {
//        int deletedEvents = 0;
//
//        if (isDateIncluded(date)) {
//            deletedEvents = events[date].size();
//            events.erase(date);
//        }
//
//        cout << "Deleted " + to_string(deletedEvents) + " events" << endl;
//        return deletedEvents;
//    }
//
//    void Find(const Date& date) const {
//        if (isDateIncluded(date)) {
//            for (const auto& str : events.at(date)) {
//                cout << str << endl;
//            }
//        }
//
//    }
//
//    void Print() const {
//        for (const auto& [date, str_events] : events) {
//            for (const auto& str_event : str_events) {
//                cout << date << " " << str_event << endl;
//            }
//        }
//    }
//
//private:
//    bool isDateIncluded(const Date& date) const {
//        return events.count(date);
//    }
//
//    map<Date, set<string>> events;
//};
//
//int main() {
//
//    Database db;
//    string line;
//    string cmd;
//    try {
//        while (getline(cin, line)) {
//            if (!line.empty()) {
//                stringstream stream(line);
//                stream >> cmd;
//                if (cmd == "Add") {
//                    Date date;
//                    string event;
//                    stream >> date >> event;
//                    db.AddEvent(date, event);
//                } else if (cmd == "Del") {
//                    Date date;
//                    string event;
//                    stream >> date;
//                    if (stream >> event) {
//                        db.DeleteEvent(date, event);
//                    } else {
//                        db.DeleteDate(date);
//                    }
//                } else if (cmd == "Find") {
//                    Date date;
//                    stream >> date;
//                    db.Find(date);
//                } else if (cmd == "Print") {
//                    db.Print();
//                } else {
//                    cout << "Unknown command: " << cmd << endl;
//                    return -1;
//                }
//            }
//        }
//    }
//    catch (runtime_error &err) {
//        cout << err.what() << endl;
//        return -2;
//    }
//    catch (...) {
//        return -3;
//    }
//
//    return 0;
//}
//


//#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

#include <iostream>
#include <stdexcept>
#include <sstream>

using namespace std;

string ParseEvent(istream& is) {
    string event;
    is >> ws;
    getline(is, event);
    return event;
}

void TestAll();

int main() {

    TestAll();
//
//    Database db;
//
//    for (string line; getline(cin, line); ) {
//        istringstream is(line);
//
//        string command;
//        is >> command;
//        if (command == "Add") {
//            const auto date = ParseDate(is);
//            const auto event = ParseEvent(is);
//            db.Add(date, event);
//        } else if (command == "Print") {
//            db.Print(cout);
//        } else if (command == "Del") {
//            auto condition = ParseCondition(is);
//            auto predicate = [condition](const Date& date, const string& event) {
//                return condition->Evaluate(date, event);
//            };
//            int count = db.RemoveIf(predicate);
//            cout << "Removed " << count << " entries" << endl;
//        } else if (command == "Find") {
//            auto condition = ParseCondition(is);
//            auto predicate = [condition](const Date& date, const string& event) {
//                return condition->Evaluate(date, event);
//            };
//
//            const auto entries = db.FindIf(predicate);
//            for (const auto& entry : entries) {
//                cout << entry << endl;
//            }
//            cout << "Found " << entries.size() << " entries" << endl;
//        } else if (command == "Last") {
//            try {
//                cout << db.Last(ParseDate(is)) << endl;
//            } catch (invalid_argument&) {
//                cout << "No entries" << endl;
//            }
//        } else if (command.empty()) {
//            continue;
//        } else {
//            throw logic_error("Unknown command: " + command);
//        }
//    }

    return 0;
}

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}


void TestDate() {
    istringstream is("2019-02-13");
    auto date = ParseDate(is);
    ostringstream os;
    os << date;
    AssertEqual(os.str(), "2019-02-13", "Parse and print date to stream");
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestDate, "TestDate");
}
