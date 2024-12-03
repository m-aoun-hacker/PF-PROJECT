#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CONTACTS 100
#define MAX_NAME_LENGTH 50
#define MAX_PHONE_LENGTH 20
#define FILE_NAME "phonebook.txt"

// Structure to store a contact
typedef struct {
    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
} Contact;

// Global variables
Contact phoneBook[MAX_CONTACTS];
int size = 0;

// Function prototypes
void addContact();
void displayContacts();
void searchContact();
void deleteContact();
void clearScreen();
void updateContact();
void loadFromFile();
void backupToFile();

int main() {
    int choice;

    // Load contacts from the file on startup
    loadFromFile();

    do {
        printf("\nPhone Book Menu:\n");
        printf("1. Add Contact\n");
        printf("2. View All Contacts\n");
        printf("3. Search Contact by Name\n");
        printf("4. Delete Contact by Name\n");
        printf("5. Clear Screen\n");
        printf("6. Update Contact\n");
        printf("7. Backup Phone Book\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                displayContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                clearScreen();
                break;
            case 6:
                updateContact();
                break;
            case 7:
                backupToFile();
                break;
            case 8:
                printf("Exiting Phone Book. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    return 0;
}

// Function to add a contact
void addContact() {
    if (size >= MAX_CONTACTS) {
        printf("Phone book is full. Cannot add more contacts.\n");
        return;
    }

    printf("Enter name: ");
    fgets(phoneBook[size].name, MAX_NAME_LENGTH, stdin);
    phoneBook[size].name[strcspn(phoneBook[size].name, "\n")] = '\0'; // Remove newline

    printf("Enter phone number: ");
    fgets(phoneBook[size].phone, MAX_PHONE_LENGTH, stdin);
    phoneBook[size].phone[strcspn(phoneBook[size].phone, "\n")] = '\0'; // Remove newline
 // Check for invalid phone number length
     size++;
    printf("Contact added successfully!\n");
}

// Function to display all contacts
void displayContacts() {
    if (size == 0) {
        printf("No contacts in phone book.\n");
        return;
    }

    printf("\nPhone Book Contacts:\n");
    for (int i = 0; i < size; i++) {
        printf("%d. %s - %s\n", i + 1, phoneBook[i].name, phoneBook[i].phone);
    }
}

// Function to search for a contact by name
void searchContact() {
    char searchName[MAX_NAME_LENGTH];
    printf("Enter the name to search: ");
    fgets(searchName, MAX_NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // Remove newline

    for (int i = 0; i < size; i++) {
        if (strcmp(phoneBook[i].name, searchName) == 0) {
            printf("Contact found: %s - %s\n", phoneBook[i].name, phoneBook[i].phone);
            return;
        }
    }
    printf("Contact not found.\n");
}

// Function to delete a contact by name
void deleteContact() {
    char deleteName[MAX_NAME_LENGTH];
    printf("Enter the name to delete: ");
    fgets(deleteName, MAX_NAME_LENGTH, stdin);
    deleteName[strcspn(deleteName, "\n")] = '\0'; // Remove newline

    for (int i = 0; i < size; i++) {
        if (strcmp(phoneBook[i].name, deleteName) == 0) {
            for (int j = i; j < size - 1; j++) {
                phoneBook[j] = phoneBook[j + 1]; // Shift contacts left
            }
            size--;
            printf("Contact deleted successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}


// Function to clear the screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to update a contact
void updateContact() {
    char searchName[MAX_NAME_LENGTH];
    printf("Enter the name of the contact to update: ");
    fgets(searchName, MAX_NAME_LENGTH, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // Remove newline

    for (int i = 0; i < size; i++) {
        if (strcmp(phoneBook[i].name, searchName) == 0) {
            printf("Enter new name (leave blank to keep current): ");
            char newName[MAX_NAME_LENGTH];
            fgets(newName, MAX_NAME_LENGTH, stdin);
            if (strcmp(newName, "\n") != 0) { // If not just a newline
                newName[strcspn(newName, "\n")] = '\0';
                strcpy(phoneBook[i].name, newName);
            }

            printf("Enter new phone number (leave blank to keep current): ");
            char newPhone[MAX_PHONE_LENGTH];
            fgets(newPhone, MAX_PHONE_LENGTH, stdin);
            if (strcmp(newPhone, "\n") != 0) { // If not just a newline
                newPhone[strcspn(newPhone, "\n")] = '\0';
                strcpy(phoneBook[i].phone, newPhone);
            }

            printf("Contact updated successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}



// Function to create a backup of the contacts
void backupToFile() {
    FILE *file = fopen("backup_phonebook.txt", "w");
    if (file == NULL) {
        printf("Error: Unable to create backup file.\n");
        return;
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%s,%s\n", phoneBook[i].name, phoneBook[i].phone);
    }
    fclose(file);
    printf("Backup created successfully in 'backup_phonebook.txt'.\n");
}

// Function to load contacts from a file
void loadFromFile() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        printf("No existing file found. Starting fresh.\n");
        return;
    }

    size = 0; // Reset size before loading
    while (fscanf(file, "%49[^,],%14[^\n]\n", phoneBook[size].name, phoneBook[size].phone) == 2) {
        size++;
        if (size >= MAX_CONTACTS) {
            printf("Warning: Maximum contacts loaded. Some entries may be skipped.\n");
            break;
        }
    }
    fclose(file);
    printf("Contacts loaded successfully from '%s'.\n", FILE_NAME);
}
