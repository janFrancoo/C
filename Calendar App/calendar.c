#include <stdio.h>
#include <stdlib.h>
#include<windows.h>

struct date{
    int day;
    int month;
    int year;
};

COORD coord = {0, 0};
char months[12][15] = {"JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE",
                    "JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMER", "DECEMBER"};
char days[7][10] = {"MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY",
                    "SUNDAY"};

void gotoxy (int x, int y){
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int menu(){
    int choice;

    printf("WELCOME TO CALENDAR APP\n\n");
    printf("1. FIND OUT THE DAY\n");
    printf("2. SEE A MONTH\n");
    printf("3. EXIT\n");

    choice = getch();
    return choice;
}

int find_out_the_day(struct date d){
    int leapCount = 0, i, firstDayOfYear, totalDays = 0, day;
    for(i=1919; i<d.year; i++){
        if(is_leap_year(i)) leapCount++;
    }
    firstDayOfYear = ((d.year - 1919) + 3 + leapCount) % 7; // 3 for (01/01/1919 -> Wednesday)
    if(d.month == 1){
        day = (d.day + firstDayOfYear - 1) % 7;
        if(day != 0){
            return day;
        }
        else{
            return 7;
        }
    }
    else{
        for(i=1; i<d.month; i++)
            totalDays += days_of_month(i);
        day = ((d.day + totalDays) + firstDayOfYear - 1) % 7;
        if(day != 0){
            return day;
        }
        else{
            return 7;
        }
    }

    return 0;
}

void see_month(struct date d){
    system("CLS");
    int i, x = 26, y = 7, choice, noteCount, startDay;
    printf("\n\n\n\t\t\t----------------------------\n");
    printf("\t\t\t\t%s %d\n", months[d.month-1], d.year);
    printf("\t\t\t----------------------------\n");
    printf("\t\t\t  M   T   W   P   F   S   S\n");

    struct date d2;
    d2.day = 1;
    d2.month = d.month;
    d2.year = d.year;
    startDay = find_out_the_day(d2) - 1;
    x = 26 + (startDay * 4);

    for(i=1; i<=days_of_month(d.month, d.year); i++){
        if(x > 50){
            x = 26;
            y++;
        }
        gotoxy(x, y);
        printf("%d", i);
        x += 4;
    }

    while(1){
        noteCount = check_notes(d.month, d.year);
        printf("\n\n\n\t\t\tPrevious Month (Q) - Next Month(W)\n");
        if(!noteCount)
            printf("\t\t\tAdd Note (A) - Menu(M)\n");
        if(noteCount == 1){
            printf("\t\t\tSee Notes (S) - 1 Note In This Month\n");
            printf("\t\t\tAdd Note (A) - Menu(M)\n");
        }
        else{
            printf("\t\t\tSee Notes (S) - %d Notes In This Month\n", noteCount);
            printf("\t\t\tAdd Note (A) - Menu(M)\n");
        }
        choice = getch();
        if(choice == 113){
            if(d.month-1 < 0){
                d.month = 12;
                d.year = d.year - 1;
                see_month(d);
            }
            else{
                d.month = d.month - 1;
                see_month(d);
            }
        }
        if(choice == 119){
            if(d.month+1 > 12){
                d.month = 1;
                d.year = d.year + 1;
                see_month(d);
            }
            else{
                d.month = d.month + 1;
                see_month(d);
            }
        }
        if(choice == 97){
            add_note(d.month, d.year);
            printf("\t\t\tDone!");
            Sleep(3000);
            see_month(d);
        }
        if(choice == 115){
            see_notes(d.month, d.year);
            Sleep(10000);
            see_month(d);
        }
        if(choice == 109){
            main();
        }
    }
}

int check_notes(int month, int year){
    int noteCount = 0;
    char str1[100];
    FILE *fp = fopen("C:/Users/ErenS/Desktop/calendar_notes.txt", "r");
    if(fp == NULL){
        return -1;
    }
    while(fscanf(fp, "%s", str1) != EOF){
        int i = 0;
        char *p = strtok(str1, ",");
        char *array[3];

        while (p != NULL){
            array[i++] = p;
            p = strtok (NULL, ",");
        }

        if(atoi(array[0]) == month && atoi(array[1]) == year){
            noteCount++;
        }
    }

    fclose(fp);

    return noteCount;
}

void see_notes(int month, int year){
    char str1[100];
    FILE *fp = fopen("C:/Users/ErenS/Desktop/calendar_notes.txt", "r");
    if(fp == NULL){
        return;
    }
    printf("\n\n\n");
    while(fscanf(fp, "%s", str1) != EOF){
        int i = 0;
        char *p = strtok(str1, ",");
        char *array[3];

        while (p != NULL){
            array[i++] = p;
            p = strtok (NULL, ",");
        }

        if(atoi(array[0]) == month && atoi(array[1]) == year){
            printf("\t\t\t%s\n", array[2]);
        }
    }

    fclose(fp);
}

void add_note(int month, int year){
    char str1[100];
    FILE *fp = fopen("C:/Users/ErenS/Desktop/calendar_notes.txt", "a+");
    if(fp == NULL){
        return;
    }
    printf("\n\n\n");
    printf("\t\t\tEnter note: ");
    scanf("%s", str1);
    fprintf(fp, "%d,%d,%s\n", month, year, str1);
    fclose(fp);
}

int days_of_month(int month, int year){
    if((month - 1) % 2 == 0){
        return 31;
    }
    else if((month - 1) == 1){
        if(is_leap_year(year))   return 29;
        else    return 28;
    }
    else{
        return 30;
    }
}

int is_leap_year(int year){
    if((year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0))) return 1;
    return 0;
}

int main()
{
    int choice, day;
    struct date d;
    system("COLOR 12");

    while(1){
        system("CLS");
        choice = menu();
        if (choice == 49){
            system("CLS");
            printf("\n\n\n\t\tENTER A DATE (DD-MM-YYYY): ");
            scanf("%d %d %d", &d.day, &d.month, &d.year);
            if(d.month > 12 || d.month < 1 || d.day > days_of_month(d.month, d.year)
                || d.day < 1 || d.year < 1919){
                printf("\tPlease enter a valid date!\n");
                Sleep(3000);
            }
            else{
                day = find_out_the_day(d);
                printf("\n\n\t\t\tDAY IS %s", days[day - 1]);
                Sleep(5000);
            }
        }
        if(choice == 50){
            system("CLS");
            printf("\n\n\n\t\tENTER A DATE (MM-YYYY): ");
            scanf("%d %d", &d.month, &d.year);
            if(d.month > 12 || d.month < 1 || d.year < 1919){
                printf("\tPlease enter a valid date!\n");
                Sleep(3000);
            }
            else{
                see_month(d);
            }
        }
        if(choice == 51){
            printf("\n\nTHANKS!\n");
            Sleep(2000);
            exit(0);
        }
    }

    return 0;
}
