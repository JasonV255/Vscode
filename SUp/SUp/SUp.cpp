

#include <stdlib.h>
#include <stdio.h>

int main()
{
    int day, month, year;

    puts("Insert a date (dd/mm/yyyy):");
    scanf_s ("%d/%d/%d", &day, &month, &year);
    printf("Inserted date: %d/%d/%d", day, month, year);
    return 0;
}
