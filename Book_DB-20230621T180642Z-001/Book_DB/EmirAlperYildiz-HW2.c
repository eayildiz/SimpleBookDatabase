/*
 *Emir Alper Yildiz, 201101004, Bil214 Project
 *emiralpery[at]gmail.com   | emiralper.yildiz[at]etu.edu.tr
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "EmirAlperYildiz.h"

int main(int argc, char *argv[]){
    if(2 != argc){
        printf("Only one argument for this program! Program will be closed!\n");
        return 1;
    }
    BookDatabase book_database;
    Book buffer_book;
    int order_input;
    int mode = 1;
    load(argv[1], &book_database);
    sort_database(book_database.books, 0, book_database.number_of_books);
    if(strcmp(argv[1], "-9 kill") == 0){
    mode = 0;
    }

    while(mode){
        printf("1 Add Book\n2 Delete Book\n3 Search by Author\n4 Search by Title\n5 Print All\n6 Save and Exit\n");
        scanf("%d", &order_input);
        getchar();
        switch(order_input){
            case 1:
                printf("Please enter title of book:\n");
                fgets(buffer_book.title, 200, stdin);
                sscanf(buffer_book.title, "%200[^\n]", buffer_book.title);
                printf("Please enter name of author\'s first name with no spaces:\n");
                fgets(buffer_book.author.first_name, 20, stdin);
                sscanf(buffer_book.author.first_name, "%20[^\n]", buffer_book.author.first_name);
                printf("Please enter name of author\'s last name with no spaces:\n");
                fgets(buffer_book.author.last_name, 20, stdin);
                sscanf(buffer_book.author.last_name, "%20[^\n]", buffer_book.author.last_name);
                printf("Please enter publishing year of book:\n");
                scanf("%d", &buffer_book.year);
                getchar();
                printf("Please enter price of book:\n");
                scanf("%lf", &buffer_book.price);
                getchar();
                addBook(&book_database, buffer_book);
                break;
            case 2:
                printf("Please enter the title of book you wanted to be removed:\n");
                fgets(buffer_book.title, 200, stdin);
                sscanf(buffer_book.title, "%200[^\n]", buffer_book.title);
                removeBook(&book_database, buffer_book.title);
                break;
            case 3:
                printf("Please enter the first name and press enter\n");
                fgets(buffer_book.author.first_name, 20, stdin);
                sscanf(buffer_book.author.first_name, "%20[^\n]", buffer_book.author.first_name);
                printf("Please enter the last name and press enter\n");
                fgets(buffer_book.author.last_name, 20, stdin);
                sscanf(buffer_book.author.last_name, "%20[^\n]", buffer_book.author.last_name);
                searchByAuthor(&book_database, buffer_book.author);
                break;
            case 4:
                printf("Please enter a title and press <enter>\n");
                scanf("%200[^\n]", buffer_book.title);
                searchByTitle(&book_database, buffer_book.title);
                break;
            case 5:
                printAll(&book_database);
                break;
            case 6:
                saveAndExit(&book_database, argv[1]);
                mode = 0;
                break;
            default:
                printf("Invalid comand! Try again.\n");
                manual();
                break;
        }
    }
    printf("Program ends.\n");
    return 0;
}

void load(char *file_name, BookDatabase *book_database){
    FILE *file_pointer;
    file_pointer = fopen(file_name, "r");
    while(file_pointer == NULL){
        printf("File open error! Please enter a valid file and press enter.\n");
        scanf("%s\n", file_name);
        if(strcmp(file_name, "-9 kill") == 0){
            return;
        }
        file_pointer = fopen(file_name, "r");
    }
    int book_counter = 0;
    char input_line[260];
    char *temp_ptr_for_conversion;
    while((fgets(input_line, 260, file_pointer)) != NULL){
        strcpy(book_database->books[book_counter].title, strtok(input_line, ","));
        strcpy(book_database->books[book_counter].author.first_name, strtok(NULL, " "));
        strcpy(book_database->books[book_counter].author.last_name, strtok(NULL, ","));
        book_database->books[book_counter].year = atoi(strtok(NULL, ","));
        book_database->books[book_counter].price = strtod(strtok(NULL, "\n"), &temp_ptr_for_conversion);
        book_counter++;
    }
    fclose(file_pointer);
    book_database->number_of_books = book_counter;
}
/*This functions compare books by their authors last name alphabetically. If they have same alphabetical order but one of them is shorter, short one will be come before.
 *Before comparing letters, it will be turned to uppercase.
 *For example if we compare evans and evanson, since evans is first arg function will be return 1.
 *return 0, 1 or 2
 *0 if they are equal
 *1 if first arg is smaller which means it comes before in alphabet
 *2 if second arg is smaller.
*/
int compare_books(Book book1, Book book2){
    int min_length;
    if(length_of_string(book1.author.last_name) < length_of_string(book2.author.last_name)){
        min_length = length_of_string(book1.author.last_name);
    }
    else{
        min_length = length_of_string(book2.author.last_name);
    }
    for(int index = 0; index < min_length; index++){
        if(toupper(book1.author.last_name[index]) < toupper(book2.author.last_name[index])){
            return 1;
        }
        else if(toupper(book1.author.last_name[index]) > toupper(book2.author.last_name[index])){
            return 2;
        }
    }
    if(min_length < length_of_string(book1.author.last_name)){
        return 2;
    }
    else if(min_length > length_of_string(book2.author.last_name)){
        return 1;
    }
    return 0;
}
int length_of_string(const char const *ltrl){
    int length = 0;
    while (*(ltrl + length) != '\0') {
        length++;
    }
    return length;
}
void sort_database(Book books[], int start_index, int end_index){
    Book temp_book;
    if(start_index == end_index){return;}
    for(int index = start_index; index < end_index - 1; index++){
        if(compare_books(books[index], books[index + 1]) == 2){
            temp_book = books[index];
            books[index] = books[index + 1];
            books[index + 1] = temp_book;
        }
    }
    sort_database(books, start_index, end_index - 1);
}
void printAll(BookDatabase *book_database){
    for(int index = 0; index < book_database->number_of_books; index++){
        print_a_book(book_database->books[index]);
    }
}
void searchByTitle(BookDatabase *book_database, char *title){
    int index;
    for(index = 0; index < book_database->number_of_books; index++){
        if(strcmp(title, book_database->books[index].title) == 0){
            print_a_book(book_database->books[index]);
            return;
        }
    }
    printf("The book with a given title cannot be found. Please make sure you entered title correct!\n");
}
void searchByAuthor(BookDatabase *book_database, Author an_author){
    int index;
    int found = 0;
    for(index = 0; (index < book_database->number_of_books) && (found == 0); index++){
        while(strcmp(an_author.last_name, book_database->books[index].author.last_name) == 0){
            if(strcmp(an_author.first_name, book_database->books[index].author.first_name) == 0){
                found = 1;
                print_a_book(book_database->books[index]);
            }
            index++;
        }
    }
    if(found == 0){
        printf("The author with a given name cannnot be found. Please make sure you entered author\'s name correctly!\n");
    }
}
void saveAndExit(BookDatabase *book_database, char *file_name){
    FILE *file_pointer;
    file_pointer = fopen(file_name, "w");
    if(file_pointer == NULL){
        printf("File open error! Could not updated file. Please enter a valid file.\n");
        return;
    }
    for(int index = 0; index < book_database->number_of_books; index++){
    fprintf(file_pointer, "%s, %s %s, %d, %.2f\n", book_database->books[index].title, book_database->books[index].author.first_name, book_database->books[index].author.last_name,
    book_database->books[index].year, book_database->books[index].price);
    }
    printf("Database updated successfuly.\n");
}
void manual(){
    printf("\t\t\t\t\t\t\tBook Database Calculator.\nThis program organize your book database. It sort given database based on author\'s "
    "last name and store inside of program. It does not affect original file unless you commanded that.\nThis program takes an argument as "
    "file name which store database of book.\nThe file has to be in given format:\nThe Book Title,AuthorFirstName AuthorLastName,Year,"
    "Price\nThe Book Title,AuthorFirstName AuthorLastName,Year,Price\n.\n.\n.\nProgram does not have defined behaviour for wrong format of "
    "file and it does not protect user.\nIf the argument is not valid, program expect you to enter a valid file name. If you enter \"-9 kill"
    "\"as file name then program ends. So, if your file name is \"-9 kill\" and if you did not give it at first, you cannot give it "
    "anymore.\n"
    "Commands of the program.\n"
    "1) Add Book:\t\tYou can add book to database. It will placed to database according to order of database. You need to enter title, "
    "author\'s first name with no \t\tspaces, author\'s last name with no spaces, publishing year and price of the book.\n"
    "2) Delete Book:\tYou can delete a book from database. It will not affect the order of database. You need to give title of book. It "
    "cannot be reversed.\n"
    "3) Search by Author:\tYou can search all books of an author. It will display all books of the author.\n"
    "4) Search by Title: \tYou can search a book by it\'s title. It will display the book. It might be slower than searching by author.\n"
    "5) PrintAll:\t\tDisplay all database in an order. It does not have particular output format so it might be confusing.\n"
    "6) Save end Exit:\tSave the changes of database to the file which is given by outwriting on it. This process cannot be reversed. It will" 
    "change your original file. Having a back up file of original \t\t\t\tfile is suggested. If you want to end program but do not change the"
    " original file, you can press <ctrl + c> buttons for linux or <ctrl + z> for windows. Do not forget that it \t\t\t\twill delete other "
    "changes you did during this program.\n");
}
void addBook(BookDatabase *book_database, Book input_book){
    if(book_database->number_of_books == DATABASE_SIZE){
        printf("Cannot store more books!\n");
        return;
    }
    int index;
    for(index = 0; index < book_database->number_of_books; index++){
        if(strcmp(input_book.title, book_database->books[index].title) == 0){
            printf("This book is already exists!\n");
            return;
        }
        if((compare_books(book_database->books[index], input_book)) == 1 && (compare_books(
        input_book, book_database->books[index + 1]) == 1)){
            book_database->number_of_books++;
            Book temp_book1;
            Book temp_book2 = book_database->books[index];
            book_database->books[index] = input_book;
            for(; index < book_database->number_of_books; index++){
                temp_book1 = book_database->books[index];
                book_database->books[index] = temp_book2;
                temp_book2 = temp_book1;
            }
            return;
        }
    }
    printf("Program worked unexpectedly!\n Your data are in danger!\nExit with terminal exit command!\n");
}
void print_a_book(Book a_book){
    printf("%s, %s %s, %d, %.2f\n", a_book.title, a_book.author.first_name, a_book.author.last_name, a_book.year, a_book.price);
}
void removeBook(BookDatabase *book_database, char *title){
    int index;
    int index_of_string;
    int found = 0;
    for(index = 0; index < book_database->number_of_books; index++){
        if(strcmp(title, book_database->books[index].title) == 0){
            found = 1;
            break;
        }
    }
    if(found){
        while(index < (book_database->number_of_books - 1)){
            book_database->books[index] = book_database->books[index + 1];
            index++;
        }
        book_database->books[index].title[0] = '\0';
        book_database->books[index].author.first_name[0] = '\0';
        book_database->books[index].author.last_name[0] = '\0';
        book_database->books[index].year = 0;
        book_database->books[index].price = 0.0;
        book_database->number_of_books--;
        return;
    }
    printf("The book with a given title cannot be found. Please make sure you entered title correct!\n");
}
