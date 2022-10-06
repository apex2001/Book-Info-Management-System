#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <sstream>

using namespace std;

struct Book {
  Book(const string& input);
  string genre;
  string title;
  string author;
  string year;
  string const toString() { return "{genre:" + genre + ",title:" + title + ",author:" + author + ",year:" + year + "}"; }
};

class InvalidBookException {
  private:
    string msg;
  public:
    InvalidBookException(string _msg) : msg(_msg) {}
    string what() { return msg; }
};

Book::Book(const string& input) {
  // check if all 4 categories are in the string
  if (input.find("genre") == string::npos || input.find("title") == string::npos || input.find("author") == string::npos || input.find("year") == string::npos)
    throw InvalidBookException("missing category");
  
  // check categories are in order
  if (!(input.find("genre") < input.find("title") && input.find("title") < input.find("author") && input.find("author") < input.find("year")))
    throw InvalidBookException("categories not in order");

  stringstream categoriesStream(input);
  string currentCategory;

  // extract genre (genre:fantasy)
  getline(categoriesStream, currentCategory, ',');
  genre = currentCategory.substr(6);

  // extract title (title:Harry.Potter)
  getline(categoriesStream, currentCategory, ',');
  title = currentCategory.substr(6);

  // extract author (author:J.K.Rowling)
  getline(categoriesStream, currentCategory, ',');
  author = currentCategory.substr(7);

  // extract year (year:1997)
  getline(categoriesStream, currentCategory, ',');
  year = currentCategory.substr(5);
}

#endif