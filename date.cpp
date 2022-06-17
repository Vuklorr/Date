#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

class Date {
public:
    Date() :
    day(1),month(1),year(1) {}

    Date(const std::string& str);

    bool isCorrect() const;
    bool operator >(const Date& date) const;

    friend std::ostream& operator<<(std::ostream& stream, const Date& date);

private:
    int day;
    int month;
    int year;

    const static inline std::array<uint, 12> daysInMonth = {31,28,31,30,31,30,31,31,30,31,30,31};

    static bool isLeapYear(int year) {
        return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    }

    static int getMaxMonthDays(int year, int month) {
        if(month == 2 && isLeapYear(year)) {
            return 29;
        }
        return daysInMonth[month - 1];
    }
};

Date::Date(const std::string &str) {
    std::istringstream iss(str);

    if(str.find('/') != std::string::npos) {
        (iss >> month).get();
        (iss >> day).get();
        iss >> year;
    } else {
        (iss >> day).get();
        (iss >> month).get();
        iss >> year;
    }
}

bool Date::isCorrect() const {
    if (year < 0
        || month < 1 || month > 12
        || day < 1 || day > getMaxMonthDays(year, month)) {
        return false;
    }

    return true;
}

bool Date::operator>(const Date &date) const {
    return std::tie(year, month, day) > std::tie(date.year, date.month, date.day);
}

std::ostream &operator<<(std::ostream &stream, const Date &date) {
    stream << std::setfill('0') << std::setw(4) << date.year << '-'
           << std::setfill('0') << std::setw(2) << date.month << '-'
           << std::setfill('0') << std::setw(2) << date.day << '\n';

    return stream;
}

int main(int argc, char *argv[]) {
    std::vector<Date> dates;

    for(int i = 1; i < argc; i++) {
        Date date(argv[i]);
        if(date.isCorrect()) {
            dates.emplace_back(date);
        }
    }

    std::sort(dates.begin(), dates.end(),[](Date first, Date second) {
        return first > second;
    });

    for(const auto& it : dates) {
        std::cout << it << '\n';
    }
}

