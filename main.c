#include <stdio.h>
#include<stdio_ext.h>
#include "contact.h"

int main() {
    int choice=0;
    char tsearch[50];
    int sortChoice=0;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook,-1);
                break;
            case 2:
                __fpurge(stdin);
                printf("Searching contacts...\n");
                printf("Enter name, phone or email to search :\t");
                scanf("%[^\n]",tsearch);
                searchContact(&addressBook, tsearch);
                break;
            case 3:
                printf("Editing...\n");
                __fpurge(stdin);
                
             editContact(&addressBook);
                break;
            case 4:
                __fpurge(stdin);
                printf("\nEnter the Name or phone no. or email of contact to delete : ");
                scanf("%[^\n]",tsearch);
                deleteContact(&addressBook,tsearch);
                break;
            case 5:          
                printf("Choose sorting criteria:\n");
                printf("1. Sort by Name\n");
                printf("2. Sort by Phone\n");
                printf("3. Sort by Email\n");
                scanf("%d", &sortChoice);
               listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving...\n");
                saveContactsToFile(&addressBook);
                break;   
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        __fpurge(stdin);
        
    } while (choice!=7);
    
       return 0;
}