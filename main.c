
// Seagate uses a fiscal year for their calculation which starts on the first Saturday in July (week 1)
// Ref: https://www.digital-detective.net/deciphering-seagate-date-codes/

// For example, the fiscal year 2021 starts on Saturday 4th July 2020 (Date Code 2111) and ends on Friday 2nd July 2021 (Date Code 21527).
// Date Code 13395 was manufactured on 3rd April 2013 (fiscal year 2013, week 39, day 5).

// 1st July 2000 was a Saturday

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char        *month[13] = {"July", "August", "September", "October", "November", "December", "January", "February", "March", "April", "May", "June", "July"};
int         days[13] = {31, 31, 30, 31, 30, 31, 31, 28, 31, 30, 31, 30, 31};

char        *name[7] = {"Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
int         adj[7] = {1, 7, 6, 5, 4, 3, 2};

int getNumber(char *string, int *pos, int count)
{
    char        tmp[3];

    strncpy(tmp, &string[*pos], count);
    tmp[count] = 0;
    *pos += count;

    return atoi(tmp);
}

int main(int argc, char *argv[])
{
    int         help = 0;

    int         year, week, day;
    int         offset, count, i, w;

    if (argc != 2)
        help = 1;
    else if (strlen(argv[1]) < 4 || strlen(argv[1]) > 5)
        help = 1;

    if (help)
    {
        printf("%s DATECODE\nThe date code is either YYWD or YYWWD\nY\tYear\nW\tWeek number (1 or 2 digits)\nD\tWeek day\n", argv[0]);

        return 1;
    }

    printf("%s -> ", argv[1]);

    i = 0;
    w = strlen(argv[1]) == 5 ? 2 : 1;
    year = getNumber(argv[1], &i, 2);
    week = getNumber(argv[1], &i, w);
    day = getNumber(argv[1], &i, 1);

    day--;

    if (year / 4 * 4 == year)
        days[7] = 29; // leap year

    year--;
    offset = adj[(year + year / 4) % 7];

    week--;
    count = week * 7 + day + offset;
    for (i = 0; i < 12; i++)
    {
        if (count <= days[i])
            break;

        count -= days[i];
    }
    if (i > 5)
        year++;

    printf("%s %i %s 20%s%i\n", name[day], count, month[i], year < 10 ? "0" : "", year);

    return 0;
}
