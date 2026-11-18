#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"


void listContacts(AddressBook *addressBook)//for creat new contact
{
    Bubble_sort(addressBook);

    printf("-----------------------------------------------------------------------------\n");
    printf("|                               ADDRESS BOOK                                |\n");
    printf("-----------------------------------------------------------------------------\n");
    printf("| %-3s | %-25s | %-10s | %-25s |\n",
           "S.No", "Name", "Phone", "Email");
    printf("-----------------------------------------------------------------------------\n");

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-3d | %-25s | %-10s | %-25s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }

    printf("-----------------------------------------------------------------------------\n");
}


void initialize(AddressBook *addressBook)//for copy the contacts for the file
{
    addressBook->contactCount = 0;

    loadContactsFromFile(addressBook);
}


void createContact(AddressBook *addressBook)// for create Contact
{
    char str[30], str1[11], str2[30];
    int res;

    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address Book is Full!\n");
        return;
    }

    do
    {
        printf("Enter the name : ");
        scanf(" %[^\n]", str);

        res = validate_name(str);

    } while (res == 0);


    do
    {
        printf("Enter the phone : ");
        scanf(" %[^\n]", str1);

        res = validate_phone(str1, addressBook);

    } while (res == 0);


    do
    {
        printf("Enter the email : ");
        scanf(" %[^\n]", str2);

        res = validate_email(str2);

        if (res == 0)
        {
            printf("Invalide Email!\n");
        }

    } while (res == 0);


    strcpy(addressBook->contacts[addressBook->contactCount].name, str);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, str1);
    strcpy(addressBook->contacts[addressBook->contactCount].email, str2);//storing the data

    addressBook->contactCount++;

    printf("Contact created successfully!\n");
}


void searchContact(AddressBook *addressBook)// for search Contact
{
    int choise;

    printf("1.Name\n2.Phone\n3.Email\n4.Exite\n");
    printf("Enter the choise : ");
    scanf("%d", &choise);

    switch (choise)
    {
        case 1:
        {
            int count;

            int *str = search_by_name(addressBook, &count);//for search by name

            free(str);

            break;
        }

        case 2:
        {
            search_by_phone(addressBook);// for  search by phone
            break;
        }

        case 3:
        {
            search_by_email(addressBook);// for search by email
            break;
        }

        case 4:
        {
            printf("Exiting...\n");// for exiting
            return;
        }

        default:
        {
            printf("Invalid choice!\n");
            break;
        }
    }
}


void editContact(AddressBook *addressBook)// for edit Contact
{
    int choise;

    printf("1.Name\n2.Phone\n3.Email\n4.Exite\n");
    printf("Enter the choise : ");
    scanf("%d", &choise);

    switch (choise)
    {
        case 1:
        {
            int count;

            int *str = search_by_name(addressBook, &count);

            if (count == 0)
            {
                free(str);
                break;
            }

            int index;

            printf("Enter the index : ");
            scanf("%d", &index);

            if (index < 1 || index > count)
            {
                printf("Enter a valid index!\n");
                free(str);
                break;
            }

            int j = str[index - 1];

            edit(addressBook, j);// for edite

            free(str);

            break;
        }

        case 2:
        {
            int res = search_by_phone(addressBook);

            if (res >= 0)
            {
                edit(addressBook, res);
            }

            break;
        }

        case 3:
        {
            int res = search_by_email(addressBook);

            if (res >= 0)
            {
                edit(addressBook, res);
            }

            break;
        }

        case 4:
        {
            printf("Exiting...\n");
            return;
        }

        default:
        {
            printf("Invalid choice!\n");
            break;
        }
    }
}


void deleteContact(AddressBook *addressBook)// for deleteing the Contact
{
    int choise;

    printf("1.Name\n2.Phone\n3.Email\n4.Exite\n");
    printf("Enter the choise : ");
    scanf("%d", &choise);

    switch (choise)
    {
        case 1:
        {
            int count;

            int *str = search_by_name(addressBook, &count);

            if (count == 0)
            {
                free(str);
                break;
            }

            int index;

            printf("Enter the index : ");
            scanf("%d", &index);

            if (index < 1 || index > count)
            {
                printf("Enter a valid index!\n");
                free(str);
                break;
            }

            int j = str[index - 1];

            printf("Deleting contact at index %d\n", j);

            for (int i = j;
                 i < addressBook->contactCount - 1;
                 i++)
            {
                addressBook->contacts[i] =
                    addressBook->contacts[i + 1];
            }

            addressBook->contactCount--;

            printf("Delete successful.....\n");

            free(str);

            break;
        }

        case 2:
        {
            int res = search_by_phone(addressBook);

            if (res >= 0)
            {
                for (int i = res;
                     i < addressBook->contactCount - 1;
                     i++)
                {
                    addressBook->contacts[i] =
                        addressBook->contacts[i + 1];
                }

                addressBook->contactCount--;

                printf("contact delete....\n");
            }

            break;
        }

        case 3:
        {
            int res = search_by_email(addressBook);

            if (res >= 0)
            {
                for (int i = res;
                     i < addressBook->contactCount - 1;
                     i++)
                {
                    addressBook->contacts[i] =
                        addressBook->contacts[i + 1];
                }

                addressBook->contactCount--;

                printf("contact delete....\n");
            }

            break;
        }

        case 4:
        {
            printf("Exiting...\n");
            return;
        }

        default:
        {
            printf("Invalid choice!\n");
            break;
        }
    }
}


int validate_name(char *str)// validateing the name
{
    for (int i = 0; str[i]; i++)
    {
        if (!((str[i] >= 'A' && str[i] <= 'Z') ||
              (str[i] >= 'a' && str[i] <= 'z') ||
              str[i] == ' ' ||
              str[i] == '.'))
        {
            printf("Invalid Name!\n");
            return 0;
        }
    }

    return 1;
}


int validate_phone(char *str1, AddressBook *addressBook)// validating the phone number 
{
    if (strlen(str1) != 10)
    {
        printf("Invalide phone numbers\n");
        return 0;
    }


    for (int i = 0; str1[i]; i++)
    {
        if (!(str1[i] >= '0' && str1[i] <= '9'))
        {
            printf("Invalide phone number\n");
            return 0;
        }
    }


    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(str1, addressBook->contacts[i].phone) == 0)
        {
            printf("Number already exist!\n");
            return 0;
        }
    }

    return 1;
}


int validate_email(char *str)// validating the email id
{
    int l = strlen(str);

    if (l < 5)
        return 0;

    int Count = 0;
    int Pos = -1;
    int dotPos = -1;


    for (int i = 0; i < l; i++)
    {
        if (str[i] == '@')
        {
            ++Count;
            Pos = i;
        }

        else if (str[i] == '.')
        {
            dotPos = i;

            if (i < l - 1)
            {
                if (str[i] == str[i + 1])
                    return 0;
            }
        }

        else if ((str[i] >= 'a' && str[i] <= 'z') ||
                 (str[i] >= '0' && str[i] <= '9') ||
                 str[i] == '-' ||
                 str[i] == '_' ||
                 str[i] == '+')
        {
            /* valid character */
        }

        else
        {
            return 0;
        }
    }


    if (Count == 0 || Count > 1)
        return 0;

    if (Pos == 0 || Pos == l - 1)
        return 0;

    if (dotPos <= Pos + 1 || dotPos == l - 1)
        return 0;


    return 1;
}


int *search_by_name(AddressBook *addressBook, int *count)// function for search by name
{
    char str[30];

    *count = 0;

    int *c = malloc(sizeof(int) * addressBook->contactCount);

    if (c == NULL && addressBook->contactCount > 0)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }


    printf("Enter the Name : ");
    scanf(" %[^\n]", str);


    if (validate_name(str) == 0)
    {
        return c;
    }


    int j = 1;


    for (int i = 0;
         i < addressBook->contactCount;
         i++)
    {
        if (strcmp(str, addressBook->contacts[i].name) == 0)
        {
            printf("%-2d. %-20s %-15s %-20s\n",
                   j,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);

            c[*count] = i;

            (*count)++;

            j++;
        }
    }


    if (*count == 0)
    {
        printf("No Records Found!\n");
    }


    return c;
}


int search_by_phone(AddressBook *addressBook) // function for search by phone
{
    char str[11];

    printf("Enter the phone number : ");
    scanf(" %[^\n]", str);


    int res = validate_phone_search(str);


    if (res == 1)
    {
        for (int i = 0;
             i < addressBook->contactCount;
             i++)
        {
            if (strcmp(str,
                       addressBook->contacts[i].phone) == 0)
            {
                printf("number found\n");

                printf("|  %-2d | %-20s | %-15s | %-20s |\n",
                       i + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);

                return i;
            }
        }

        printf("Number not found!\n");

        return -1;
    }

    return -1;
}


int search_by_email(AddressBook *addressBook) // function search by email
{
    char str[20];

    printf("Enter the Email id : ");
    scanf(" %[^\n]", str);


    int res = validate_email(str);


    if (res == 1)
    {
        for (int i = 0;
             i < addressBook->contactCount;
             i++)
        {
            if (strcmp(str,
                       addressBook->contacts[i].email) == 0)
            {
                printf("Email found\n");

                printf("|  %-2d | %-20s | %-15s | %-20s |\n",
                       i + 1,
                       addressBook->contacts[i].name,
                       addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);

                return i;
            }
        }

        printf("Email not found !\n");

        return -1;
    }

    printf("Invalid Email!\n");

    return -1;
}


void Bubble_sort(AddressBook *addressBook)// function for listing the contacts in oder useing Bubble sort
{
    for (int i = 0;
         i < addressBook->contactCount - 1;
         i++)
    {
        for (int j = 0;
             j < addressBook->contactCount - 1 - i;
             j++)
        {
            if (strcmp(addressBook->contacts[j].name,
                       addressBook->contacts[j + 1].name) > 0)
            {
                Contact tmp = addressBook->contacts[j];

                addressBook->contacts[j] =
                    addressBook->contacts[j + 1];

                addressBook->contacts[j + 1] = tmp;
            }
        }
    }
}


void edit(AddressBook *addressBook, int res)// function for Edit
{
    int choise;

    printf("1.Name\n2.Phone\n3.Email\n4.Exite\n");
    printf("Enter the choise : ");
    scanf("%d", &choise);

    switch (choise)
    {
        case 1:
        {
            edit_name(addressBook, &res);
            break;
        }

        case 2:
        {
            edit_phone(addressBook, res);
            break;
        }

        case 3:
        {
            edit_email(addressBook, res);
            break;
        }

        case 4:
        {
            printf("Exiting...\n");
            return;
        }

        default:
        {
            printf("Invalid option!\n");
            break;
        }
    }
}


void edit_phone(AddressBook *addressBook, int res)// function for edit phone
{
    char str[30];
    int r;

    do
    {
        printf("Enter the Phone Number to replace : ");
        scanf(" %[^\n]", str);

        r = validate_phone_search(str);

        if (r == 1)
        {
            for (int i = 0;
                 i < addressBook->contactCount;
                 i++)
            {
                if (i != res &&
                    strcmp(str,
                           addressBook->contacts[i].phone) == 0)
                {
                    printf("Number already exist!\n");
                    r = 0;
                    break;
                }
            }
        }

    } while (r == 0);


    strcpy(addressBook->contacts[res].phone, str);

    printf("Edited.....\n");
}


void edit_email(AddressBook *addressBook, int res)// function of edit Email
{
    char str[30];
    int r;

    do
    {
        printf("Enter the Email to replace : ");
        scanf(" %[^\n]", str);

        r = validate_email(str);

    } while (r == 0);


    strcpy(addressBook->contacts[res].email, str);

    printf("Edited.....\n");
}


int validate_phone_search(char *str)// fuction for  validate phone search
{
    if (strlen(str) != 10)
    {
        printf("Invalide phone numbers\n");
        return 0;
    }


    for (int i = 0; str[i]; i++)
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
        {
            printf("Invalide phone number\n");
            return 0;
        }
    }


    return 1;
}


void edit_name(AddressBook *addressBook, int *res)// function for Edit the name
{
    char name[20];
    int r;

    do
    {
        printf("Enter the Name to replace : ");
        scanf(" %[^\n]", name);

        r = validate_name(name);

    } while (r == 0);


    strcpy(addressBook->contacts[*res].name, name);

    printf("Edited.....\n");
}
