#include <stdio.h>
#include "conversion.h"

int main()
{
    int day, month, year, year_day, days, mday;

    day = 26, month = 4, year = 2004, year_day = 152;
    days = day_of_year(year, month, day);
    if (!days)
        return 1;
    printf("Day of the year: %i\n", days);
    mday = month_day(year, year_day, &month, &day);
    if (!mday)
        return 1;
    printf("Month day: %i, month: %i\n", day, month);
    printf("Month name: %s\n", month_name(month));
    return 0;
}