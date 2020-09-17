#include "moviefactory.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
//
// Preconditions:   none
//
// Postconditions:  none
//
MovieFactory::MovieFactory() {
   
}

//------------------------------- destructor ----------------------------------
// Description:     intentionally left empty
//
// Preconditions:   none
//
// Postconditions:  none
//
MovieFactory::~MovieFactory() {
   
}

//------------------------------ createMovie ----------------------------------
// Description:     Creates a Movie object
//                  Used by the Store class to create a new Movie type
//
// Preconditions:   string data is information about a movie and is correctly
//                  formatted
//                  Movie*& newMovie is null
//
// Postconditions:  returns a pointer to a Movie object
//                  (i.e. Classic, Comedy, Drama)
//
bool MovieFactory::createMovie(Movie*& newMovie, string movieData) {
   char movieType;
   movieType = movieData.at(0);            // 'C', 'F', or 'D'
   
   switch(movieType) {                     // find movie type
      case 'F':
         newMovie = new Comedy;
         break;
      case 'C':
         newMovie = new Classic;
         break;
      case 'D':
         newMovie = new Drama;
         break;
      default:
         cout << "ERROR: Movie Not Added To Inventory: ";
         cout << "Invalid movie type '" << movieType << "'" << endl;
         newMovie = nullptr;
         return false;
   }
   
   // If object was successfully created, set it's data
   // return false if there is invalid data
   bool success = newMovie->setData(movieData);
   if(!success) return false;
   
   return true;
}
