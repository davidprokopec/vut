#include <stdio.h>
#include <string.h>

struct date_t {
    int year;
    int month;
    int day;
};

int is_valid_date(struct date_t date)
{
    if (date.year > 0 && date.year < 2500 && date.month > 0 && date.month <= 12 && date.day > 0 && date.day <= 31) {
        return 1;
    }
    return 0;

}

int main()
{
    struct date_t date;
    printf("Please specify the date (format yyyy mm dd): ");
    scanf("%d %d %d", &date.year, &date.month, &date.day);

    int isValid = is_valid_date(date);

    if(isValid) {
        printf("Date %n %d %n is valid", date.year, date.month, date.day);
    } else {
        printf("Date %n %d %n is invalid", date.year, date.month, date.day);
   }

    return 0;

}