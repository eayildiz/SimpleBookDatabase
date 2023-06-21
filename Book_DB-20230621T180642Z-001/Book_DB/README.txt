									Book Database Calculator.
This program organize your book database up to 2000 books. It sort given database based on author's last name and store inside of program. It does not affect original file unless you commanded that.
This program takes an argument as file name which store database of book.
The file has to be in given format:
The Book Title,AuthorFirstName AuthorLastName,Year,Price
The Book Title,AuthorFirstName AuthorLastName,Year,Price
.
.
.
Program does not have defined behaviour for wrong format of file and it does not protect user.
Program does not protect for actions which are not undefined! Please only give valid inputs to program.
If the argument is not valid, program expect you to enter a valid file name. If you enter "-9 kill" as file name then program ends. So, if your file name is "-9 kill" and if you did not give it at first, you cannot give it anymore.
Commands of the program.
1) Add Book:		You can add book to database. It will placed to database according to order of database. You need to enter title, author's first name with no spaces, author's last name with no 			spaces, publishing year and price of book.
2) Delete Book:	You can delete a book from database. It will not affect the order of database. You need to give title of book. It cannot be reversed.
3) Search by Author:	You can search all books off an author. It will display all books of the author.
4) Search by Title: 	You can search a book by it's title. It will display the book.
5) PrintAll:		Display all database in an order. It does not have particular output format so it might be confusing.
6) Save end Exit:	Save the changes of database to the file which is given by outwriting on it. This process cannot be reversed. It will change your original file. Having a back up file of original 				file is suggested. If you want to end program but do not change the original file, you can press <ctrl + c> buttons for linux or <ctrl + z> for windows. Do not forget that it 				will delete other changes you did during this program.

Author: Emir Alper Yildiz
Contact info: emiralper.yildiz[at]etu.edu.tr	|	emiralpery[at]gmail.com

Unfortunalety I could not implement quick sort and better search algorithms to code. Since I had a little time I prefer easier algorithms to implement. This function body prototypes which cannot be implemented stay in a text file in my personal computer. As a result program might work slower for bigger databases. Except that program compiled withouth a problem and works as intented for every function. You must first compile header file than actual code.
