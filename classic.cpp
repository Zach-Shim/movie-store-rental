#include "classic.h"

//--------------------------- default constructor -----------------------------
// Description:     intentionally left empty
//
// Preconditions:   none
//
// Postconditions:  none
//
Classic::Classic() {}

//------------------------------- destructor ----------------------------------
// Description:     intentionally left empty
//
// Preconditions:   none
//
// Postconditions:  none
//
Classic::~Classic(){}

//----------------------------- copy constructor ------------------------------
// Description:     deep copies a Classic into *this
//
// Preconditions:   Classic& right is a Classic with initialized data
//
// Postconditions:  *this is a copy of Classic& right
//
Classic::Classic(const Movie& right) {
   copy(right);
}

//------------------------------- operator= -----------------------------------
// Description:     deep copies a Classic into *this
//
// Preconditions:   Classic& right is a Classic with initialized data
//
// Postconditions:  *this is a copy of Classic& right
//
Classic& Classic::operator=(const Movie& right) {
   if(this != &right) {
      copy(right);
   }
   return *this;
}

//--------------------------------- copy --------------------------------------
// Description:     deep copies a Classic into *this
//
// Preconditions:   Classic& right is a Classic with initialized data
//
// Postconditions:  *this is a copy of Classic& right
//
void Classic::copy(const Movie& right) {
   const Classic& rightMovie = static_cast<const Classic &>(right);
   director = rightMovie.director;
   title = rightMovie.title;
   type = rightMovie.type;
   stock = rightMovie.stock;
   year = rightMovie.year;
   releaseMonth = rightMovie.releaseMonth;
   majorActor = rightMovie.majorActor;
   return;
}

//--------------------------------- setData -----------------------------------
// Description:     Sets the data members of a Classic Movie
//
// Preconditions:   string data holds information about a Classic Movie
//
// Postconditions:  return true if valid data was initailized to data members
//                  return false otherwise
//
bool Classic::setData(string data) {
   char space;
   stringstream ss(data);
   
   getline(ss, data, ',');   // movie type (i.e. comedy, classic, drama)
   type = data.at(0);
      
   getline(ss, data, ',');   // stock of movie
   stock = stoi(data);
   
   ss.get(space);
   getline(ss, data, ',');   // movie director
   director = data;
   
   ss.get(space);
   getline(ss, data, ',');   // movie title
   title = data;
   
   string firstName, lastName;         // major actor in movie
   ss >> firstName >> lastName;
   majorActor = firstName + " " + lastName;
   
   ss >> releaseMonth >> year;     // release date
   return true;
}

//------------------------------- operator< -----------------------------------
// Description:     Tests the value of two Movie objects
//                  Compares by title, then year it released
//
// Preconditions:   Movie& right is a Movie with intialized, valid data
//
// Postconditions:  return true if *this Movie's release date and major actor
//                  values are less than Movie& right
//                  return false otherwise
//
bool Classic::operator<(const Movie& right) const {
   const Classic& rightMovie = static_cast<const Classic &>(right);
   // test movie release years
   if(year < rightMovie.year) {
      return true;
   }
   else if(year > rightMovie.year) {
      return false;
   }
   
   // test movie release months if years are equal
   if(releaseMonth < rightMovie.releaseMonth) {
      return true;
   }
   else if(releaseMonth > rightMovie.releaseMonth) {
      return false;
   }
   
   // test major actor if release date is equal
   if(majorActor < rightMovie.majorActor) {
      return true;
   }
   else if(majorActor > rightMovie.majorActor) {
      return false;
   }
   return false;
}

//------------------------------- operator> -----------------------------------
// Description:     Tests the value of two Movie objects
//                  Compares by title, then year it released
//                  Utilizes already defined operator<
//
// Preconditions:   Movie& right is a Movie with intialized, valid data
//
// Postconditions:  return true if *this Movie's release date and major actor
//                  values is greater than Movie& right
//                  return false otherwise
//
bool Classic::operator>(const Movie& right) const {
   const Classic& rightMovie = static_cast<const Classic &>(right);
   return !(*this < rightMovie) && (*this != rightMovie);
}

//------------------------------- operator== ----------------------------------
// Description:     Tests the equality of two Movie objects
//                  Compares by title, then year it released
//
// Preconditions:   Movie& right is a Movie with intialized, valid data
//
// Postconditions:  return true if *this Movie's release date and major actor
//                  values is equal to Movie& right
//                  return false otherwise
//
bool Classic::operator==(const Movie& right) const {
   const Classic& rightMovie = static_cast<const Classic &>(right);
   return (majorActor == rightMovie.majorActor) && (year == rightMovie.year) &&
                                     (releaseMonth == rightMovie.releaseMonth);
}

//--------------------------------- isEqual -----------------------------------
// Description:     Tests the equality of two Movie objects
//                  Compares by director and title
//
// Preconditions:   Movie& right is a Movie with intialized, valid data
//
// Postconditions:  return true if *this Movie's release date and major actor
//                  values is equal to Movie& right
//                  return false otherwise
//
bool Classic::isEqual(const Movie& right) const {
   const Classic& rightMovie = static_cast<const Classic &>(right);
   return (director == rightMovie.director) && (title == rightMovie.title) &&
          (year == rightMovie.year) && (majorActor != rightMovie.majorActor) &&
          (stock != rightMovie.stock);
}

//------------------------------- operator!= ----------------------------------
// Description:     Tests the equality of two Movie objects
//                  Compares by title, then year it released
//                  Utilizes already defined operator==
//
// Preconditions:   Movie& right is a Movie with intialized, valid data
//
// Postconditions:  return true if *this Movie's release date and major actor
//                  values is not equal to Movie& right
//                  return false otherwise
//
bool Classic::operator!=(const Movie& right) const {
   return !(*this == right);
}

//----------------------------- getReleaseDate --------------------------------
int Classic::getReleaseDate() const {
   return releaseMonth + year;
}

//------------------------------ getMajorActor --------------------------------
string Classic::getMajorActor() const {
   return majorActor;
}

//------------------------------ setMajorActor --------------------------------
// Description:     sets the current Movie's major actor
//
// Preconditions:   none
//
// Postconditions:  the current major actor is set to majorA
//
bool Classic::setMajorActor(string majorA) {
   majorActor = majorA;
   return true;
}

//------------------------------ setReleaseMonth ------------------------------
// Description:     sets the current Movie's major actor
//
// Preconditions:   none
//
// Postconditions:  the current major actor is set to releaseM
//
bool Classic::setReleaseMonth(int releaseM) {
   releaseMonth = releaseM;
   return true;
}

//-------------------------------- display ------------------------------------
// Description:     Displays Movie data
//
// Preconditions:   none
//
// Postconditions:  Movie data is displayed using cout
//
void Classic::display() const {
   cout << setw(5) << type << setw(8) << 'D';
   cout << setw(25) << title << setw(18) << director;
   cout << setw(20) << majorActor;
   cout << setw(7) << releaseMonth << setw(7) << year;
   cout << setw(7) << stock << endl;
}


