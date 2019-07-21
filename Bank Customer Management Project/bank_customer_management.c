#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <string.h>

struct acc{
    int id;
    char name[30];
    char surname[30];
    char address[30];
    char phone[30];
    char createdDate[30];
    char lastOpDate[30];
    float balance;
};

typedef struct acc account;

int menu(){

    system("cls");
    int choice;

    printf("\n\n\n\t\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n\n\n");
    printf("\t\t\t\t   \xB2\xB2\xB2\xB2\xB2 WELCOME TO THE MAIN MENU \xB2\xB2\xB2\xB2\xB2\n\n\n");
    printf("\t\t\t\t1. Create New Account\n");
    printf("\t\t\t\t2. Update an Account\n");
    printf("\t\t\t\t3. Transactions\n");
    printf("\t\t\t\t4. Check Details of an Account\n");
    printf("\t\t\t\t5. Remove an Account\n");
    printf("\t\t\t\t6. Customer's List\n");
    printf("\t\t\t\t7. Exit\n\n\n");
    printf("\t\t\t\tEnter your choice: ");
    scanf("%d", &choice);

    if(choice < 1 || choice > 7){
        printf("\t\t\t\tError! Enter a valid number.\n\n\n\n\n\n");
        sleep(3);
        choice = menu();
        return choice;
    }

    return choice;

}

account *create_account(){
    int id;
    char name[30], surname[30], address[30], phone[30], buffer[30];
    float balance;
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer,30,"%x", info);

    printf("\n\n\t\t\t\tEnter ID: ");
    scanf("%d", &id);
    printf("\t\t\t\tEnter Name - Surname: ");
    scanf("%s %s", name, surname);
    printf("\t\t\t\tEnter Address: ");
    scanf("%s", address);
    printf("\t\t\t\tEnter Phone: ");
    scanf("%s", phone);
    printf("\t\t\t\tEnter Balance: ");
    scanf("%f", &balance);

    account *newAcc = malloc(sizeof(account));
    newAcc->id = id;
    strcpy(newAcc->name, name);
    strcpy(newAcc->surname, surname);
    strcpy(newAcc->address, address);
    strcpy(newAcc->phone, phone);
    strcpy(newAcc->createdDate, buffer);
    strcpy(newAcc->lastOpDate, buffer);
    newAcc->balance = balance;

    return newAcc;
};

void customers_list(){

    FILE *fp;
    fp = fopen("acc", "r");
    char str1[300];

    printf("\n\n\n");

    while(fscanf(fp, "%s", str1) != EOF){
        int i = 0;
        char *p = strtok(str1, ",");
        char *array[8];

        while (p != NULL){
            array[i++] = p;
            p = strtok (NULL, ",");
        }

        printf("\tCUSTOMER ID: %s\n", array[0]);
        printf("\tCUSTOMER NAME: %s\n", array[1]);
        printf("\tCUSTOMER SURNAME: %s\n", array[2]);
        printf("\tCUSTOMER ADDRESS: %s\n", array[3]);
        printf("\tCUSTOMER PHONE: %s\n", array[4]);
        printf("\tCUSTOMER BALANCE: %s\n", array[5]);
        printf("\tCUSTOMER CREATED DAY: %s\n", array[6]);
        printf("\tCUSTOMER LAST OPERATION DAY: %s\n", array[7]);
        printf("\t****************************\n");
    }

    fclose(fp);
}

void check_detail(){

    FILE *fp;
    char name[30], id[10];
    printf("Enter ID: ");
    scanf("%s", id);
    printf("Enter name: ");
    scanf("%s", name);

    fp = fopen("acc", "r");
    char str1[300];

    printf("\n\n\n");

    while(fscanf(fp, "%s", str1) != EOF){
        int i = 0;
        char *p = strtok(str1, ",");
        char *array[8];

        while (p != NULL){
            array[i++] = p;
            p = strtok (NULL, ",");
        }

        if(strcmp(array[0], id) == 0 || strcmp(array[1], name) == 0){
            int ID = atoi(array[0]);
            float balance = strtod(array[5], NULL);
            printf("\tCUSTOMER ID: %d\n", ID);
            printf("\tCUSTOMER NAME: %s\n", array[1]);
            printf("\tCUSTOMER SURNAME: %s\n", array[2]);
            printf("\tCUSTOMER ADDRESS: %s\n", array[3]);
            printf("\tCUSTOMER PHONE: %s\n", array[4]);
            printf("\tCUSTOMER BALANCE: %f\n", balance);
            printf("\tCUSTOMER CREATED DAY: %s\n", array[6]);
            printf("\tCUSTOMER LAST OPERATION DAY: %s\n", array[7]);
            printf("\t****************************\n");
        }
    }

    fclose(fp);

}

void update_account(){

    FILE *fp, *fp2;
    char name[30], id[10];
    printf("Enter ID: ");
    scanf("%s", id);
    printf("Enter name: ");
    scanf("%s", name);

    int newID;
    char newName[30], newSurname[30], newAddress[30], newPhone[30], newBuffer[30];
    float newBalance;
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(newBuffer, 30, "%x", info);

    fp = fopen("acc", "r");
    fp2 = fopen("acc_tmp", "a+");
    char str1[300];

    printf("\n\n\n");

    while(fscanf(fp, "%s", str1) != EOF){
        int i = 0;
        char *p = strtok(str1, ",");
        char *array[8];

        while (p != NULL){
            array[i++] = p;
            p = strtok (NULL, ",");
        }

        if(strcmp(array[0], id) == 0 || strcmp(array[1], name) == 0){
            printf("\n\n\t\t\t\tEnter ID: ");
            scanf("%d", &newID);
            printf("\t\t\t\tEnter Name - Surname: ");
            scanf("%s %s", newName, newSurname);
            printf("\t\t\t\tEnter Address: ");
            scanf("%s", newAddress);
            printf("\t\t\t\tEnter Phone: ");
            scanf("%s", newPhone);
            printf("\t\t\t\tEnter Balance: ");
            scanf("%f", &newBalance);

            fprintf(fp2, "%d,", newID);
            fprintf(fp2, "%s,", newName);
            fprintf(fp2, "%s,", newSurname);
            fprintf(fp2, "%s,", newAddress);
            fprintf(fp2, "%s,", newPhone);
            fprintf(fp2, "%f,", newBalance);
            fprintf(fp2, "%s,", array[6]);
            fprintf(fp2, "%s\n", newBuffer);
        }
        else{
            int newID = atoi(array[0]);
            fprintf(fp2, "%d,", newID);
            fprintf(fp2, "%s,", array[1]);
            fprintf(fp2, "%s,", array[2]);
            fprintf(fp2, "%s,", array[3]);
            fprintf(fp2, "%s,", array[4]);
            float newBalance = strtod(array[5], NULL);
            fprintf(fp2, "%f,", newBalance);
            fprintf(fp2, "%s,", array[6]);
            fprintf(fp2, "%s\n", array[7]);
        }
    }

    fclose(fp);
    fclose(fp2);

    remove("acc");
    rename("acc_tmp", "acc");
    printf("\t\t\t\tAccount(s) has been updated.\n\n");
    sleep(2);

}

void delete_account(){

    FILE *fp, *fp2;
    char name[30], id[10];
    printf("Enter ID: ");
    scanf("%s", id);
    printf("Enter name: ");
    scanf("%s", name);

    fp = fopen("acc", "r");
    fp2 = fopen("acc_tmp", "a+");
    char str1[300];

    while(fscanf(fp, "%s", str1) != EOF){
        int i = 0;
        char *p = strtok(str1, ",");
        char *array[8];

        while (p != NULL){
            array[i++] = p;
            p = strtok (NULL, ",");
        }

        if(strcmp(array[0], id) != 0 || strcmp(array[1], name) != 0){
            int newID = atoi(array[0]);
            fprintf(fp2, "%d,", newID);
            fprintf(fp2, "%s,", array[1]);
            fprintf(fp2, "%s,", array[2]);
            fprintf(fp2, "%s,", array[3]);
            fprintf(fp2, "%s,", array[4]);
            float newBalance = strtod(array[5], NULL);
            fprintf(fp2, "%f,", newBalance);
            fprintf(fp2, "%s,", array[6]);
            fprintf(fp2, "%s\n", array[7]);
        }
    }

    fclose(fp);
    fclose(fp2);

    remove("acc");
    rename("acc_tmp", "acc");
    printf("\t\t\t\tAccount(s) has been deleted.\n\n");
    sleep(2);
}

void transactions(){

    FILE *fp, *fp2;
    char name[30], id[10], name2[30], id2[10], newBuffer[30];
    printf("From Whom ID: ");
    scanf("%s", id);
    printf("From Whom Name: ");
    scanf("%s", name);
    printf("To Whom ID: ");
    scanf("%s", id2);
    printf("To Whom Name: ");
    scanf("%s", name2);

    float sendB;
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(newBuffer, 30, "%x", info);

    fp = fopen("acc", "r");
    fp2 = fopen("acc_tmp", "a+");
    char str1[300];

    printf("\n\n\n");

    while(fscanf(fp, "%s", str1) != EOF){
        int i = 0;
        char *p = strtok(str1, ",");
        char *array[8];

        while (p != NULL){
            array[i++] = p;
            p = strtok (NULL, ",");
        }

        if(strcmp(array[0], id) == 0 || strcmp(array[1], name) == 0){
            printf("\t\t\t\tEnter Balance That You Want to Send: ");
            scanf("%f", &sendB);
            float newBalance = strtod(array[5], NULL);
            if(sendB > newBalance){
                printf("\t\t\t\tInsufficient balance!\n");
                fclose(fp);
                fclose(fp2);
                remove("acc_tmp");
                return;
            }
            newBalance -= sendB;

            int newID = atoi(array[0]);
            fprintf(fp2, "%d,", newID);
            fprintf(fp2, "%s,", array[1]);
            fprintf(fp2, "%s,", array[2]);
            fprintf(fp2, "%s,", array[3]);
            fprintf(fp2, "%s,", array[4]);
            fprintf(fp2, "%f,", newBalance);
            fprintf(fp2, "%s,", array[6]);
            fprintf(fp2, "%s\n", newBuffer);
        }
        else if(strcmp(array[0], id2) == 0 || strcmp(array[1], name2) == 0){
            int newID = atoi(array[0]);
            fprintf(fp2, "%d,", newID);
            fprintf(fp2, "%s,", array[1]);
            fprintf(fp2, "%s,", array[2]);
            fprintf(fp2, "%s,", array[3]);
            fprintf(fp2, "%s,", array[4]);
            float newBalance = strtod(array[5], NULL);
            newBalance += sendB;
            fprintf(fp2, "%f,", newBalance);
            fprintf(fp2, "%s,", array[6]);
            fprintf(fp2, "%s\n", newBuffer);
        }
        else{
            int newID = atoi(array[0]);
            fprintf(fp2, "%d,", newID);
            fprintf(fp2, "%s,", array[1]);
            fprintf(fp2, "%s,", array[2]);
            fprintf(fp2, "%s,", array[3]);
            fprintf(fp2, "%s,", array[4]);
            float newBalance = strtod(array[5], NULL);
            fprintf(fp2, "%f,", newBalance);
            fprintf(fp2, "%s,", array[6]);
            fprintf(fp2, "%s\n", array[7]);
        }
    }

    fclose(fp);
    fclose(fp2);

    remove("acc");
    rename("acc_tmp", "acc");
    printf("\t\t\t\tSuccessfully sent money!\n\n");
    sleep(2);
}

int main()
{
    int choice = 0;
    char c[1];
    account *newAcc;

    while(choice != 7){
        choice = menu();
        switch(choice){
            case 1:
                newAcc = create_account();
                printf("\t\t\t\tNew account created successfully!\n");
                sleep(5);
                FILE *fp;
                fp = fopen("acc", "a+");
                fprintf(fp, "%d,", newAcc->id);
                fprintf(fp, "%s,", newAcc->name);
                fprintf(fp, "%s,", newAcc->surname);
                fprintf(fp, "%s,", newAcc->address);
                fprintf(fp, "%s,", newAcc->phone);
                fprintf(fp, "%f,", newAcc->balance);
                fprintf(fp, "%s,", newAcc->createdDate);
                fprintf(fp, "%s\n", newAcc->lastOpDate);
                fclose(fp);
                break;
            case 2:
                update_account();
                printf("\tPress 'Enter' for menu.\n\n\n");
                scanf("%c", c);
                scanf("%c", c);
                break;
            case 3:
                transactions();
                printf("\tPress 'Enter' for menu.\n\n\n");
                scanf("%c", c);
                scanf("%c", c);
                break;
            case 4:
                check_detail();
                printf("\tPress 'Enter' for menu.\n\n\n");
                scanf("%c", c);
                scanf("%c", c);
                break;
            case 5:
                delete_account();
                printf("\tPress 'Enter' for menu.\n\n\n");
                scanf("%c", c);
                scanf("%c", c);
                break;
            case 6:
                customers_list();
                printf("\tPress 'Enter' for menu.\n\n\n");
                scanf("%c", c);
                scanf("%c", c);
                break;
            case 7:
                printf("\t\t\t\tHave a good day!");
                sleep(3);
                break;
        }
    }

    return 0;
}
