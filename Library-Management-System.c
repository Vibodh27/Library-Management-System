#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to define a Book
struct Book {
	int id;
	char title[100];
	char author[100];
};

// Function to add a book
void addBook() {
	FILE *file = fopen("library.dat", "ab");
	struct Book b;
	printf("\nEnter Book ID: ");
	scanf("%d", &b.id);
	getchar(); // To clear newline
	printf("Enter Book Title: ");
	fgets(b.title, 100, stdin);
	b.title[strcspn(b.title, "\n")] = '\0'; // Remove newline
	printf("Enter Book Author: ");
	fgets(b.author, 100, stdin);
	b.author[strcspn(b.author, "\n")] = '\0';
	fwrite(&b, sizeof(b), 1, file);
	fclose(file);
	printf("\nBook added successfully!\n");
}

// Function to display all books
void displayBooks() {
	FILE *file = fopen("library.dat", "rb");
	struct Book b;
	int flag=0;
	if (file==NULL)
	{
	    printf("there is no book in the library. please add atleast one book to display it.");
	    return;
	}
	printf("\n--- Library Books ---\n");
	while (fread(&b, sizeof(b), 1, file)) {
		printf("\nID: %d\nTitle: %s\nAuthor: %s\n", b.id, b.title, b.author);
		flag=1;
	}
	fclose(file);
	
}

// Function to search for a book by ID
void searchBook() {
	FILE *file = fopen("library.dat", "rb");
	struct Book b;
	int id, found = 0;
	printf("\nEnter Book ID to search: ");
	scanf("%d", &id);
	while (fread(&b, sizeof(b), 1, file)) {
		if (b.id == id) {
			printf("\nBook Found:\nID: %d\nTitle: %s\nAuthor: %s\n", b.id, b.title, b.author);
			found = 1;
			break;
		}
	}
	fclose(file);
	if (!found) {
		printf("\nBook not found.\n");
	}
}

// Function to delete a book
void deleteBook() {
	FILE *file = fopen("library.dat", "rb");
	FILE *temp = fopen("temp.dat", "wb");
	struct Book b;
	int id, found = 0;
	printf("\nEnter Book ID to delete: ");
	scanf("%d", &id);
	while (fread(&b, sizeof(b), 1, file)) {
		if (b.id != id) {
			fwrite(&b, sizeof(b), 1, temp);
		} else {
			found = 1;
		}
	}
	fclose(file);
	fclose(temp);
	remove("library.dat");
	rename("temp.dat", "library.dat");
	if (found) {
		printf("\nBook deleted successfully!\n");
	} else {
		printf("\nBook not found.\nCheck whether the book is there in library or not.\nPlease provide the correct book ID");
	}
}

// Main Menu
int main() {
	int choice;
	while (1) {
		printf("\n====== Library Management System ======\n");
		printf("1. Add Book\n2. Display All Books\n3. Search Book\n4. Delete Book\n5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		printf("Note:the choices must be 1,2,3,4,5 nothing except that");
		switch (choice) {
		case 1:
			addBook();
			break;
		case 2:
			displayBooks();
			break;
		case 3:
			searchBook();
			break;
		case 4:
			deleteBook();
			break;
		case 5:
			exit(0);
		default:
			printf("\nInvalid choice. Try again.\n");
		}
	}
	return 0;
}
