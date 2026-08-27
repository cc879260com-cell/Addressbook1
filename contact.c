#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdio_ext.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"
#include <ctype.h>

int isvalidName(char *name);
int isvalidphone(char *phone);
int isvalidemail(char *email);

int contactCount=0;
char tname[100];
char tphone[11];
char temail[50];
char tsearch1[100];
char auth=0;
char auth2=0;
int i,slno=1;
int choice,editflag=0;
int indexar[101];



void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    printf("\n\nSL.No\tNAME \t\tPHONE\t\t\tEMAIL\n");
    printf("------------------------------------------------------------------------------------------------------\n"); 

   while(1)
   {
    switch (sortCriteria) {
        case 1: // Sort by Name
            for (i = 0; i < addressBook->contactCount - 1; i++) {
                for (int j = i + 1; j < addressBook->contactCount; j++) {
                    if (strcmp(addressBook->contacts[i].name, addressBook->contacts[j].name) > 0) {
                        Contact temp = addressBook->contacts[i];
                        addressBook->contacts[i] = addressBook->contacts[j];
                        addressBook->contacts[j] = temp;
                    }
                }
            }
            break;
        case 2: // Sort by Phone
            for (i = 0; i < addressBook->contactCount - 1; i++) {
                for (int j = i + 1; j < addressBook->contactCount; j++) {
                    if (strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone) > 0) {
                        Contact temp = addressBook->contacts[i];
                        addressBook->contacts[i] = addressBook->contacts[j];
                        addressBook->contacts[j] = temp;
                    }
                }
            }
            break;
        case 3: // Sort by Email
            for (i = 0; i < addressBook->contactCount - 1; i++) {
                for (int j = i + 1; j < addressBook->contactCount; j++) {
                    if (strcmp(addressBook->contacts[i].email, addressBook->contacts[j].email) > 0) {
                        Contact temp = addressBook->contacts[i];
                        addressBook->contacts[i] = addressBook->contacts[j];
                        addressBook->contacts[j] = temp;
                    }
                }
            }
            break;
        default:
            printf("Invalid sorting criteria. Listing contacts without sorting.\n\n");
            break;
    }
    for( i=0;i<addressBook->contactCount;i++)
    {
        printf("%d\t%s\t\t%s\t\t%s\n", i+1,addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

    }
    printf("\nPress any key to return to main menu : ");
    auth2='\0';
    scanf("%c",&auth2);
    if(auth2!=0){ return;}

    }
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook, int contact)
    {
            __fpurge(stdin);
        if(contact == -1 || editflag==0) { contact=addressBook->contactCount;
        printf("Creating a new contact...\n");
        printf("------------------------------------------------------------------------------------------------------\n"); }
 
        printf("Enter name of the contact :\t");
        scanf("%[^\n]", tname);
        while(1)
        {
            if(isvalidName(tname))
            {
                break;
            }
            else
            {
                __fpurge(stdin);
                printf("Enter name of the contact :\t");
                scanf("%[^\n]", tname);
            }
        }
        __fpurge(stdin);
        printf("Name recorded !\nEnter the Phone number :\t");
        scanf("%s",tphone);
        while(1)
        {
            if(isvalidphone(tphone))
            {
                break;
            }
            else
            {
                printf("Please enter a valid phone number again : \t");
                scanf("%s",tphone);

            }
        }
        __fpurge(stdin);
        printf("Phone number recorded !\nEnter the email ID :\t");
        scanf("%s",temail);
        while(1)
        {
            if(isvalidemail(temail))
            {
                break ;
            }
            else
            {
            printf("\nPlease enter a valid email ID again :\t");
                scanf("%s",temail);  
            }
        }
        __fpurge(stdin);
        printf("\nName, Phone, email ID is recorded successfully !\nPress any key to save this contact, or press 0 to discard :\t");
        scanf("%c",&auth);
        if(auth!='0')
    {
        short int flag=0;
       if(editflag==0)
       {

        
                for(i=0;i<addressBook->contactCount;i++)
                {
                    if(strcmp(addressBook->contacts[i].name,tname)==0)
                    {
                        printf("\nContact with the same name already exists !");
                        flag=1;
                        break;
                    }
                    if(strcmp(addressBook->contacts[i].phone,tphone)==0)
                    {
                        printf("\nContact with the same phone number already exists !");
                        flag=1;
                        break;
                    }
                    if(strcmp(addressBook->contacts[i].email,temail)==0)
                    {
                        printf("\nContact with the same email ID already exists !");
                        flag=1;
                        break;
                                }            
                 }
        }
    if(flag==0)
    {
        { printf("\nContact is saved successfully !!\n"); 
            printf("------------------------------------------------------------------------------------------------------\n"); 

            strcpy((addressBook->contacts[contact].name), tname);
            strcpy((addressBook->contacts[contact].phone), tphone);
            strcpy((addressBook->contacts[contact].email), temail);

            if(editflag==0)
            {
                addressBook->contactCount++;
            
            printf("\nPress any key to return to main menu : ");
            __fpurge(stdin);
            auth2='\0';
            scanf("%c",&auth2);
            if(auth2!=0){ return;}
            }
        }
    }
    else
    {
        __fpurge(stdin);
        printf("\nDo you want to retry ? Press 1 to retry or 0 to discard : ");
        scanf("%c",&auth2);
        if(auth2=='1')
        {
            createContact(addressBook,contact);
        }
        else
        {
            printf("\nContact is discarded !\n");
            __fpurge(stdin);
            printf("\nPress any key to return to main menu : ");
            auth2='\0';
            scanf("%c",&auth2);
            if(auth2!=0){ return;}
        }
    }	/* Define the logic to create a Contacts */
    }   
    else 
    {
        printf("\nContact is discarded !\n");
        return;
    }
}

void searchContact(AddressBook *addressBook,char* tsearch) 
{
    short int flag=0;
    
    slno=1;

    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strstr(addressBook->contacts[i].name,tsearch)!=NULL || strstr(addressBook->contacts[i].phone,tsearch)!=NULL || strstr(addressBook->contacts[i].email,tsearch)!=NULL)
        {
            flag=i+1;
            printf("%d\t%s\t\t%s\t\t%s\n",slno,addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            indexar[slno-1]=i;
            slno++;

        }
    } 
    if(flag==0)
    {
        printf("No contacts has Name, Email or phone number matching the entered input !\n");
    }
    if(editflag==0)
    {
        __fpurge(stdin);
    printf("\nPress any key to return to main menu : ");
    printf("This is in search function\n");
    auth2='\0';
    scanf("%c",&auth2);
    if(auth2!=0){  return ;}

    }
    /* Define the logic for search */
}

void editContact(AddressBook *addressBook)
{
    printf("\nEnter the Name or phone no. or email of contact to be edited : ");
                scanf("%[^\n]",tsearch1);
                editflag=1;
                searchContact(
                    addressBook, tsearch1);
    printf("\nChoose serial no. of contact to be edited : ");
    scanf("%d",&choice);
    if(choice<1 || choice>slno)
    {
        printf("Invalid choice !\n");
        return;
    }
    createContact(addressBook,indexar[choice-1]);
    editflag=0;
    return;


	/* Define the logic for Editcontact */
    
}

void deleteContact(AddressBook *addressBook,char* tsearch)
{
    short int flag=0;
   //Search + delete.
    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strstr(addressBook->contacts[i].name,tsearch)!=NULL || strstr(addressBook->contacts[i].phone,tsearch)!=NULL || strstr(addressBook->contacts[i].email,tsearch)!=NULL)
        {
            flag=i+1;
            printf("%d\t%s\t\t%s\t\t%s\n", i+1,addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
        }
    } 
    if(flag==0)
    {
        printf("No contacts has Name, Email or phone number matching the entered input !\n");
        return ; 
    }
    else
    {
        __fpurge(stdin);
        printf("\nChoose serial no. of contact to be deleted");
        scanf("%d",&choice);
        if(choice<1 || choice>addressBook->contactCount)
        {
            printf("Invalid choice !\n");
            return;
        }   
        choice=choice-1;
        for(i=choice;i<addressBook->contactCount-1;i++)
        {
            addressBook->contacts[i]=addressBook->contacts[i+1];
        }
        addressBook->contactCount--;
    }
	/* Define the logic for deletecontact */
   
}

int isvalidName(char *name) 
{
    // Check if the name contains only letters and spaces
    for (i = 0; name[i] != '\0'; i++) {
        if (!isalpha(name[i]) && name[i] != ' ') 
        {
            printf("Invalid name. Please enter a valid name.\n");
            return 0; // Invalid name
        }
    }
    return 1; // Valid name
}

int isvalidphone(char* phone)
{
    if(strlen(phone)<10){printf("Please enter 10 digits\n"); return 0;}
    if(phone[0]<(5+'0')){ printf("The first number should not be less than 5\n"); return 0; }
    for(i=0; phone[i]!=0;i++)
    {
        if(phone[i]<'0' || phone[i]>'9')
        {
            printf("Please enter only digits 0 - 9\n");
            return 0;
        }
    }
return 1;
}
int isvalidemail(char * email)
{
    int len = strlen(email);
    int at_count = 0;      // how many '@' symbols found
    int at_position = -1;  // where '@' is located
    int dot_after_at = 0;  // is there a '.' after the '@'?

    // length check
    if (len < 5) 
    {
        printf("Length of email is too short/invalid\n");
        return 0;
    }

    // Step 1: Count '@' symbols and find its position
    for (i = 0; i < len; i++) {
        if (email[i] == '@') {
            at_count = at_count + 1;
            at_position = i;
        }
    }

    // Must have exactly one '@'
    if (at_count != 1) {
        return 0;
    }

    // '@' cannot be the first or last character
    if (at_position == 0 || at_position == len - 1) {
        return 0;
    }


    //  Check character after '@' is not '.'
    if (email[at_position + 1] == '.') 
    {
        printf("Domain name missing / invalid\n");
        return 0;
    }

    //  Look for a '.' after the '@' symbol
    for (i = at_position + 1; i < len; i++) {
        if (email[i] == '.') 
        {

            dot_after_at = 1;
        }
    }

    if (dot_after_at == 0) {
        printf("Domain name missing / invalid\n");
        return 0;
    }

    // Step 5: Last character cannot be '.'
    if (email[len - 1] == '.') 
    {
        printf("Email should end with .com\n");
        return 0;
    }

    // Step 6: Check for spaces (not allowed in email)
    for (i = 0; i < len; i++) {
        if (email[i] == ' ') 
        {   
            printf("Space should not be used in email\n");
            return 0;
        }
    }
return 1;
}