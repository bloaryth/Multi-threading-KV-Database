#pragma once

#include "Logger/Logger.h"

class Date
{
public:
    Date(int year_, int month_, int day_, int hour_, int minute_);
    Date();
    ~Date() = default;

    const int year;
    const int month;
    const int day;
    const int hour;
    const int minute;
};


Date::Date(int year_, int month_, int day_, int hour_, int minute_) :
        year(year_), month(month_), day(day_), hour(hour_), minute(minute_) {}

Date::Date() :
        year(-1), month(-1), day(-1), hour(-1), minute(-1) {}


