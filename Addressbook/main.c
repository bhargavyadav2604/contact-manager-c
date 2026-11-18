/*AddressBook 
Bhargav A
stating date 31-7-2026
ending date 10-8-2026
Project Description--->
The Address Book Management System is a menu-driven application developed 
using C programming to efficiently manage contact information. 
The system allows users to add, search, edit, delete, and display contacts containing 
details such as name, phone number, and email address. The project uses important C programming 
concepts such as structures, arrays, functions, pointers, and file handling to store and manage data. 
It provides a simple command-line interface and demonstrates the practical implementation of C programming 
concepts in a real-world contact management application.*/
#include <stdio.h>
#include "contact.h"
#include "file.h"

int main()
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do
    {
        //printing list of address book 
        printf("\n\n***************************************\n");
        printf("|           ADDRESS BOOK MENU         |\n");
        printf("---------------------------------------\n");
        printf("|   1   |   %-25s |\n", "CREATE CONTACT");
        printf("|   2   |   %-25s |\n", "SEARCH CONTACT");
        printf("|   3   |   %-25s |\n", "EDIT CONTACT");
        printf("|   4   |   %-25s |\n", "DELETE CONTACT");
        printf("|   5   |   %-25s |\n", "LIST ALL CONTACTS");
        printf("|   6   |   %-25s |\n", "SAVE AND EXIT");
        printf("|   7   |   %-25s |\n", "EXIT");
        printf("---------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
            createContact(&addressBook);//for creat new contact
            break;
        case 2:
            searchContact(&addressBook);//for search Contact
            break;
        case 3:
            editContact(&addressBook);//for edit Contact
            break;
        case 4:
            deleteContact(&addressBook);// for delete Contact
            break;
        case 5:
            listContacts(&addressBook);// for list Contacts
            break;
        case 6:
            printf("Saving and Exiting...\n");
            saveContactsToFile(&addressBook);// for save Contacts To File
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
