// --------------------------------- movie.h ----------------------------------

// CSS 343
// Created: August 5th, 2020
// Last Modified: August 21st, 2020

// ----------------------------------------------------------------------------

// Movie Class: Movie represents a general type of movie based on specific
//              genres of movies (Comedy, Drama, Classics) inherit from.

// ----------------------------------------------------------------------------

// Notes on specifications, special algorithms, and assumptions.

// - Movie is an abstract class
// - Movie is a base class for subclasses of genres
// - For genre of Movies: 'F' = comedy; 'D' = drama; 'C' = classic

//

#ifndef MOVIE_H
#define MOVIE_H

#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

class Movie {
public:
   Movie();                      // default constructor
   Movie(char);                  // constructor
   virtual ~Movie();             // destructor
   Movie(const Movie&);          // copy constructor
   
   // setter functions
   virtual bool setData(string);    // set data members
   bool addStock();                 // add stock of a movie
   bool removeStock();              // change stock of a movie
   
   // getter functions
   char getType() const;
   string getTitle() const;
   string getDirector() const;
   int getYear() const;
   int getStock() const;
   
   // setter functions
   bool setTitle(string);
   bool setYear(int);
   bool setDirector(string);
   
   // overloaded operators
   virtual Movie& operator=(const Movie&);
   virtual bool operator<(const Movie&) const = 0;
   virtual bool operator>(const Movie&) const = 0;
   virtual bool operator==(const Movie&) const = 0;
   virtual bool operator!=(const Movie&) const = 0;
   
   virtual void display() const;
   
protected:
   string director = "";   // director of the movie
   string title = "";      // title of the movie
   
   char type = '\0';       // genre of movie
   
   int stock = 0;          // current stock of movie type
   int year = 0;           // year movie was released
   
   void copy(const Movie&);
};
#endif
