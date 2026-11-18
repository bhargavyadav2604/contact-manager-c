#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void initialize(AddressBook *addressBook);
void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);

int validate_name(char *str);
int validate_phone(char *str1, AddressBook *addressBook);
int validate_email(char *str);
void Bubble_sort(AddressBook *addressBook);

int *search_by_name(AddressBook *addressBook, int *count);
int search_by_phone(AddressBook *addressBook);
int search_by_email(AddressBook *addressBook);

int validate_phone_search(char *str);

void edit(AddressBook *addressBook, int res);
void edit_name(AddressBook *addressBook, int *res);
void edit_phone(AddressBook *addressBook, int res);
void edit_email(AddressBook *addressBook, int res);

#endif