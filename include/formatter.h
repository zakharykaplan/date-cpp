//
//  formatter.h
//  Date string formatter header file.
//
//  Created by Zakhary Kaplan on 2019-12-03.
//  Copyright © 2019 Zakhary Kaplan. All rights reserved.
//

#pragma once

#include <string>
using std::string;

#include "date.h"

//  -- Date Formatting Table --
//  d       day     1       31
//  dd      day     01      31
//  M       month   1       12
//  MM      month   01      12
//  MMM     month   Jan     Dec
//  MMMM    month   January December
//  y       year    0       99
//  yy      year    00      99
//  yyy     year    000     9999
//  yyyy    year    0000    9999
//  c       century 0       99
//  cc      century 00      99
//
//  -- Time Formatting Table --
//  h       hour    0       12
//  hh      hour    00      12
//  H       hour    1       12
//  HH      hour    01      12
//  m       minute  0       59
//  mm      minute  00      59
//  s       second  0       59
//  ss      second  00      59
//  t       period  a       p
//  tt      period  am      pm
//  T       period  A       P
//  TT      period  AM      PM
//  z       tz      +0      +12
//  zz      tz      +00     +12


class Formatter {
    private:
        // Date formatting
        static string day(const Date &date, string format);
        static string month(const Date &date, string format);
        static string year(const Date &date, string format);
        static string century(const Date &date, string format);
        // Time formatting
        static string hour(const Date &date, string format);
        static string minute(const Date &date, string format);
        static string second(const Date &date, string format);
        static string period(const Date &date, string format);
        static string tz(const Date &date, string format);

    public:
        static string format(const Date &date);
};