#define DAYS_IN_A_YEAR 365

static char calendar[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

static int is_leap_year(unsigned int year)
{
    return year % 4 == 0;
}

static int is_valid(unsigned int month, unsigned int day)
{
    return (month > 12 || day > 31) ? 0 : 1;
}

static int is_valid2(unsigned int month, unsigned int year_day)
{
    return (month > 12 || year_day > DAYS_IN_A_YEAR + 1) ? 0 : 1;
}

unsigned int day_of_year(unsigned int year, unsigned int month, unsigned int day)
{
    if (!is_valid(month, day))
        return 0;
    int i, days, leap;
    leap = is_leap_year(year);
    for (i = days = 0; i <= month; i++)
        days += *(*(calendar + leap) + i);
    return (days + day);
}

unsigned int month_day(
    unsigned int year,
    int year_day,
    unsigned int *month,
    unsigned int *day)
{
    if (!is_valid(*month, *day))
        return 0;
    int leap, i, days;
    leap = is_leap_year(year);
    for (i = 0; (days = *(*(calendar + leap) + i)) < year_day; i++)
        year_day -= days;
    *month = i;
    *day = year_day;
    return 1;
}

char *month_name(unsigned int n)
{
    static char *months[13] = {
        "Invalid month", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};
    return (n < 1 || n > 12) ? *months : *(months + n);
}