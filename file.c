#include <stdio.h>
#include "file.h"

//-------------------------------------save contact----------------------------------------------//

void saveContactsToFile(AddressBook *addressBook) 
{
  FILE *fptr=fopen("contacts.csv","w");
  if(fptr==NULL)
  {
    printf("file is not opening\n");
    return;
  }
  fprintf(fptr,"#%d\n",addressBook->contactCount);
  for(int i=0;i<addressBook->contactCount;i++)
  {
    fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
  }
  fclose(fptr);
}

//-------------------------------------load contact----------------------------------------------//

void loadContactsFromFile(AddressBook *addressBook) 
{
  FILE *fptr=fopen("contacts.csv","r");
  if(fptr==NULL)
  {
    printf("file is not opening\n");
    return;
  }
  fscanf(fptr,"#%d",&addressBook->contactCount);
  for(int i=0;i<addressBook->contactCount;i++)
  {
    fscanf(fptr," %[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
  }
  fclose(fptr);
}