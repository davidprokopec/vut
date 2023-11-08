#include <stdio.h>

struct date_t {
    int year;
    int month;
    int day;
};

void compare_dates(struct date_t date1, struct date_t date2) {
    if(date1.year > date2.year) {
        printf("Date #1 is later");
    } else if (date1.year < date2.year) {
        printf("Date #2 is later");
    } else {
        if(date1.month > date2.month) {
            printf("Date #1 is later");
        } else if (date1.month < date2.month) {
            printf("Date #2 is later");
        } else {
            if (date1.day > date2.day) {
                printf("Date #1 is later");
            } else if(date1.day < date2.day) {
                printf("Date #2 is later");
            } else {
                printf("both dates are the same");
            }
        }
    }
}

int main() {
    struct date_t date1, date2;

    printf("Please specify the first date (format yyyy mm dd): ");
    scanf("%d %d %d", &date1.year, &date1.month, &date1.day);
    printf("Please specify the second date (format yyyy mm dd): ");
    scanf("%d %d %d", &date2.year, &date2.month, &date2.day);


    compare_dates(date1, date2);
    printf("\n");
    return 0;
}