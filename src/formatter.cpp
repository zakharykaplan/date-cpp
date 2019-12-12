//
//  formatter.cpp
//  Date to string formatter.
//
//  Created by Zakhary Kaplan on 2019-12-03.
//  Copyright © 2019 Zakhary Kaplan. All rights reserved.
//

#include <cstdio>
#include <regex>
#include <string>

#include "date.h"
#include "formatter.h"


// -- Constants --
const std::string Formatter::WEEKDAYS[] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};
const std::string Formatter::MONTHS[] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};
const std::string Formatter::SPECIFIERS[] = {
    "dd", "d", "MMMM", "MMM", "MM", "M", "yyyy", "yyy", "yy", "y", "cc", "c",
    "hh", "h", "HH", "H", "mm", "m", "ss", "s", "tt", "t", "TT", "T", "zz", "z"
};



// -- Public Methods --
// Format a Date object by the default string specifier
std::string Formatter::format(const Date &date) {
    // Use default format string specifier
    const std::string formatStr = "H:mm:ss dd/MM/yyyy";

    // Format on default string specifier
    return Formatter::format(date, formatStr);
}



// Format a Date object by a string specifier
std::string Formatter::format(const Date &date, const std::string formatStr) {
    std::string formatOut = formatStr;

    for (auto &s: Formatter::SPECIFIERS) {
        formatOut = std::regex_replace(
                formatOut,
                std::regex(s),
                Formatter::substitute(date, s)
        );
    }

    return formatOut;
}


// -- Private Methods --

// Perform appropriate format substitution
std::string Formatter::substitute(const Date &date, std::string format) {
    switch (format[0]) {
        case 'd':
            return Formatter::day(date, format);

        case 'M':
            return Formatter::month(date, format);

        case 'y':
            return Formatter::year(date, format);

        case 'c':
            return Formatter::century(date, format);

        case 'h':
        case 'H':
            return Formatter::hour(date, format);

        case 'm':
            return Formatter::minute(date, format);

        case 's':
            return Formatter::second(date, format);

        case 't':
        case 'T':
            return Formatter::period(date, format);

        case 'z':
            return Formatter::timezone(date, format);

        default:
            return format;
    }
}


// Formatting
std::string Formatter::day(const Date &date, std::string format) {
    int day = date.day();

    // Return formatted day string
    if (format == "d") {
        return std::to_string(day);
    } else if (format == "dd") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", day);
        return std::string(buffer);
    } else if (format == "ddd") {
        return std::string(Formatter::WEEKDAYS[day-1], 0, 3);
    } else if (format == "dddd") {
        return std::string(Formatter::WEEKDAYS[day-1]);
    }

    // Return empty string for invalid format
    return format;
}


std::string Formatter::month(const Date &date, std::string format) {
    int month = date.month();

    // Return formatted month string
    if (format == "M") {
        return std::to_string(month);
    } else if (format == "MM") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", month);
        return std::string(buffer);
    } else if (format == "MMM") {
        return std::string(Formatter::MONTHS[month-1], 0, 3);
    } else if (format == "MMMM") {
        return std::string(Formatter::MONTHS[month-1]);
    }

    // Return empty string for invalid format
    return format;
}


std::string Formatter::year(const Date &date, std::string format) {
    int year = date.year();

    // Return formatted year string
    if (format == "y") {
        return std::to_string(year);
    } else if (format == "yy") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", year % 100);
        return std::string(buffer);
    } else if (format == "yyy") {
        char buffer[5];
        snprintf(buffer, 5, "%03d", year);
        return std::string(buffer);
    } else if (format == "yyyy") {
        char buffer[5];
        snprintf(buffer, 5, "%04d", year);
        return std::string(buffer);
    }

    // Return empty string for invalid format
    return format;
}


std::string Formatter::century(const Date &date, std::string format) {
    int century = date.year() / 100;

    // Return formatted century string
    if (format == "c") {
        return std::to_string(century);
    } else if (format == "cc") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", century % 100);
        return std::string(buffer);
    }

    // Return empty string for invalid format
    return format;
}


std::string Formatter::hour(const Date &date, std::string format) {
    int hour24 = date.hour();
    int hour12 = (hour24) ? hour24 % 12 : 12;

    // Return formatted hour string
    if (format == "h") {
        return std::to_string(hour12);
    } else if (format == "hh") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", hour12);
        return std::string(buffer);
    } else if (format == "H") {
        return std::to_string(hour24);
    } else if (format == "HH") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", hour24);
        return std::string(buffer);
    }

    // Return empty string for invalid format
    return format;
}


std::string Formatter::minute(const Date &date, std::string format) {
    int minute = date.minute();

    // Return formatted minute string
    if (format == "m") {
        return std::to_string(minute);
    } else if (format == "mm") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", minute);
        return std::string(buffer);
    }

    // Return empty string for invalid format
    return format;
}


std::string Formatter::second(const Date &date, std::string format) {
    int second = date.second();

    // Return formatted second string
    if (format == "s") {
        return std::to_string(second);
    } else if (format == "ss") {
        char buffer[3];
        snprintf(buffer, 3, "%02d", second);
        return std::string(buffer);
    }

    // Return empty string for invalid format
    return format;
}


std::string Formatter::period(const Date &date, std::string format) {
    std::string period = (date.hour() < 12) ? "am" : "pm";

    // Return formatted period string
    if (format == "t") {
        return period.substr(0, 1);
    } else if (format == "tt") {
        return period;
    } else if (format == "T") {
        for (auto &c: period)
            c = toupper(c); // to upper case
        return period.substr(0, 1);
    } else if (format == "TT") {
        for (auto &c: period)
            c = toupper(c); // to upper case
        return period;
    }

    // Return empty string for invalid format
    return format;
}


std::string Formatter::timezone(const Date &date, std::string format) {
    int timezone = date.timezone();

    // Return formatted timezone string
    if (format == "z") {
        char buffer[4];
        snprintf(buffer, 4, "%+d", timezone);
        return std::string(buffer);
    } else if (format == "zz") {
        char buffer[4];
        snprintf(buffer, 4, "%+02i", timezone);
        return std::string(buffer);
    }

    // Return empty string for invalid format
    return format;
}
