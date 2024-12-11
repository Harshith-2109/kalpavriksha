// added to branch
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "users.txt"

typedef struct {
    int id;
    char name[50];
    int age;
} Person;


void createRecord();
void readRecords();
void updateRecord();
void deleteRecord();
int findRecordById(FILE *file, int id, Person *p);

int main() {
    int choice;

    while (1) {
        printf("\nCRUD Operations Menu:\n");
        printf("1. Create Record\n");
        printf("2. Read Records\n");
        printf("3. Update Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createRecord(); break;
            case 2: readRecords(); break;
            case 3: updateRecord(); break;
            case 4: deleteRecord(); break;
            case 5: exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

int is_id_unique(int id) {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        
        return 1;
    }

    Person record;
    while (fscanf(file, "%d %[^\n] %d", &record.id, record.name, &record.age) != EOF) {
        if (record.id == id) {
            fclose(file);
            return 0; 
        }
    }

    fclose(file);
    return 1; 
}


void createRecord() {
    FILE *file = fopen(FILE_NAME, "r+");
    if (!file) {
        
        file = fopen(FILE_NAME, "w");
        if (!file) {
            perror("Error creating file");
            return;
        }
    }

    Person p;
    int isUnique;

    do {
        isUnique = 1; 
        printf("Enter ID: ");
        scanf("%d", &p.id);

        
        rewind(file);
        Person temp;
        while (fscanf(file, "%d,%49[^,],%d\n", &temp.id, temp.name, &temp.age) == 3) {
            if (temp.id == p.id) {
                isUnique = 0;
                printf("ID already exists. Please enter a unique ID.\n");
                break;
            }
        }
    } while (!isUnique);

    printf("Enter Name: ");
    scanf("%s", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);

    
    fprintf(file, "%d,%s,%d\n", p.id, p.name, p.age);
    fclose(file);
    printf("Record added successfully.\n");
}


void readRecords() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    Person p;
    printf("\nID\tName\tAge\n");
    while (fscanf(file, "%d,%49[^,],%d\n", &p.id, p.name, &p.age) == 3) {
        printf("%d\t%s\t%d\n", p.id, p.name, p.age);
    }

    fclose(file);
}

void updateRecord() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror("Error opening temp file");
        fclose(file);
        return;
    }

    int id, found = 0;
    printf("Enter ID to update: ");
    scanf("%d", &id);

    Person p, updatedPerson;
    printf("Enter new Name: ");
    scanf("%s", updatedPerson.name);
    printf("Enter new Age: ");
    scanf("%d", &updatedPerson.age);

    while (fscanf(file, "%d,%49[^,],%d\n", &p.id, p.name, &p.age) == 3) {
        if (p.id == id) {
            found = 1;
            fprintf(tempFile, "%d,%s,%d\n", id, updatedPerson.name, updatedPerson.age);
        } else {
            fprintf(tempFile, "%d,%s,%d\n", p.id, p.name, p.age);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILE_NAME);
        rename("temp.txt", FILE_NAME);
        printf("Record updated successfully.\n");
    } else {
        remove("temp.txt");
        printf("Record not found.\n");
    }
}

void deleteRecord() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (!tempFile) {
        perror("Error opening temp file");
        fclose(file);
        return;
    }

    int id, found = 0;
    printf("Enter ID to delete: ");
    scanf("%d", &id);

    Person p;
    while (fscanf(file, "%d,%49[^,],%d\n", &p.id, p.name, &p.age) == 3) {
        if (p.id == id) {
            found = 1;
        } else {
            fprintf(tempFile, "%d,%s,%d\n", p.id, p.name, p.age);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found) {
        remove(FILE_NAME);
        rename("temp.txt", FILE_NAME);
        printf("Record deleted successfully.\n");
    } else {
        remove("temp.txt");
        printf("Record not found.\n");
    }
}
