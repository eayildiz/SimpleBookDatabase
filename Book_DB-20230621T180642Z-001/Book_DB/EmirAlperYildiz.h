#define DATABASE_SIZE 2000
#define TITLE_SIZE 200
#define NAME_SIZE 20
typedef struct{
    char first_name[NAME_SIZE];
    char last_name[NAME_SIZE];
}Author;
typedef struct{
    char title[TITLE_SIZE];
    Author author;
    int year;
    double price;
}Book;
typedef struct{
    int number_of_books;
    Book books[DATABASE_SIZE];
}BookDatabase;
void load(char *file_name, BookDatabase *book_database);
int compare_books(Book book1, Book book2);
int length_of_string(const char const *ltrl);
void sort_database(Book books[], int start_index, int end_index);
void printAll(BookDatabase *book_database);
void searchByTitle(BookDatabase *book_database, char *title);
void searchByAuthor(BookDatabase *book_database, Author an_author);
void saveAndExit(BookDatabase *book_database, char *file_name);
void manual();
void addBook(BookDatabase *book_database, Book input_book);
void print_a_book(Book a_book);
void removeBook(BookDatabase *book_database, char *title);