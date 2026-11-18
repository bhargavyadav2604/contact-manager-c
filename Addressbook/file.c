
#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)// function writeing the data to file
{
    FILE *fpt = fopen("contacts.csv", "w");

    if (fpt == NULL)
    {
        printf("Can't access file contacts.csv!\n");
        return;
    }

    fprintf(fpt, "#%d\n", addressBook->contactCount);

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fpt, "%s,%s,%s\n",
                addressBook->contacts[i].name,
                addressBook->contacts[i].phone,
                addressBook->contacts[i].email);
    }

    fclose(fpt);
}

void loadContactsFromFile(AddressBook *addressBook)// function to reading the data from the file
{
    FILE *fp;

    if ((fp = fopen("contacts.csv", "r")) == NULL)
    {
        addressBook->contactCount = 0;
        return;
    }

    if (fscanf(fp, "#%d\n",
               &addressBook->contactCount) != 1)
    {
        addressBook->contactCount = 0;
        fclose(fp);
        return;
    }

    if (addressBook->contactCount > MAX_CONTACTS)
    {
        addressBook->contactCount = MAX_CONTACTS;
    }

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fscanf(fp,
               "%49[^,],%19[^,],%49[^\n]\n",
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    fclose(fp);
}
