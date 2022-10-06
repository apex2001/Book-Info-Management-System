#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "ArgumentManager.h"
#include "Book.h"

using namespace std;

string extractAndCleanInput(istream& input);
vector<Book> parseBooks(const string& input);
vector<Book> findBooks(istream& command, const vector<Book>& bookShelf);
template<typename T> bool vectorContains(vector<T> vec, T value);

int main(int argc, char* argv[]) {
  
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ifstream command(am.get("command"));
  ofstream output(am.get("output"));
  /*chmod
  ifstream input("input11.txt");
  ifstream command("command11.txt");
  ofstream output("output11.txt");*/
  // parse input and initialize book vector
  string cleanedInput = extractAndCleanInput(input);
  //cout << cleanedInput << endl;
  vector<Book> bookShelf = parseBooks(cleanedInput);

  // read commands and find selected books
  vector<Book> selectedBooks = findBooks(command, bookShelf);
  
  // output selected books
  for (Book book : selectedBooks) {
    output << book.toString() << endl;
  }
}

string extractAndCleanInput(istream& input) {
  string cleanedInput = "";
  char rawChar;

  while (input >> rawChar) {
    //if (rawChar != ' ' && rawChar != '\n') {
      cleanedInput.push_back(rawChar);
    //}
  }

  return cleanedInput;
}

vector<Book> parseBooks(const string& input) {
  vector<Book> bookShelf;

  int indexOfLastBook = input.find('{');
  while (indexOfLastBook != string::npos) {
    int indexOfLastBookEnd = input.find('}', indexOfLastBook + 1);
    
    try {
      int lengthOfBookInput = (indexOfLastBookEnd - indexOfLastBook - 1);
      Book newBook(input.substr(indexOfLastBook + 1, lengthOfBookInput));
      bookShelf.push_back(newBook);
    }
    catch(InvalidBookException ex) {}
    
    indexOfLastBook = input.find('{', indexOfLastBook + 1);
  }

  return bookShelf;
}

vector<Book> findBooks(istream& command, const vector<Book>& bookShelf) {
  vector<Book> matchedBooks;
  vector<string> genre, title, author, year;
  
  // parsing the search criteria
  string line;
  while (getline(command, line)) {
    string category = line.substr(0, line.find(':'));
    string content = line.substr(line.find(':') + 1);

    if (category == "genre")
      genre.push_back(content);
    else if (category == "title")
      title.push_back(content);
    else if (category == "author")
      author.push_back(content);
    else if (category == "year")
      year.push_back(content);
  }

  // query the bookshelf using the criteria
  for (Book book : bookShelf) {
    if (genre.size() > 0) {
      // make sure the book is one of the genres in the genre vector
      if (!vectorContains(genre, book.genre))
        continue;
        // if not, do not add this book to matchedBooks
    }
    if (title.size() > 0) {
      if (!vectorContains(title, book.title))
        continue;
    }
    if (author.size() > 0) {
      if (!vectorContains(author, book.author))
        continue;
    }
    if (year.size() > 0) {
      if (!vectorContains(year, book.year))
        continue;
    }
    
    matchedBooks.push_back(book);
  }

  return matchedBooks;
}

template<typename T>
bool vectorContains(vector<T> vec, T value) {
  // return true if value in vec, else return false
  for (T element : vec) {
    if (element == value) {
      return true;
    }
  }
  return false;  
}

/*
x extract and clean the input (spaces and new lines)
x parse strings into Books and add to Shelf
x extract commands
x query Shelf with commands
x output result of query
*/