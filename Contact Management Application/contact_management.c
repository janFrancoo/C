#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int globalID = 1;
COORD coord = {0, 0};

typedef struct{
    int id;
    char name[30];
    char phone[20];
    char address[50];
    char email[30];
}contact;

typedef struct{
    contact c;
    struct node* next;
}node;

node* add_new_contact(node* head, char name[], char phone[], char address[], char email[]){
    contact c;
    node* n = malloc(sizeof(node));
    node* t = head;

    c.id = ++globalID;
    strcpy(c.name, name);
    strcpy(c.phone, phone);
    strcpy(c.address, address);
    strcpy(c.email, email);

    n->c = c;
    n->next = NULL;

    if(head == NULL){
        return n;
    }

    while(t->next != NULL)
        t = t->next;

    t->next = n;

    return n;
}


node* menu(node* head){
    int choice;
    char name[30], phone[20], address[50], email[30];

    while(choice != 6){
        system("CLS");

        printf("\n\n\t\t*** WELCOME TO THE CONTACT MANAGEMENT SYSTEM ***");
        printf("\n\n\t\t\t\tMAIN MENU");
        printf("\n\t\t\t=========================");
        printf("\n\t\t\t1. Add a new contact");
        printf("\n\t\t\t2. Edit an existing contact");
        printf("\n\t\t\t3. Search a contact");
        printf("\n\t\t\t4. Delete a contact");
        printf("\n\t\t\t5. List all contacts");
        printf("\n\t\t\t6. Exit from the application");
        printf("\n\t\t\t=========================");

        printf("\n\t\t\t|| Enter: ");
        scanf("%d", &choice);
        system("CLS");

        switch(choice){
            case 1:
                printf("Name: ");
                scanf("%s", name);
                printf("Phone: ");
                scanf("%s", phone);
                printf("Address: ");
                scanf("%s", address);
                printf("E-Mail: ");
                scanf("%s", email);

                if(head == NULL){
                    head = add_new_contact(head, name, phone, address, email);
                }
                else{
                    add_new_contact(head, name, phone, address, email);
                }
                break;
            case 2:
                edit_contact(head);
                break;
            case 3:
                search_contact(head);
                break;
            case 4:
                delete_contact(&head);
                break;
            case 5:
                list_all_contacts(head);
                break;
        }
    }

    return head;
}

void edit_contact(node* head){
    node* t = head;
    char name[30], phone[20], address[50], email[30];

    printf("Name: ");
    scanf("%s", &name);

    while(t != NULL){
        if(strcmp(t->c.name, name) == 0){
            printf("Name: ");
            scanf("%s", name);
            printf("Phone: ");
            scanf("%s", phone);
            printf("Address: ");
            scanf("%s", address);
            printf("EMail: ");
            scanf("%s", email);

            strcpy(t->c.name, name);
            strcpy(t->c.phone, phone);
            strcpy(t->c.address, address);
            strcpy(t->c.email, email);
        }
        t = t->next;
    }

    if(t == NULL)
        printf("Not Found.");
}

void search_contact(node* head){
    int found = 0;
    char name[30], choice;
    node* t = head;

    printf("Name: ");
    scanf("%s", name);

    while(t != NULL){
        if(strcmp(t->c.name, name) == 0){
            print_contact(t->c, 0);
            found = 1;
        }
        t = t->next;
    }

    if(found == 0){
        printf("Not Found.");
    }

    printf("\n\n\n\t====================================================== Enter a Key for Menu: ");
    scanf("%c", &choice);
    scanf("%c", &choice);

}

void delete_contact(node **head){
    char name[30];
    node* t = *head, *prev;

    printf("Name: ");
    scanf("%s", name);

    if(t != NULL && strcmp(t->c.name, name) == 0){
        *head = t->next;
        free(t);
        return;
    }

    while(t != NULL && strcmp(t->c.name, name) != 0){
        prev = t;
        t = t->next;
    }

    if(t == NULL)
        return;

    prev->next = t->next;
    free(t);
}

void list_all_contacts(node *head){
    char choice;
    node* t = head;

    printf("\n\t\t==============================================");
    printf("\n\t\t\t\tLIST OF CONTACTS");
    printf("\n\t\t==============================================");
    printf("\n\n\t\tNAME\t\t\tPHONE\t\t\tADDRESS\t\t\tEMAIL");
    printf("\n\t=============================================================================================");

    while(t != NULL){
        print_contact(t->c, 1);
        printf("\n\n\n\t====================================================== Enter N for Next, anything else for Menu: ");
        scanf("%c", &choice);
        scanf("%c", &choice);
        if(choice == 'N'){
            t = t->next;
            gotoxy(0, 6);
        }
        else{
            break;
        }
    }

    if(t == NULL){
        gotoxy(0, 7);
        for(int i=0; i<1000; i++){
            printf(" ");
        }
        printf("\n\n\t\t\tLIST IS EMPTY - Q for Exit, anything else for Menu: ");
        scanf("%d", &choice);
        if(choice == 'Q'){
            exit(0);
        }
    }

}

void print_contact(contact c, int print_type){
    if(print_type == 0){                // Default print
        printf("\n\t\t%s", c.name);
        printf("\n\t\t%s", c.phone);
        printf("\n\t\t%s", c.address);
        printf("\n\t\t%s\n", c.email);
    }
    else{                               // Print with controlled cursor
        printf("\n\t\t%s", c.name);
        gotoxy(40, 7);
        printf("%s", c.phone);
        gotoxy(coord.X + 24, 7);
        printf("%s", c.address);
        gotoxy(coord.X + 24, 7);
        printf("%s\n", c.email);
    }
}

void gotoxy(int x, int y){
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

node* read_contacts_from_file(node* head){
    int i;
    FILE *fp;
    char str[130];

    fp = fopen("contacts", "r");

    if(fp == NULL){
        printf("ERROR!");
        exit(0);
    }

    while(fscanf(fp, "%s", str) != EOF){
        i = 0;
        char *p = strtok(str, ",");
        char *array[4];

        while (p != NULL){
            array[i++] = p;
            p = strtok (NULL, ",");
        }

        printf("%s,%s,%s,%s", array[0], array[1], array[2], array[3]);

        if(head == NULL){
            head = add_new_contact(head, array[0], array[1], array[2], array[3]);
        }
        else{
            add_new_contact(head, array[0], array[1], array[2], array[3]);
        }
    }

    fclose(fp);

    return head;
}

void write_contacts_from_file(node *head){
    FILE* fp;
    node* t = head;

    fp = fopen("contacts", "w");

    if(fp == NULL){
        printf("ERROR!");
        exit(0);
    }

    while(t != NULL){
        fprintf(fp, "%s,", t->c.name);
        fprintf(fp, "%s,", t->c.phone);
        fprintf(fp, "%s,", t->c.address);
        fprintf(fp, "%s\n", t->c.email);
        t = t->next;
    }

    fclose(fp);
}

int main()
{
    node* head = NULL;
    head = read_contacts_from_file(head);
    head = menu(head);
    write_contacts_from_file(head);

    return 0;
}
